# QQ `wrapper.node` signing reconstruction notes

This directory documents the current reverse-engineering state for the Linux QQ
`wrapper.node` signing path and the Python reconstruction in
`decompiled/signature_algorithm.py`.

## Documents

- [`signing_pipeline.md`](signing_pipeline.md)
  - High-level call chain and data flow.
  - `sub_5B62121`, `sub_5B6D9EB`, `sub_5B61D31`, final `LL` tail.
  - Current byte-for-byte regression status.
- [`keyderive_llijl.md`](keyderive_llijl.md)
  - Recovered `key8` derivation.
  - RC4 whitening and LLIJL VM/ChaCha path.
  - Native trace samples and validation results.
- [`environment_detection.md`](environment_detection.md)
  - Opcode `0x79` environment byte.
  - `madvise`, `/proc/<pid>/comm`, `frida-agent`, wrapper path checks.
  - Why default Python environment uses byte `0x00` for current traces.
- [`frida_tracing.md`](frida_tracing.md)
  - Which Frida scripts are safe/current.
  - Known pitfalls: `-q`, spawn vs attach, stdout mixing, Frida detection.
  - Recommended commands.
- [`trace_inventory.md`](trace_inventory.md)
  - Important trace files and what they prove.

## Current status snapshot

As of the latest attach trace (`attach_console_trace1.jsonl`):

```text
key8 derivation regression: 14 / 14
LLIJL transform regression: 14 / 14
full main signing regression: 14 / 14
py_compile: OK
```

Earlier trace sets remain useful:

```text
llijl_trace.jsonl: key8 25 / 25, LLIJL 25 / 25
sign_trace.jsonl: final LL tail 18 / 18
```

The main remaining operational caution is that Frida attach can trigger QQ
termination after some time. The current reconstruction does **not** require
Frida at runtime; Frida is only for research/validation traces.
