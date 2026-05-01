# Opcode `0x79` environment byte audit

This note documents every native check that contributes to byte `raw21[5]` in
the reconstructed wrapper output.

## Where the byte is written

- VM interpreter: `sub_5B64F10` (`decompiled/ida_raw/0x5B64F10_0x5B64F10.c`).
- Opcode: `0x79`.
- Target: object data byte offset `5`.
- Python mirror: `NativeEnvironment.flags_for_module()` and opcode `0x79` in
  `decompiled/signature_algorithm.py`.

For replaying captured native samples, `NativeEnvironment.env_flags_override`
can force the exact byte directly. If it is `None`, the byte is computed from
the modeled probe inputs below.

## Bit layout

| Bit | Mask | Native trigger | IDA evidence |
| --- | ---: | --- | --- |
| 0 | `0x01` | `madvise(obj_data, 0, 50) != -1` | `sub_5B64F10` at `0x5b6c039`, decompiled lines 1413-1423 |
| 1 | `0x02` | `/proc/<pid>/comm` does **not** contain `qq` | `sub_5B64F10` at `0x5b6ba89` builds `/proc/%d/comm`, lines 2105-2195 |
| 2 | `0x04` | global `dword_79ED4F0 == 1`; set by `/proc/self/maps` scan finding `frida-agent` | `sub_5B64F10` lines 1456-1460; `sub_5B7DFCD` at `0x5b7e13a` calls `strstr(line, "frida-agent")` |
| 3 | `0x08` | global `dword_79ED398 == 1`; set by wrapper path/module-name check failing | `sub_557A6A0` writes `dword_79ED398`; `sub_5B64F10` lines 1665-1675 ORs `0x08` |
| 7 | `0x80` | module id has neither `login` nor `Login`, and global `::i1 + 52` validity check fails | `sub_5B64F10` lines 1431-1454 |

All currently captured native traces used for regression have `raw21[5] == 0x00`.
Therefore the default Python environment models the observed QQ process as all
bits clear.

## `0x01`: `madvise` probe

Native path:

```c
addr = (void *)sub_5B62E30(i1a_1, v455);
v454 = madvise(addr, 0, 50) != -1;
if (v454)
    *(_BYTE *)(*((_QWORD *)addr + 1) + 5LL) = 1;
else
    *(_BYTE *)(*((_QWORD *)addr + 1) + 5LL) = 0;
```

Evidence:

- `0x5B64F10_0x5B64F10.c:1413-1423`.
- IDA address: `0x5b6c039`.

Important detail: this is an overwrite of byte `5`, not an OR. Later checks OR
additional bits into the same byte.

Current traces show the resulting byte is `0`, so Python uses
`madvise_success=False` by default.

## `0x02`: process comm probe

Native path:

1. `getpid()`.
2. `snprintf(filename, 0x100, "/proc/%d/comm", pid)`.
3. `fopen(..., "r")` and `fgets`.
4. Wrap line in `std::string`.
5. Search for substring `"qq"`.
6. If absent, OR byte `5` with `0x02`.

Evidence:

- `0x5B64F10_0x5B64F10.c:2105-2195`.
- Key addresses:
  - `0x5b6ba6a`: `getpid()`.
  - `0x5b6ba89`: builds `/proc/%d/comm`.
  - `0x5b6b999` / `0x5b6b9b1`: searches for `qq`.
  - `0x5b657c6`: ORs `0x02`.

Python mirror: `proc_comm="qq"` by default; if `"qq" not in proc_comm`, bit
`0x02` is set.

## `0x04`: Frida maps probe

Global: `dword_79ED4F0`.

IDA xrefs to `0x79ED4F0`:

- `0x5b67713` in `sub_5B64F10`: read for `== 1` check.
- `0x5b69776` in `sub_5B64F10`: read for initial `== -1` state.
- `0x5b6a346` / `0x5b67ca5` in `sub_5B64F10`: passed to `pthread_create`.

Thread function: `sub_5B7DFCD`.

Call xrefs to `sub_5B7DFCD`:

- `0x5b6a33f` in `sub_5B64F10`.
- `0x5b67c9e` in `sub_5B64F10`.

`sub_5B7DFCD` behavior:

1. Opens global `filename` with mode `"r"`.
2. Static initializer `sub_5B7E7D1` decodes `filename` to `/proc/self/maps`.
3. Reads each line with `fgets`.
4. Parses maps line with decoded format `%lx-%lx %*s %lx %*x:%*x %*d %s%n`.
5. Calls `strstr(line, "frida-agent")`.
6. On match, writes `*a1 = 1` and exits thread.
7. On EOF/no match, writes `*a1 = 0` and exits thread.

Evidence:

- `sub_5B7DFCD` decompiled from IDA at `0x5b7dfcd`.
- `0x5b7e433`: loads global `filename` for `fopen`.
- `0x5b7e13a`: `strstr(s, "frida-agent")`.
- `0x5b7e7ae`: writes `*a1 = 1`.
- `0x5b7e7bd`: writes `*a1 = 0`.
- `sub_5B7E7D1` decodes:
  - `3olv{4ipxq9|qca` with `byte ^ ((i + 1) ^ 0x1d)` -> `/proc/self/maps`.
  - second buffer -> `%lx-%lx %*s %lx %*x:%*x %*d %s%n`.

Opcode use:

```c
if (dword_79ED4F0 == 1)
    *(_BYTE *)(*((_QWORD *)addr + 1) + 5LL) |= 4u;
```

The VM starts this thread when `dword_79ED4F0 == -1`, and again after roughly
301 seconds. This means Frida detection is asynchronous: early signatures can
still show bit `0x04` clear even when Frida is attached, depending on timing and
whether the agent mapping name appears before the scan completes.

## `0x08`: wrapper path/module-name probe

Global: `dword_79ED398`.

IDA xrefs to `0x79ED398`:

- `0x557a995` in `sub_557A6A0`: writes `0`.
- `0x557ab4f` in `sub_557A6A0`: writes `1`.
- `0x5b694bc` in `sub_5B64F10`: reads for opcode `0x79`.

`sub_557A6A0` behavior:

1. Calls `dladdr(return_address, &info)`.
2. Reads `info.dli_fname`.
3. Decodes the local needle `wrapper.node` from `#Y_M[ZLZ\tHJ@F`.
4. `strstr(info.dli_fname, "wrapper.node")`:
   - if found: `dword_79ED398 = 0`.
   - if not found: `dword_79ED398 = 1`.

Evidence:

- `0x557A6A0_0x557A6A0.c:44-45`: `dladdr`.
- `0x557A6A0_0x557A6A0.c:202-205`: `strstr(haystack, decoded_needle)` and branch.
- `0x557a995`: set `0`.
- `0x557ab4f`: set `1`.
- Decoded needle: `wrapper.node`.

Opcode use:

```c
v395 = dword_79ED398;
if (dword_79ED398) {
    if (v395 == 1)
        byte5 |= 0x08;
}
```

The raw initial IDB value at `0x79ED398` is `-1`, but the relevant signing path
updates it in `sub_557A6A0` before the environment byte is consumed. Python
models the effective condition from the image path: contains `wrapper.node` ->
clear; otherwise set.

## `0x80`: non-login/global-state guard

Native path:

1. Copy module id from `i1 + 64`.
2. If module contains `login` or `Login`, skip this guard.
3. Otherwise call `sub_55FDCC0(&once_control_)`.
4. Check `*(unsigned int *)(::i1 + 52)`.
5. If invalid, OR byte `5` with `0x80`.

Evidence:

- `0x5B64F10_0x5B64F10.c:1431-1454`.
- Key addresses:
  - `0x5b69330`: `find("login")`.
  - `0x5b65b28`: `find("Login")`.
  - `0x5b6c811`: `sub_55FDCC0(&once_control_)`.
  - `0x5b6a59b`: ORs `0x80`.

Python mirror: if module id has neither `login` nor `Login` and
`global_i1_52_valid=False`, bit `0x80` is set.

## Current trace conclusion

Observed traces:

- `attach_console_trace1.jsonl`: `14/14` raw environment bytes are `0x00`.
- `sign_trace.jsonl`: `18/18` raw environment bytes are `0x00`.

So the byte-identical default is:

```python
NativeEnvironment(
    image_path="wrapper.node",
    proc_comm="qq",
    env_flags_override=None,
    madvise_success=False,
    global_i1_52_valid=True,
    dword_79ED4F0=0,
    dword_79ED398_override=None,
)
```

Frida-specific caution: `sub_5B7DFCD` can flip `dword_79ED4F0` to `1` after a
maps scan sees `frida-agent`; if that has happened before opcode `0x79`, native
will produce byte `0x04` instead of `0x00` (or OR it with other active bits).
