// Frida 17 safe sampler for wrapper.node final "LL" VM.
//
// This version intentionally hooks only function entry/return addresses, not
// internal basic-block labels. The previous deep script can crash QQ because
// patching flattened-interpreter mid-block addresses is unsafe.
//
// Usage:
//   frida -p <QQ_PID> -l frida_trace_ll_safe.js -o ll_safe_trace.jsonl
//
// WARNING: attaching Frida can change the native anti-tamper/environment path.
// Treat final returned `data_hex` values as contaminated research samples, not
// byte-identical ground truth.  Use this script only for opcode/helper recovery
// hints unless a separate clean validation channel confirms the same output.

'use strict';

const TRACE_TARGET_MODULE = 'wrapper.node';

const OFF = {
  sub_5B62E30: 0x5B62E30,   // object slot resolver
  sub_5B63780: 0x5B63780,   // bind object to VM slot
  sub_5B64F10: 0x5B64F10,   // VM interpreter
  sub_5B749DE: 0x5B749DE,   // object table find/append
  sub_5B7D5DC: 0x5B7D5DC,   // final LL launcher
};

const SNAPSHOT_SLOTS = 64;
const SNAPSHOT_OBJECTS = 80;
const MAX_BYTES = 256;
const MAX_RESOLVE_LOGS = 3000;
const MAX_BIND_LOGS = 1000;

let llDepth = 0;
let vmDepth = 0;
let sampleId = 0;
let resolveCount = 0;
let bindCount = 0;
let indexCount = 0;

function now() { return (new Date()).toISOString(); }
function jlog(obj) { obj.ts = now(); console.log(JSON.stringify(obj)); }
function hexPtr(p) { try { return ptr(p).toString(); } catch (_) { return String(p); } }

function dumpHex(p, len, maxLen) {
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
  if (!p || p.isNull()) return null;
  try { return p.readCString(maxLen || 128); } catch (e) { return 'CSTR_ERROR:' + e; }
}

function readArgBlock(ap) {
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
  if (!rp || rp.isNull()) return { ptr: hexPtr(rp), null: true };
  try {
    const len = rp.readU32();
    const data = rp.add(8).readPointer();
    return { ptr: hexPtr(rp), len, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, 4096) };
  } catch (e) {
    return { ptr: hexPtr(rp), error: String(e) };
  }
}

function readNativeObject(op) {
  if (!op || op.isNull()) return { ptr: hexPtr(op), null: true };
  try {
    const len = op.readU32();
    const type = op.add(4).readU16();
    const data = op.add(8).readPointer();
    return { ptr: hexPtr(op), len, type, data_ptr: hexPtr(data), data_head: dumpHex(data, Math.min(len, MAX_BYTES), MAX_BYTES) };
  } catch (e) {
    return { ptr: hexPtr(op), error: String(e) };
  }
}

function slotCtx(ctx) {
  // sub_5B64F10 receives the full VM context.  sub_5B62E30/sub_5B63780 operate
  // on the slot/object subcontext at ctx+8.
  return ctx.add(8);
}

function readCtxLayout(ctx) {
  if (!ctx || ctx.isNull()) return { ctx: hexPtr(ctx), null: true };
  try {
    const sc = slotCtx(ctx);
    return {
      ctx: hexPtr(ctx),
      program: hexPtr(ctx.readPointer()),
      slot_ctx: hexPtr(sc),
      scalar_base: hexPtr(sc.readPointer()),
      obj_index_base: hexPtr(sc.add(8).readPointer()),
      obj_flag_base: hexPtr(sc.add(16).readPointer()),
      obj_table_begin: hexPtr(sc.add(24).readPointer()),
      obj_table_end: hexPtr(sc.add(32).readPointer()),
    };
  } catch (e) {
    return { ctx: hexPtr(ctx), error: String(e) };
  }
}

function readCtxSnapshot(ctx) {
  const out = { layout: readCtxLayout(ctx) };
  try {
    const sc = slotCtx(ctx);
    const scalar = sc.readPointer();
    const objIndex = sc.add(8).readPointer();
    const flags = sc.add(16).readPointer();
    const tableBegin = sc.add(24).readPointer();
    const tableEnd = sc.add(32).readPointer();

    out.slots_u64_hex = [];
    out.slots_u32_hex = [];
    out.obj_indices = [];
    out.obj_flags_hex = dumpHex(flags, SNAPSHOT_SLOTS, SNAPSHOT_SLOTS);

    for (let i = 0; i < SNAPSHOT_SLOTS; i++) {
      try { out.slots_u64_hex.push(scalar.add(8 * i).readU64().toString(16)); } catch (_) { out.slots_u64_hex.push(null); }
      try { out.slots_u32_hex.push(scalar.add(8 * i).readU32().toString(16)); } catch (_) { out.slots_u32_hex.push(null); }
      try { out.obj_indices.push(objIndex.add(8 * i).readU64().toString()); } catch (_) { out.obj_indices.push(null); }
    }

    let count = 0;
    try { count = Number(tableEnd.sub(tableBegin)) / 8; } catch (_) { count = 0; }
    count = Math.max(0, Math.min(count | 0, SNAPSHOT_OBJECTS));
    out.object_table_count = count;
    out.objects = [];
    for (let i = 0; i < count; i++) {
      try { out.objects.push(readNativeObject(tableBegin.add(8 * i).readPointer())); }
      catch (e) { out.objects.push({ error: String(e) }); }
    }
  } catch (e) {
    out.error = String(e);
  }
  return out;
}

function isLLProgram(program) {
  return dumpHex(program, 16, 16) === '35000000000000000000000000000000';
}

function installHooks(mod) {
  jlog({ event: 'install_safe_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  Interceptor.attach(mod.base.add(OFF.sub_5B7D5DC), {
    onEnter(args) {
      const fmt = readCStringSafe(args[0], 8);
      const arg0 = readArgBlock(args[1]);
      // The observed format pointer is not a clean NUL-terminated "LL" string;
      // boundary traces showed values like "LL�Bad escape se".  Treat any
      // string starting with "LL" plus a 20-byte first ArgBlock as the final
      // tail VM launcher.
      this.isLL = !!fmt && fmt.indexOf('LL') === 0 && arg0 && arg0.len === 20;
      if (this.isLL) {
        sampleId++;
        llDepth++;
        resolveCount = 0;
        bindCount = 0;
        indexCount = 0;
        jlog({ event: 'safe_enter_LL_launcher', sample_id: sampleId, format: fmt, arg0 });
      }
    },
    onLeave(retval) {
      if (this.isLL) {
        jlog({ event: 'safe_leave_LL_launcher', sample_id: sampleId, result: readNativeResult(retval) });
        llDepth = Math.max(0, llDepth - 1);
      }
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B64F10), {
    onEnter(args) {
      this.ctx = ptr(args[0]);
      this.program = this.ctx.readPointer();
      this.isLL = llDepth > 0 && isLLProgram(this.program);
      if (this.isLL) {
        vmDepth++;
        jlog({ event: 'safe_enter_LL_VM', sample_id: sampleId, ctx: hexPtr(this.ctx), program: hexPtr(this.program), snapshot: readCtxSnapshot(this.ctx) });
      }
    },
    onLeave(retval) {
      if (this.isLL) {
        jlog({ event: 'safe_leave_LL_VM', sample_id: sampleId, result: readNativeResult(retval), snapshot: readCtxSnapshot(this.ctx) });
        vmDepth = Math.max(0, vmDepth - 1);
      }
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B62E30), {
    onEnter(args) {
      this.enabled = vmDepth > 0 && resolveCount < MAX_RESOLVE_LOGS;
      if (!this.enabled) return;
      this.slot = Number(args[1]);
      this.caller = this.returnAddress;
    },
    onLeave(retval) {
      if (!this.enabled) return;
      resolveCount++;
      jlog({ event: 'safe_resolve_object', sample_id: sampleId, n: resolveCount, caller: hexPtr(this.caller), slot: this.slot, object: readNativeObject(retval) });
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B63780), {
    onEnter(args) {
      this.enabled = vmDepth > 0 && bindCount < MAX_BIND_LOGS;
      if (!this.enabled) return;
      bindCount++;
      this.slot = Number(args[1]);
      this.obj = ptr(args[2]);
      this.caller = this.returnAddress;
      jlog({ event: 'safe_bind_object', sample_id: sampleId, n: bindCount, caller: hexPtr(this.caller), slot: this.slot, object: readNativeObject(this.obj) });
    }
  });

  Interceptor.attach(mod.base.add(OFF.sub_5B749DE), {
    onEnter(args) {
      this.enabled = vmDepth > 0 && indexCount < MAX_BIND_LOGS;
      if (!this.enabled) return;
      this.obj = ptr(args[1]);
      this.out = ptr(args[2]);
      this.caller = this.returnAddress;
    },
    onLeave(_) {
      if (!this.enabled) return;
      indexCount++;
      let idx = null;
      try { idx = this.out.readU64().toString(); } catch (_) {}
      jlog({ event: 'safe_object_table_index', sample_id: sampleId, n: indexCount, caller: hexPtr(this.caller), index: idx, object: readNativeObject(this.obj) });
    }
  });
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

jlog({ event: 'safe_script_loaded', pid: Process.id, arch: Process.arch, platform: Process.platform });
waitForModule(TRACE_TARGET_MODULE, installHooks);
