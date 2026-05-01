# rewrapper ZSign-compatible API

This API mirrors the useful HTTP shape of `ZSign/agent.py` without Frida and
without loading `wrapper.node`.

Important: the signer is fully native-free, but the reconstructed final VM has
not yet been proven byte-identical against native `wrapper.node` samples.  The
public sign endpoint therefore refuses to return a sign by default.  Use
`allow_unverified_sign` only for local differential research.

Do not use signatures captured while Frida is attached as final byte-identical
truth.  Those samples may include anti-instrumentation/environment pollution.
Clean validation must come from a non-Frida or otherwise decontaminated QQ /
`wrapper.node` run with matching environment flags.

For research-only cleaner traces, load `frida_bypass_antitrace.js` before the
trace script.  It forces wrapper-originated checks for `dladdr`, `madvise`,
`/proc/<pid>/comm`, and `/proc/self/maps` toward the normal QQ/wrapper path, but
the process is still Frida-attached and results must still be verified against a
true no-Frida capture.

## Start

```bash
python api_server.py --host 0.0.0.0 --port 5000
```

Optional environment controls for the VM opcode `0x79` byte:

```bash
python api_server.py --port 5000 --image-path wrapper.node --proc-comm qq --dword-79ed4f0 0
```

## Endpoints

### Health

```text
GET /
GET /health
```

### App info

Compatible with ZSign:

```text
GET  /api/sign/<version_code>/appinfo
POST /api/sign/<version_code>/appinfo
GET  /api/sign/<version_code>/appinfo_v2
POST /api/sign/<version_code>/appinfo_v2
```

### Sign

```text
POST /api/sign/<version_code>
Content-Type: application/json
```

Request body:

```json
{
  "cmd": "trpc.login.ecdh.EcdhService.SsoKeyExchange",
  "src": "0A4104...",
  "seq": 123456,
  "sign_type": 123456,
  "config_seed": "",
  "key_material": "",
  "allow_unverified_sign": false,
  "env": {
    "image_path": "wrapper.node",
    "proc_comm": "qq",
    "madvise_success": true,
    "global_i1_52_valid": true,
    "dword_79ED4F0": 0
  }
}
```

Notes:

- `cmd` maps to native `module_id`.
- `src` is payload bytes as hex.
- `src` may be an empty string; native constructs the body from pointer+length.
- `seq` is echoed and defaults `sign_type` when `sign_type` is omitted.
- `config_seed` and `key_material` are optional hex overrides for reconstructed
  global state.
- `env` overrides the native environment checks that feed output byte `sign[5]`.
- `allow_unverified_sign=true` is required to return the reconstructed sign;
  otherwise the endpoint returns an error rather than pretending the sign is
  byte-identical.
- For the two `trpc.o3.ecdh_access.*` modules, native `sub_556440D` derives
  field1 from `payload` via `sub_58FC982/sub_55455F8`; until that producer is
  translated, the API requires a verified `ecdh_field1_override` instead of
  returning a fake value.

Response shape follows ZSign:

```json
{
  "platform": "Linux",
  "version": "3.2.22-42941-rewrapped",
  "version_code": "42941",
  "status": "ok",
  "verified_byte_identical": false,
  "seq": 123456,
  "cmd": "trpc.login.ecdh.EcdhService.SsoKeyExchange",
  "env_flags": 1,
  "env": {
    "dword_79ED398": 0,
    "dword_79ED4F0": 0,
    "proc_comm": "qq"
  },
  "value": {
    "sign": "...",
    "extra": "...",
    "token": "..."
  }
}
```

`env_flags` is the exact byte inserted by VM opcode `0x79` at offset 5 of the
21-byte native-wrapped sign.

## Example

```bash
curl -s http://127.0.0.1:5000/api/sign/42941 \
  -H "Content-Type: application/json" \
  -d '{"cmd":"wtlogin.trans_emp","src":"020164","seq":1}'
```
