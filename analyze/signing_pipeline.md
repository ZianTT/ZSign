# Signing pipeline reconstruction

## Scope

This document describes the recovered Linux QQ `wrapper.node` signing chain used
by the Python implementation in `decompiled/signature_algorithm.py`.

The focus is the path observed through `sub_55658EF` → `sub_5B62121` → nested VM
programs → final 32-byte wrapped digest.

## Main observed call chain

Latest confirmed attach trace: `attach_console_trace1.jsonl`.

Typical event sequence:

```text
enter_sub_55658EF
  enter_sub_5B62121
    enter_sub_5B64F10       # VM_PROGRAM_MAIN
      enter_sub_5B6D9EB     # compound helper, opcode 0x77 path
        enter_sub_5B64F10   # VIPII nested VM, token generation
        enter_sub_5B61D31   # LLIJL launcher
          enter_sub_5B64F10 # VM_PROGRAM_LLIJL
      enter_sub_5B7D768     # tail wrapper, opcode 0x7a path
        enter_sub_5B7D5DC   # nested VM launcher("LL", ...)
          enter_sub_5B64F10 # final LL VM
```

Representative trace sample:

```json
{
  "event": "enter_sub_5B62121",
  "module_id": { "text": "wtlogin.trans_emp" },
  "digest_hex": "e5eb327429d9d6f4159fce3bb1337009",
  "extra_len": 0
}
```

The corresponding helper call:

```json
{
  "event": "enter_sub_5B6D9EB",
  "scalar": 2465009152,
  "n": 4,
  "mode": 21,
  "salt": "0x14b7ba9329e934e3"
}
```

Then LLIJL receives:

```json
{
  "event": "enter_sub_5B61D31",
  "key_hex": "46775a07d5cab38e",
  "src_len": 20,
  "src_hex": "e5eb327429d9d6f4159fce3bb1337009000eed92"
}
```

Final output for that sample:

```json
{
  "event": "leave_sub_5B62121",
  "result": {
    "len": 32,
    "data_hex": "6d8a870dcd9f0a5ee6dbb1a0ef17105f46effe1a69c77ec69f8ed786ec0458fa"
  }
}
```

## `sub_5B62121`: top-level native wrap digest

Observed arguments:

```text
arg0: std::string* module_id
arg1: digest pointer
arg2: digest length, observed 16
arg3: extra pointer
arg4: extra length, observed 0 in current samples
```

Python entry point:

```python
native_wrap_digest_recovered(module_id, digest16, extra, env, timestamp_word)
```

The current implementation requires the timestamp/scalar for exact trace
regression. In production-style usage it generates one from time.

## `VM_PROGRAM_MAIN`

`sub_5B62121` enters `sub_5B64F10` with a program head matching:

```text
12000200090000009d1b0000b500000002001500750112000000000145010400
```

This is `VM_PROGRAM_MAIN` in Python.

Key operations:

1. Build a 20-byte header object.
2. Populate timestamp/scalar bytes.
3. Run `sub_5B6D9EB` to fill token and digest portion.
4. Run opcode `0x79` environment-byte mutation.
5. Run opcode `0x7a`, which calls `sub_5B7D768` and final `LL` VM.

## Header and raw21 layout

Before final tail wrapping, native has a 21-byte object that can be recovered
from `enter_sub_5B7D768.input_minus2_21_hex`.

Observed layout:

```text
raw21[0]      = 0x0c
raw21[1]      = 0x15
raw21[2:4]   = CRC16-like checksum, little-endian
raw21[4]      = first byte of 4-byte VIPII token
raw21[5]      = environment byte from opcode 0x79
raw21[6:8]   = remaining VIPII token bytes
raw21[8:12]  = scalar/timestamp bytes in the transformed layout boundary
raw21[... ]  = first 8 bytes of MD5(LLIJL output), shifted by env insertion
```

Important: Python initially failed full main regression because `raw21[5]` was
modeled as `0x01`; native current traces show it is `0x00`. See
[`environment_detection.md`](environment_detection.md).

## `sub_5B6D9EB`: compound helper

`sub_5B6D9EB` receives:

```text
scalar: timestamp-like u32
n:      4
mode:   21
salt:   0x14b7ba9329e934e3
```

It performs:

1. Generate a 4-byte VIPII token.
2. Copy the token into the header.
3. Derive `key8`.
4. Build LLIJL source as `digest16 + scalar_le32`.
5. Run `sub_5B61D31(key8, 8, salt, src20, 20)`.
6. MD5 the LLIJL output and copy the first 8 bytes into the header.

## `sub_5B61D31`: LLIJL launcher

This launches the nested `LLIJL` VM program. The program head observed in traces:

```text
1b00050006000000420f0000e70000002400170028011a00201221231e000204
```

Python entry point:

```python
llijl_transform(src20, key8, salt64)
```

## `sub_5B7D768` and final `LL` VM

`sub_5B7D768(input_ptr, n=20)` receives `raw21 + 2`, constructs the final 20-byte
object, overwrites the last logical byte with `0x04`, and calls `sub_5B7D5DC`
with format `"LL"`.

The final `LL` VM program head observed:

```text
3500000000000000000000000000000028003400020100012111200022013605
```

Python entry point:

```python
native_tail_wrap_0x7a(raw21)
```

## Current validation

Latest trace: `attach_console_trace1.jsonl`, extracted from the Frida console
output.

Regression command summary:

```text
key8  14 / 14
llijl 14 / 14
main  14 / 14
```

The older traces also remain aligned for their validated layers:

```text
llijl_trace.jsonl: key8 25 / 25, LLIJL 25 / 25
sign_trace.jsonl: final LL tail 18 / 18
```
