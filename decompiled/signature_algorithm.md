# sub_2BF4E50 signing algorithm reconstruction

Target: `wrapper.node` (`D:\User\Downloads\QQ\42941\wrapper.node`)  
Entry: `sub_2BF4E50` (`msf_security_sign_callback.cc`, log function name `MSFSign`)

Raw Hex-Rays output has been exported to `decompiled/ida_raw/`.

## Top-level flow

```text
sub_2BF4E50(ctx, module_id_string, byte_vector, out_3_strings, sign_type)
  └─ one-time init and persistent callback registration
  └─ sub_557A6A0(module_id.c_str(), data.ptr, data.len, sign_type, temp768)
       ├─ anti-tamper dladdr check: image path must contain "wrapper.node"
       ├─ sign_type_s = std::to_string(sign_type)
       ├─ body = std::string(data.ptr, data.ptr + data.len)
       ├─ part2 = sub_55658EF(module_id, sign_type_s, body)
       ├─ part1 = sub_556440D(module_id, body)
       └─ part0 = sub_5555707()  // cache/refresh ECDH/session key material
```

`sub_557A6A0` writes three fixed slots:

| Slot | Native offset | Producer | Meaning |
|---|---:|---|---|
| part0 | `dest + 0`, len at `dest[255]` | `sub_5555707()` | cached/refreshed ECDH key material/token |
| part1 | `dest + 256`, len at `dest[511]` | `sub_556440D(module, body)` | ECDH access protobuf-like auxiliary blob |
| part2 | `dest + 512`, len at `dest[767]` | `sub_55658EF(module, sign_type_s, body)` | final MD5 digest after native wrapping |

`sub_2BF4E50` converts these three slots back to three output `std::string`s.

## `sub_55658EF`: final signature part

This function contains an inlined standard MD5 implementation:

* IV: standard MD5 state (`0x67452301`, `0xefcdab89`, `0x98badcfe`, `0x10325476`) via `xmmword_990130`.
* Round constants include `-680876936`, `-389564586`, `606105819`, etc.
* Rotation groups match MD5: `7,12,17,22`, `5,9,14,20`, `4,11,16,23`, `6,10,15,21`.
* Padding is the normal MD5 `0x80, 0, ...` block.

Recovered behavior:

```python
if !global_security_enabled:
    return ""

if sign_type_s and global_config.mode == 1:
    digest = MD5(sign_type_s)
else:
    material = sub_5555707() + sub_556440D(module_id, body) + body
    digest = MD5(material)

return sub_5B62121(module_id, digest16, "")
```

`sub_5B62121` is the native wrapping/encoding layer. It receives the raw
16-byte MD5 digest and an empty extra string, builds two length+pointer blocks,
and calls `sub_5B61AFB(module_id, "LLL", ...)`. `sub_5B61AFB` copies a static
`0x17a` byte table and returns an allocated output buffer via `sub_5B64F10`.

The recovered `LLL` raw object `r7` is 21 bytes:

```text
offset  source
0..4    first five bytes of the 20-byte native header
5       environment flags written by VM opcode 0x79
6..20   header bytes 5..19
```

This raw object is **not** the final sign.  Native immediately runs opcode
`0x7a`:

```text
r2 = sub_5B7D768(r7.data + 2, slot[2])  # slot[2] == 20 on this path
return r2
```

`sub_5B7D768` builds a 20-byte input object, copies 19 bytes from `r7.data + 2`,
writes `0x04` as the last byte, and invokes another nested VM with format
`"LL"`.  `sub_55658EF` copies the final returned object's own length, not 21
bytes.  Any implementation returning the raw 21-byte `r7` is wrong.

The environment byte is part of the raw object that feeds the final `LL` wrapper.
Its bits are:

```text
0x01  madvise probe succeeded
0x02  /proc/<pid>/comm does not contain "qq" or cannot be read
0x04  dword_79ED4F0 == 1
0x08  dword_79ED398 == 1; set when dladdr image path lacks "wrapper.node"
0x80  global ::i1+52 path/string check invalid
```

For module names containing `login` or `Login`, native skips the `0x80/0x04/0x08`
checks but still applies the process-name `0x02` check.

## `sub_556440D`: ECDH access blob

Obfuscated strings decode to:

```text
trpc.o3.ecdh_access.EcdhAccess.SsoEstablishShareKey
trpc.o3.ecdh_access.EcdhAccess.SsoSecureAccess
```

For these modules, it calls `sub_58FC982` and `sub_55455F8` to derive field data from global config/session state.

Important payload detail: for these ECDH access modules, native constructs a
string from the exact body bytes and passes it into `sub_58FC982`; therefore the
body affects `extra` as well as being appended to the MD5 material.  For other
modules, `extra` is only the recovered config/session fields and the body affects
the final digest through the final `+ body` append in `sub_55658EF`.

Exception: when global mode at `sub_5564244()+160` is `1` and the sign-type
string is non-empty, `sub_55658EF` hashes only the decimal sign-type string and
does not include body bytes in the MD5 input.

The output serialization is protobuf-like length-delimited fields:

```text
field 1 tag 0x0a: field1 bytes
field 2 tag 0x12: field2 bytes
field 3 tag 0x1a: field3 bytes
```

## Files

* `signature_algorithm.py` — readable reconstruction with executable helpers for the recovered native wrapping path.
* `ida_raw/*.c` — raw Hex-Rays output for the analyzed functions.

## Remaining uncertainty

The `LLIJL` transform and environment byte are translated.  Remaining
byte-for-byte blocker: final opcode `0x7a` / `sub_5B7D768("LL")`, which transforms
the raw 21-byte object into the actual returned sign object.
