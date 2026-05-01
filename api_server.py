"""ZSign-compatible HTTP API for the reconstructed signer.

This server intentionally does **not** load `wrapper.node` and does not use
Frida.  It exposes the same practical endpoints as ZSign's `agent.py`, then
routes requests into `decompiled.signature_algorithm`.

The wrapper path is translated at the high level from VM_PROGRAM_MAIN, including
the environment byte written by opcode 0x79.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass
from typing import Any

from flask import Flask, jsonify, request

from decompiled.signature_algorithm import (
    NativeWrapper,
    NativeEnvironment,
    SecurityState,
    build_ecdh_access_blob,
    build_encrypted_md5_signature,
    generate_security_sign_parts,
)


VERSION = "3.2.22-42941-rewrapped"
VERSION_CODE = ["42941"]

APPINFO: dict[str, Any] = {
    "AppClientVersion": 42941,
    "AppId": 1600001615,
    "AppIdQrCode": 13697054,
    "CurrentVersion": "3.2.22-42941",
    "Kernel": "Linux",
    "SdkInfo": {
        "MainSigMap": 169742560,
        "MiscBitMap": 32764,
        "SdkVersion": "nt.wtlogin.0.0.1",
        "SubSigMap": 0,
        "SdkBuildTime": 0,
    },
    "NTLoginType": 1,
    "Os": "Linux",
    "PackageName": "com.tencent.qq",
    "ApkSignatureMd5": "636f6d2e74656e63656e742e7171",
    "PtVersion": "2.0.0",
    "SsoVersion": 19,
    "SubAppId": 537328659,
    "VendorOs": "linux",
}


@dataclass
class ApiConfig:
    qua: str = "V1_LNX_NQ_3.2.22_42941_GW_B"
    uin: str = "0"
    guid: str = "14dd2dee2a8321b8f3461a197ee0b7a2"
    config_seed_hex: str = ""
    key_material_hex: str = ""
    state_mode: int = 0
    image_path: str = "wrapper.node"
    proc_comm: str = "qq"
    env_flags: int | None = None
    madvise_success: bool = False
    global_i1_52_valid: bool = True
    dword_79ED4F0: int = 0
    dword_79ED398: int | None = None
    allow_unverified_sign: bool = False


def _hex_to_bytes(value: str, field: str) -> bytes:
    value = (value or "").strip()
    if not value:
        return b""
    try:
        return bytes.fromhex(value)
    except ValueError as exc:
        raise ValueError(f"{field} must be hex") from exc


def _json_error(message: str, status_code: int = 400, **extra: Any):
    payload = {"status": "error", "message": message}
    payload.update(extra)
    return jsonify(payload), status_code


def _build_state(config: ApiConfig, body: dict[str, Any]) -> SecurityState:
    state = SecurityState()
    state.qua = str(body.get("qua", body.get("version_qua", config.qua)))
    state.uin = str(body.get("uin", config.uin))
    state.guid = str(body.get("guid", config.guid))
    state.mode = int(body.get("state_mode", config.state_mode))
    state.config_seed = _hex_to_bytes(body.get("config_seed", config.config_seed_hex), "config_seed")
    state.cached_key_material = _hex_to_bytes(
        body.get("key_material", config.key_material_hex), "key_material"
    )
    if "ecdh_field1_override" in body:
        state.ecdh_field1_override = _hex_to_bytes(body.get("ecdh_field1_override", ""), "ecdh_field1_override")
    return state


def _payload_from_request(body: dict[str, Any]) -> tuple[str, bytes, int, int]:
    cmd = str(body.get("cmd", ""))
    if "src" not in body:
        raise ValueError("缺少必要参数 src")
    src_hex = str(body.get("src", ""))
    seq = int(body.get("seq", 0))
    sign_type = int(body.get("sign_type", seq))
    if not cmd:
        raise ValueError("缺少必要参数 cmd")
    return cmd, _hex_to_bytes(src_hex, "src"), seq, sign_type


def _milky_body_to_zsign_body(body: dict[str, Any], config: ApiConfig) -> dict[str, Any]:
    """Translate Lagrange.Milky Signer.cs sec-sign request shape.

    Milky posts to /api/sign/sec-sign with {command, seq, body, guid, qua, uin}
    and expects {code, message, value: {sec_sign, sec_token, sec_extra}}.
    """
    command = str(body.get("command", body.get("cmd", "")))
    src = str(body.get("body", body.get("src", "")))
    translated = dict(body)
    translated["cmd"] = command
    translated["src"] = src
    translated["seq"] = int(body.get("seq", body.get("sequence", 0)))
    translated["sign_type"] = int(body.get("sign_type", translated["seq"]))
    translated["uin"] = str(body.get("uin", config.uin))
    translated["guid"] = str(body.get("guid", config.guid))
    translated["qua"] = str(body.get("qua", body.get("version_qua", config.qua)))
    # Milky's Signer.cs does not send this research gate; compatibility endpoint
    # should still return the expected sign object when the server was started
    # for local signing.
    translated["allow_unverified_sign"] = bool(body.get("allow_unverified_sign", config.allow_unverified_sign))
    return translated


def _build_env(config: ApiConfig, body: dict[str, Any]) -> NativeEnvironment:
    env_body = body.get("env", {}) if isinstance(body.get("env", {}), dict) else {}
    env_flags = env_body.get("env_flags", body.get("env_flags", config.env_flags))
    dword_79ED398 = env_body.get("dword_79ED398", body.get("dword_79ED398", config.dword_79ED398))
    return NativeEnvironment(
        image_path=str(env_body.get("image_path", body.get("image_path", config.image_path))),
        proc_comm=str(env_body.get("proc_comm", body.get("proc_comm", config.proc_comm))),
        env_flags_override=None if env_flags is None else int(env_flags),
        madvise_success=bool(env_body.get("madvise_success", body.get("madvise_success", config.madvise_success))),
        global_i1_52_valid=bool(env_body.get("global_i1_52_valid", body.get("global_i1_52_valid", config.global_i1_52_valid))),
        dword_79ED4F0=int(env_body.get("dword_79ED4F0", body.get("dword_79ED4F0", config.dword_79ED4F0))),
        dword_79ED398_override=None if dword_79ED398 is None else int(dword_79ED398),
    )


def _sign_response(
    config: ApiConfig,
    body: dict[str, Any],
    version_code: str,
) -> dict[str, Any]:
    if not bool(body.get("allow_unverified_sign", config.allow_unverified_sign)):
        raise RuntimeError(
            "offline signer is fully native-free but not yet proven byte-identical "
            "against wrapper.node samples; refusing to return an unverified sign "
            "(set allow_unverified_sign=true only for local differential research)"
        )
    cmd, payload, seq, sign_type = _payload_from_request(body)
    state = _build_state(config, body)
    env = _build_env(config, body)
    wrapper = NativeWrapper(env=env)

    parts = generate_security_sign_parts(
        state=state,
        module_id=cmd,
        payload=payload,
        sign_type=sign_type,
        wrapper=wrapper,
        image_path=env.image_path,
    )

    return {
        "platform": "Linux",
        "version": VERSION,
        "version_code": version_code,
        "status": "ok",
        "verified_byte_identical": False,
        "seq": seq,
        "cmd": cmd,
        "env_flags": env.flags_for_module(cmd),
        "env": {
            "env_flags_override": env.env_flags_override,
            "madvise_success": env.madvise_success,
            "dword_79ED398": env.dword_79ED398,
            "dword_79ED4F0": env.dword_79ED4F0,
            "global_i1_52_valid": env.global_i1_52_valid,
            "image_path": env.image_path,
            "proc_comm": env.proc_comm,
        },
        "a1": {
            "qua": state.qua,
            "uin": state.uin,
            "guid": state.guid,
            "note": "A1 fields are captured but the full native initialization chain is not fully translated yet",
        },
        "value": {
            # ZSign-compatible names.
            "sign": parts.part2_signature.hex(),
            "extra": parts.part1_ecdh_blob.hex(),
            "token": parts.part0_key_material.hex(),
        },
    }


def create_app(config: ApiConfig | None = None) -> Flask:
    config = config or ApiConfig()
    app = Flask(__name__)

    @app.get("/")
    def index():
        return jsonify({"status": "ok", "msg": "Welcome to rewrapper ZSign-compatible API!"})

    @app.get("/health")
    def health():
        return jsonify({
            "status": "ok",
            "engine": "rewrapper",
            "native_dependency": False,
            "environment_byte_modeled": True,
        })

    @app.route("/mng/version_code", methods=["GET", "PUT", "DELETE"])
    def manage_version_code():
        if request.method == "GET":
            return jsonify({"status": "ok", "version_code": VERSION_CODE})
        data = request.get_json(silent=True) or {}
        version_code = str(data.get("version_code", ""))
        if not version_code:
            return _json_error("缺少 version_code 参数")
        if request.method == "PUT":
            if version_code not in VERSION_CODE:
                VERSION_CODE.append(version_code)
            return jsonify({"status": "ok", "version_code": VERSION_CODE})
        if version_code in VERSION_CODE:
            VERSION_CODE.remove(version_code)
        return jsonify({"status": "ok", "version_code": VERSION_CODE})

    @app.route("/api/sign/<version_code>/appinfo", methods=["GET", "POST"])
    @app.route("/api/sign/<version_code>/appinfo_v2", methods=["GET", "POST"])
    def appinfo(version_code: str):
        return jsonify(APPINFO | {"VersionCode": version_code})

    @app.post("/api/sign/<version_code>")
    def sign(version_code: str):
        try:
            body = request.get_json(silent=True) or {}
            return jsonify(_sign_response(config, body, version_code))
        except Exception as exc:  # keep ZSign-like JSON failures
            return _json_error(str(exc), 400)

    @app.post("/api/sign/sec-sign")
    def milky_sec_sign():
        try:
            body = _milky_body_to_zsign_body(request.get_json(silent=True) or {}, config)
            response = _sign_response(config, body, VERSION_CODE[0] if VERSION_CODE else "42941")
            value = response["value"]
            return jsonify({
                "code": 0,
                "message": "ok",
                "value": {
                    "sec_sign": value["sign"],
                    "sec_token": value["token"],
                    "sec_extra": value["extra"],
                },
            })
        except Exception as exc:
            return jsonify({"code": 1, "message": str(exc), "value": None}), 400

    @app.post("/api/debug/md5")
    def debug_md5():
        try:
            body = request.get_json(silent=True) or {}
            cmd, payload, _seq, sign_type = _payload_from_request(body)
            state = _build_state(config, body)
            digest = build_encrypted_md5_signature(
                state, cmd, str(sign_type).encode("ascii"), payload, NativeWrapper(env=_build_env(config, body))
            )
            ecdh = build_ecdh_access_blob(state, cmd, payload)
            return jsonify({"status": "ok", "wrapped_sign": digest.hex(), "extra": ecdh.hex()})
        except Exception as exc:
            return _json_error(str(exc), 400)

    return app


def main() -> None:
    parser = argparse.ArgumentParser(description="Run rewrapper ZSign-compatible API")
    parser.add_argument("--host", default="0.0.0.0")
    parser.add_argument("--port", type=int, default=5000)
    parser.add_argument("--config-seed", default="", help="default state.config_seed as hex")
    parser.add_argument("--key-material", default="", help="default key material as hex")
    parser.add_argument("--qua", default="V1_LNX_NQ_3.2.22_42941_GW_B", help="A1 +64 QUA/version string")
    parser.add_argument("--uin", default="0", help="A1 +88 UIN string")
    parser.add_argument("--guid", default="14dd2dee2a8321b8f3461a197ee0b7a2", help="A1 +112 GUID string")
    parser.add_argument("--state-mode", type=int, default=0)
    parser.add_argument("--image-path", default="wrapper.node")
    parser.add_argument("--proc-comm", default="qq")
    parser.add_argument("--env-flags", type=lambda value: int(value, 0), default=None,
                        help="force exact opcode 0x79 environment byte, e.g. 0x04")
    parser.add_argument("--madvise-success", action="store_true",
                        help="set bit 0x01 unless --env-flags overrides it")
    parser.add_argument("--dword-79ed4f0", type=int, default=0)
    parser.add_argument("--dword-79ed398", type=int, default=None)
    parser.add_argument("--global-i1-52-invalid", action="store_true",
                        help="set bit 0x80 for non-login modules unless --env-flags overrides it")
    parser.add_argument("--allow-unverified-sign", action="store_true")
    args = parser.parse_args()

    app = create_app(ApiConfig(
        qua=args.qua,
        uin=args.uin,
        guid=args.guid,
        config_seed_hex=args.config_seed,
        key_material_hex=args.key_material,
        state_mode=args.state_mode,
        image_path=args.image_path,
        proc_comm=args.proc_comm,
        env_flags=args.env_flags,
        madvise_success=args.madvise_success,
        global_i1_52_valid=not args.global_i1_52_invalid,
        dword_79ED4F0=args.dword_79ed4f0,
        dword_79ED398=args.dword_79ed398,
        allow_unverified_sign=args.allow_unverified_sign,
    ))
    app.run(host=args.host, port=args.port, debug=False, use_reloader=False)


if __name__ == "__main__":
    main()
