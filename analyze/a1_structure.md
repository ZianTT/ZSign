# A1 / MSF security self-structure audit

This note documents the native `a1` object used by `sub_2BF4E50` and the
related initialization path.  The important correction is that `a1` is not a
plain C struct with scalar fields.  It is a C++ object containing several
24-byte `std::string`-like slots using the libc++/Cr small-string layout.

## Native string slot layout

The code checks the low bit of the first byte/qword to distinguish small vs
heap strings:

```c
if ((*(_BYTE *)(slot) & 1) != 0)
    ptr = *(_QWORD *)(slot + 16);   // heap string data
else
    ptr = slot + 1;                 // small-string inline data
```

For length, small strings use `first_byte >> 1`; heap strings use the size at
`slot + 8`.  This is why `sub_2BF4E50` reads `a1+64`, `a1+88`, etc. as strings,
not raw pointers.

## `sub_2BF4310` copies JS/init input into `a1`

`sub_2BF4310(a1, a2, a3)` is the clearer initializer.  It copies five string
slots from the incoming config object `a2` into `a1`:

| `a1` offset | Source `a2` offset | Meaning | Evidence |
| ---: | ---: | --- | --- |
| `+16` | `a2+0` | data directory / base path | `sub_2BF4310`: `sub_22854A0(a1 + 16, a2)` |
| `+40` | `a2+24` | secondary path/config string | `sub_2BF4310`: `sub_22854A0(a1 + 40, a2 + 24)` |
| `+64` | `a2+48` | QUA / version string | log prints `Init, uin:{} qua:{}` and derives QUA length from `a2+48`; copied to `a1+64` |
| `+88` | `a2+72` | UIN | copied for the log's `uin:{}` argument and to `a1+88` |
| `+112` | `a2+96` | GUID | copied to `a1+112`; also used for `nt_mmkv_o3` MMKV init |

Evidence addresses:

- `0x2bf43a8`: copy `a2` -> `a1+16`.
- `0x2bf43b5`: copy `a2+24` -> `a1+40`.
- `0x2bf43c1`: copy `a2+48` -> `a1+64`.
- `0x2bf43d0`: copy `a2+72` -> `a1+88`.
- `0x2bf43e3`: copy `a2+96` -> `a1+112`.
- `0x2bf443b` / `0x2bf4458`: copies `a1+112` and initializes `nt_mmkv_o3`.
- `sub_2BF40F0(a3)`: sets the data directory and appends `security_data`.

`a1+8` is an initialization guard byte.  If set, `sub_2BF4310`/`sub_2BF4E50`
skip the one-time global config setup.

## `sub_2BF4E50` builds the five-pointer init array

On first use, `sub_2BF4E50` builds a local `dest[0..4]` array and passes it to
`sub_5575184 -> sub_557566C`:

| `dest` entry | Source | Meaning |
| ---: | --- | --- |
| `dest[0]` | `a1+16` string | data directory / base path |
| `dest[1]` | `sub_29FF8E0` then `sub_29FFC30(... +32)` | runtime device/session string, not an `a1` field |
| `dest[2]` | `a1+64` string | QUA / version string |
| `dest[3]` | `a1+88` string | UIN |
| `dest[4]` | `a1+112` string | GUID |

Important: `dest[1]` is the confusing “blank” value in our earlier model.  It
does not come from `a1`.  It is read from a singleton allocated by
`sub_29FF8E0`; `sub_29FFC30` copies the string at singleton offset `+32`.  In
the later report/config upload path this becomes one of the fields passed to
`sub_557EAAF`, but the signer output we reconstruct does not currently depend
on it unless the native background/report path is reproduced.

Evidence addresses:

- `0x2bf4eb3..0x2bf4f62`: resolves `dest[0..4]`.
- `0x29ffc42` / `0x29ffc51`: `sub_29FFC30` locks singleton `+16` and copies
  singleton `+32` into a temporary string.
- `0x2bf4f86`: calls `sub_5575184(dest)`.

## Global config object (`sub_5564244() -> &obj_`)

`sub_5564244` returns `&obj_`.  The relevant init write is
`sub_557E8BA(obj_, dest[0], dest[1], dest[2], dest[3], dest[4])`:

| `obj_` offset | Native assignment | Meaning |
| ---: | --- | --- |
| `+64` | `std::string::_M_replace(a1 + 64, ..., s_2)` where `s_2 = dest[2]` | QUA/version |
| `+96` | replaced from `s = dest[3]` | UIN |
| `+128` | replaced from `s_1 = dest[4]` | GUID |

`dest[0]` and `dest[1]` are passed to `sub_557E8BA` but are not stored in
`obj_+64/+96/+128`; they are used by the larger initialization/report path in
`sub_557566C`.

Evidence:

- `sub_557E8BA`:
  - `0x557e96d..0x557e98c`: write `a1+64` from `s_2`.
  - `0x557ea48..0x557ea67`: write `a1+96` from `s`.
  - `0x557e9c5..0x557e9e9`: write `a1+128` from `s_1`.
- `sub_556440D` reads `sub_5564244()+64` and serializes it as protobuf field
  `0x12` for non-special modules.
- `sub_55658EF` reads `sub_5564244()+160` as a mode flag.

## Separate report/config object (`qword_7A100E8`)

`sub_557566C` also constructs a larger object via `sub_557EAAF(&nn_1)`.  This is
not the `a1` self object and not the main signer output object.  It is a cached
report/config package used by other SDK paths.

`sub_557EAAF` allocates `0xF8` bytes and copies strings from a local serialized
bundle:

| Object offset | Meaning from inputs nearby |
| ---: | --- |
| `+8` | UIN / account string copy |
| `+40` | GUID copy |
| `+72` | an empty/default string in this path |
| `+104` | key material from `sub_5555707()` |
| `+136` | runtime device/session string (`dest[1]`) |
| `+168` | integer constant `4` in this path |
| `+176` | QUA/version string (`dest[2]`) |

Evidence:

- `sub_557566C` lines around `0x5579e4d..0x557a018` build the local bundle:
  - first string from `dest[3]` (UIN),
  - second from `dest[4]` (GUID),
  - one empty/default string,
  - key material from `sub_5555707()`,
  - `dest[1]` runtime string,
  - integer `4`,
  - `dest[2]` QUA.
- `sub_557EAAF` copies those bundle fields to `qword_7A100E8` at offsets
  `+8`, `+40`, `+72`, `+104`, `+136`, `+168`, `+176`.

This explains why several apparent “blank” fields exist: some are intentionally
empty/default report fields, and one is populated asynchronously from
`sub_5555707()` key material.

## Current Python mapping and gaps

Current `SecurityState` models only the signer-relevant subset:

| Python field | Native source | Notes |
| --- | --- | --- |
| `qua` | `a1+64` -> `obj_+64` | Used by `sub_556440D` field #2. |
| `uin` | `a1+88` -> `obj_+96` | Needed for faithful global/report state; not directly in current MD5 input except through future paths. |
| `guid` | `a1+112` -> `obj_+128` | Used for MMKV namespace/init and report/config object. |
| `cached_key_material` | `sub_5555707()` output | Currently empty unless supplied; native refresh path still not fully translated. |
| `config_seed` | override for `obj_+64` field #2 | Should normally be empty so QUA is used. |
| `ecdh_field1_override` | `sub_58FC982/sub_55455F8` special ECDH producer | Required only for special `trpc.o3.ecdh_access.*` modules until translated. |

Fields not yet modeled because they do not affect the recovered sign path we are
currently returning:

- `a1+16`: data directory / base path, used for `security_data` and MMKV setup.
- `a1+40`: copied from init input but not consumed by `sub_2BF4E50`'s signer
  array; likely secondary path/config string for broader SDK init.
- `dest[1]`: singleton runtime device/session string from `sub_29FF8E0`.
- report bundle empty/default string at `qword_7A100E8+72`.
- the full `sub_5555707()` key-material refresh/cache machinery.

For byte-identical signing of the currently verified samples, the critical
native inputs remain QUA, UIN, GUID, key material when non-empty, and the
`sub_556440D` special ECDH field override for the two special modules.
