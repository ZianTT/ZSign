// Frida 17 compatible deep sampler for wrapper.node final "LL" VM.
//
// Purpose:
//   Boundary trace already proved sub_5B7D5DC("LL") inputs/outputs.  This
//   script samples the VM internals enough to align native execution with the
//   Python NativeWrappingVM implementation: object resolution, object binding,
//   scalar/object table snapshots, and selected hot native interpreter labels.
//
// Usage:
//   frida -p <QQ_PID> -l frida_trace_ll_deep.js -o ll_deep_trace.jsonl
//
// Stop after one or two LL samples; this intentionally logs a lot.

'use strict';

const TARGET_MODULE = 'wrapper.node';

const OFF = {
  sub_5B62E30: 0x5B62E30,   // object slot resolver
  sub_5B63780: 0x5B63780,   // bind object to VM slot
  sub_5B64F10: 0x5B64F10,   // VM interpreter
  sub_5B749DE: 0x5B749DE,   // object table find/append
  sub_5B7D5DC: 0x5B7D5DC,   // final LL launcher
};

// Native interpreter label offsets from Hex-Rays comments.  These are not VM
// opcodes by themselves, but they mark important semantic paths.
const LABELS = {
  scalar_dword_write: 0x5B6939B,
  scalar_qword_write: 0x5B6C0CD,
  obj_write_byte: 0x5B66DE8,
  obj_write_dword: 0x5B67CDC,
  obj_read_byte: 0x5B6A0C8,
  obj_read_dword: 0x5B67259,
  obj_read_qword: 0x5B67A1B,
  obj_write_qword: 0x5B68808,
  branch_taken_word: 0x5B6839C,
  instr_advance_4: 0x5B6C0D5,
  instr_advance_2: 0x5B6C7CD,
  vm_return: 0x5B6C873,
};

const MAX_BYTES = 256;
const MAX_RESOLVE_LOGS = 12000;
const MAX_BIND_LOGS = 2000;
const MAX_LABEL_LOGS = 8000;
const SNAPSHOT_SLOTS = 64;
const SNAPSHOT_OBJECTS = 80;

let modBase = NULL;
let llLauncherDepth = 0;
let activeVmDepth = 0;
let activeCtx = NULL;
let activeProgram = NULL;
let activeSampleId = 0;
let resolveLogs = 0;
let bindLogs = 0;
let labelLogs = 0;

function now() { return (new Date()).toISOString(); }

function jlog(obj) {
  obj.ts = now();
  console.log(JSON.stringify(obj));
}

function hexPtr(p) {
  try { return ptr(p).toString(); } catch (_) { return String(p); }
}

function ptrOrNull(p) {
  try { return ptr(p); } catch (_) { return NULL; }
}

function rel(p) {
  try {
    if (!modBase || modBase.isNull()) return hexPtr(p);
    return '0x' + ptr(p).sub(modBase).toString(16);
  } catch (_) {
    return hexPtr(p);
  }
}

function dumpHex(p, len, maxLen) {
  p = ptrOrNull(p);
  if (!p || p.isNull()) return null;
  const n = Math.max(0, Math.min(Number(len), maxLen || MAX_BYTES));
  try {
    const ab = p.readByteArray(n);
    if (ab === null) return null;
    const u = new Uint8Array(ab);
    let s = '';
    for (let i = 0; i < u.length; i++) s += ('0' + u[i].toString(16)).slice(-2);
    return s;
  } catch (e) {
    return 'READ_ERROR:' + e;
  }
}

function readCStringSafe(p, maxLen) {
  p = ptrOrNull(p);
  if (!p || p.isNull()) return null;
  try { return p.readCString(maxLen || 128); } catch (e) { return 'CSTR_ERROR:' + e; }
}

function readNativeObject(op) {
  op = ptrOrNull(op);
  if (!op || op.isNull()) return { ptr: hexPtr(op), null: true };
  try {
    const len = op.readU32();
    const type = op.add(4).readU16();
    const data = op.add(8).readPointer();
    return {
      ptr: hexPtr(op),
      len: len,
      type: type,
      data_ptr: hexPtr(data),
      data_head: dumpHex(data, Math.min(len, MAX_BYTES), MAX_BYTES),
    };
  } catch (e) {
    return { ptr: hexPtr(op), error: String(e) };
  }
}

function readArgBlock(ap) {
  ap = ptrOrNull(ap);
  if (!ap || ap.isNull()) return { ptr: hexPtr(ap), null: true };
  try {
    const len = ap.readU32();
    const type = ap.add(4).readU16();
    const data = ap.add(8).readPointer();
    return { ptr: hexPtr(ap), len, type, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, MAX_BYTES) };
  } catch (e) {
    return { ptr: hexPtr(ap), error: String(e) };
  }
}

function readNativeResult(rp) {
  rp = ptrOrNull(rp);
  if (!rp || rp.isNull()) return { ptr: hexPtr(rp), null: true };
  try {
    const len = rp.readU32();
    const data = rp.add(8).readPointer();
    return { ptr: hexPtr(rp), len, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, 4096) };
  } catch (e) {
    return { ptr: hexPtr(rp), error: String(e) };
  }
}

function readCtxLayout(ctx) {
  ctx = ptrOrNull(ctx);
  if (!ctx || ctx.isNull()) return { ctx: hexPtr(ctx), null: true };
  try {
    return {
      ctx: hexPtr(ctx),
      program: hexPtr(ctx.readPointer()),
      scalar_base: hexPtr(ctx.add(8).readPointer()),
      obj_index_base: hexPtr(ctx.add(16).readPointer()),
      obj_flag_base: hexPtr(ctx.add(24).readPointer()),
      obj_table_begin: hexPtr(ctx.add(32).readPointer()),
      obj_table_end: hexPtr(ctx.add(40).readPointer()),
    };
  } catch (e) {
    return { ctx: hexPtr(ctx), error: String(e) };
  }
}

function readCtxSnapshot(ctx) {
  ctx = ptrOrNull(ctx);
  const layout = readCtxLayout(ctx);
  const out = { layout };
  try {
    const scalar = ctx.add(8).readPointer();
    const objIndex = ctx.add(16).readPointer();
    const flags = ctx.add(24).readPointer();
    const tableBegin = ctx.add(32).readPointer();
    const tableEnd = ctx.add(40).readPointer();
    out.slots_u64 = [];
    out.obj_indices = [];
    out.obj_flags_hex = dumpHex(flags, SNAPSHOT_SLOTS, SNAPSHOT_SLOTS);
    for (let i = 0; i < SNAPSHOT_SLOTS; i++) {
      try { out.slots_u64.push(scalar.add(8 * i).readU64().toString()); } catch (_) { out.slots_u64.push(null); }
      try { out.obj_indices.push(objIndex.add(8 * i).readU64().toString()); } catch (_) { out.obj_indices.push(null); }
    }
    const count = Math.min(Number(tableEnd.sub(tableBegin).toInt32() / 8), SNAPSHOT_OBJECTS);
    out.object_table_count = count;
    out.objects = [];
    for (let i = 0; i < count; i++) {
      try {
        const objp = tableBegin.add(8 * i).readPointer();
        out.objects.push(readNativeObject(objp));
      } catch (e) {
        out.objects.push({ error: String(e) });
      }
    }
  } catch (e) {
    out.error = String(e);
  }
  return out;
}

function isLikelyLLProgram(program) {
  const head = dumpHex(program, 16, 16);
  return head === '35000000000000000000000000000000';
}

function regs(ctx) {
  const names = ['rax','rbx','rcx','rdx','rsi','rdi','rbp','rsp','r8','r9','r10','r11','r12','r13','r14','r15'];
  const o = {};
  for (const n of names) o[n] = hexPtr(ctx[n]);
  return o;
}

function installHooks(mod) {
  modBase = mod.base;
  jlog({ event: 'install_deep_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  Interceptor.attach(mod.base.add(OFF.sub_5B7D5DC), {
    onEnter(args) {
      const fmt = readCStringSafe(args[0], 8);
      const arg0 = readArgBlock(args[1]);
      this.isLL = fmt === 'LL' && arg0 && arg0.len === 20;
      if (this.isLL) {
        llLauncherDepth++;
        activeSampleId++;
        resolveLogs = 0;
        bindLogs = 0;
        labelLogs = 0;
        jlog({ event: 'deep_enter_LL_launcher', sample_id: activeSampleId, format: fmt, arg0 });
      }
    },
    onLeave(retval) {
      if (this.isLL) {
        jlog({ event: 'deep_leave_LL_launcher', sample_id: activeSampleId, result: readNativeResult(retval) });
        llLauncherDepth = Math.max(0, llLauncherDepth - 1);
      }
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B64F10), {
    onEnter(args) {
      this.ctx = ptr(args[0]);
      this.program = this.ctx.readPointer();
      this.isLL = llLauncherDepth > 0 && isLikelyLLProgram(this.program);
      if (this.isLL) {
        activeVmDepth++;
        activeCtx = this.ctx;
        activeProgram = this.program;
        jlog({ event: 'deep_enter_LL_VM', sample_id: activeSampleId, ctx: hexPtr(this.ctx), program: hexPtr(this.program), snapshot: readCtxSnapshot(this.ctx) });
      }
    },
    onLeave(retval) {
      if (this.isLL) {
        jlog({ event: 'deep_leave_LL_VM', sample_id: activeSampleId, result: readNativeResult(retval), snapshot: readCtxSnapshot(this.ctx) });
        activeVmDepth = Math.max(0, activeVmDepth - 1);
        if (activeVmDepth === 0) { activeCtx = NULL; activeProgram = NULL; }
      }
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B62E30), {
    onEnter(args) {
      this.enabled = activeVmDepth > 0 && resolveLogs < MAX_RESOLVE_LOGS;
      if (!this.enabled) return;
      this.vmctx = ptr(args[0]);
      this.slot = Number(args[1]);
      this.caller = this.returnAddress;
    },
    onLeave(retval) {
      if (!this.enabled) return;
      resolveLogs++;
      jlog({
        event: 'vm_resolve_object',
        sample_id: activeSampleId,
        n: resolveLogs,
        caller: hexPtr(this.caller),
        caller_off: rel(this.caller),
        ctx_arg: hexPtr(this.vmctx),
        slot: this.slot,
        object: readNativeObject(retval),
      });
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B63780), {
    onEnter(args) {
      this.enabled = activeVmDepth > 0 && bindLogs < MAX_BIND_LOGS;
      if (!this.enabled) return;
      this.ctx = ptr(args[0]);
      this.slot = Number(args[1]);
      this.obj = ptr(args[2]);
      this.a4 = args[3];
      this.caller = this.returnAddress;
      bindLogs++;
      jlog({
        event: 'vm_bind_object_enter',
        sample_id: activeSampleId,
        n: bindLogs,
        caller: hexPtr(this.caller),
        caller_off: rel(this.caller),
        ctx: hexPtr(this.ctx),
        slot: this.slot,
        a4: hexPtr(this.a4),
        object: readNativeObject(this.obj),
      });
    },
    onLeave(_) {
      if (!this.enabled) return;
      jlog({ event: 'vm_bind_object_leave', sample_id: activeSampleId, n: bindLogs, slot: this.slot, snapshot_brief: readCtxSnapshot(this.ctx) });
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B749DE), {
    onEnter(args) {
      this.enabled = activeVmDepth > 0 && bindLogs < MAX_BIND_LOGS;
      if (!this.enabled) return;
      this.ctx = ptr(args[0]);
      this.obj = ptr(args[1]);
      this.outIndexPtr = ptr(args[2]);
      this.caller = this.returnAddress;
    },
    onLeave(_) {
      if (!this.enabled) return;
      let idx = null;
      try { idx = this.outIndexPtr.readU64().toString(); } catch (_) {}
      jlog({ event: 'vm_object_table_index', sample_id: activeSampleId, caller_off: rel(this.caller), object: readNativeObject(this.obj), index: idx });
    }
  });

  for (const [name, off] of Object.entries(LABELS)) {
    Interceptor.attach(mod.base.add(off), {
      onEnter() {
        if (activeVmDepth <= 0 || labelLogs >= MAX_LABEL_LOGS) return;
        labelLogs++;
        // Register dumps let us reconstruct exact operands for the most useful
        // labels after looking at the nearby native disassembly.
        jlog({ event: 'vm_label_hit', sample_id: activeSampleId, n: labelLogs, label: name, off: '0x' + off.toString(16), regs: regs(this.context) });
      }
    });
  }
}

function waitForModule(moduleName, callback) {
  const seen = new Set();
  function tryInstall() {
    const mod = Process.findModuleByName(moduleName);
    if (!mod) return false;
    const key = mod.base.toString();
    if (seen.has(key)) return true;
    seen.add(key);
    callback(mod);
    return true;
  }
  if (tryInstall()) return;
  const timer = setInterval(function () { if (tryInstall()) clearInterval(timer); }, 250);
}

jlog({ event: 'deep_script_loaded', pid: Process.id, arch: Process.arch, platform: Process.platform });
waitForModule(TARGET_MODULE, installHooks);
