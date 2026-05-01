// Full safe signing trace for QQ wrapper.node.
// Frida 17 compatible. Function-boundary hooks only: no internal instruction
// hooks, no patching, no large stack-window dumps.
//
// Recommended attach:
//   frida -q -p <qq-main-pid> -l frida_trace_full_safe.js > full_safe_trace.jsonl
// Recommended spawn:
//   frida -q -f /opt/QQ/qq -l frida_trace_full_safe.js > full_safe_trace.jsonl

'use strict';

const TARGET_MODULE = 'wrapper.node';
const MAX_DUMP = 512;

const OFF = {
  sub_55658EF: 0x55658EF,   // high-level entry seen in old sign trace
  sub_5B62121: 0x5B62121,   // native_wrap_digest entry
  sub_5B64F10: 0x5B64F10,   // VM interpreter
  sub_5B6D9EB: 0x5B6D9EB,   // compound helper / key8 derivation caller
  sub_5B61D31: 0x5B61D31,   // LLIJL launcher
  sub_5B7D768: 0x5B7D768,   // final tail wrapper before LL VM
  sub_5B7D5DC: 0x5B7D5DC,   // nested VM launcher(format,...)
};

let installed = false;
let seq = 0;

function now() { return (new Date()).toISOString(); }
function nextSeq() { seq += 1; return seq; }
function jlog(obj) {
  obj.seq = nextSeq();
  obj.ts = now();
  console.log(JSON.stringify(obj));
}
function hexPtr(p) {
  if (p === null || p === undefined) return 'null';
  try { return ptr(p).toString(); } catch (_) { return String(p); }
}
function dumpHex(p, len, maxLen) {
  if (!p || p.isNull()) return null;
  const n = Math.max(0, Math.min(Number(len) || 0, maxLen || MAX_DUMP));
  if (n === 0) return '';
  try {
    const ab = ptr(p).readByteArray(n);
    if (ab === null) return null;
    const u = new Uint8Array(ab);
    let s = '';
    for (let i = 0; i < u.length; i++) s += ('0' + u[i].toString(16)).slice(-2);
    return s;
  } catch (e) { return 'READ_ERROR:' + e; }
}
function readCStringSafe(p, maxLen) {
  if (!p || p.isNull()) return null;
  try { return ptr(p).readCString(maxLen || 128); }
  catch (e) { return 'CSTR_ERROR:' + e; }
}
function readUtf8Safe(p, len) {
  if (!p || p.isNull()) return null;
  try { return ptr(p).readUtf8String(Math.min(Number(len) || 0, 256)); }
  catch (e) { return 'UTF8_ERROR:' + e; }
}

// Observed libstdc++ string layout: +0 data pointer, +8 length.
function readStdString(sp) {
  if (!sp || sp.isNull()) return { ptr: hexPtr(sp), error: 'null' };
  try {
    const p = ptr(sp);
    const data = p.readPointer();
    const len = Number(p.add(8).readU64());
    const sane = len >= 0 && len <= 0x10000;
    return {
      ptr: hexPtr(p), data_ptr: hexPtr(data), len,
      hex: sane ? dumpHex(data, len, MAX_DUMP) : null,
      text: sane ? readUtf8Safe(data, len) : null,
      truncated: sane && len > MAX_DUMP,
    };
  } catch (e) { return { ptr: hexPtr(sp), error: String(e) }; }
}

// NativeResult recovered layout: +0 u32 len, +8 data pointer.
function readNativeResult(rp) {
  if (!rp || rp.isNull()) return { ptr: hexPtr(rp), null: true };
  try {
    const p = ptr(rp);
    const len = p.readU32();
    const data = p.add(8).readPointer();
    return {
      ptr: hexPtr(p), len, data_ptr: hexPtr(data),
      data_hex: dumpHex(data, len, MAX_DUMP),
      truncated: len > MAX_DUMP,
    };
  } catch (e) { return { ptr: hexPtr(rp), error: String(e) }; }
}

// ArgBlock observed layout: +0 u32 len, +4 u16 type, +8 data pointer.
function readArgBlock(ap) {
  if (!ap || ap.isNull()) return { ptr: hexPtr(ap), null: true };
  try {
    const p = ptr(ap);
    const len = p.readU32();
    const type = p.add(4).readU16();
    const data = p.add(8).readPointer();
    return {
      ptr: hexPtr(p), len, type, data_ptr: hexPtr(data),
      data_hex: dumpHex(data, len, MAX_DUMP),
      truncated: len > MAX_DUMP,
    };
  } catch (e) { return { ptr: hexPtr(ap), error: String(e) }; }
}

function addHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', name, module: mod.name, base: hexPtr(mod.base), addr: hexPtr(addr) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function installHooks(mod) {
  if (installed) return;
  installed = true;
  jlog({ event: 'install_full_safe_hooks', pid: Process.id, module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_55658EF', {
    onEnter(args) {
      jlog({ event: 'enter_sub_55658EF', tid: Process.getCurrentThreadId(), args: [0,1,2,3,4,5].map(i => hexPtr(args[i])) });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_55658EF', tid: Process.getCurrentThreadId(), retval: hexPtr(retval) }); }
  });

  addHook(mod, 'sub_5B62121', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      this.module_id = readStdString(args[0]);
      this.digest_len = Number(args[2]);
      this.extra_len = Number(args[4]);
      jlog({
        event: 'enter_sub_5B62121', tid: this.tid,
        module_id: this.module_id,
        digest_ptr: hexPtr(args[1]), digest_len: this.digest_len, digest_hex: dumpHex(ptr(args[1]), this.digest_len, 64),
        extra_ptr: hexPtr(args[3]), extra_len: this.extra_len, extra_hex: dumpHex(ptr(args[3]), this.extra_len, MAX_DUMP),
      });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B62121', tid: this.tid, result: readNativeResult(retval) }); }
  });

  addHook(mod, 'sub_5B6D9EB', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      jlog({
        event: 'enter_sub_5B6D9EB', tid: this.tid,
        i1: hexPtr(args[0]), i1_head_hex: dumpHex(ptr(args[0]), 64, 64),
        scalar: Number(args[1]) >>> 0,
        a3: hexPtr(args[2]),
        n: Number(args[3]),
        mode: Number(args[4]) >>> 0,
        a6: hexPtr(args[5]), a6_hex: dumpHex(ptr(args[5]), 32, 32),
        a7: hexPtr(args[6]),
        p_n: hexPtr(args[7]), p_n_hex: dumpHex(ptr(args[7]), 32, 32),
        salt: hexPtr(args[8]),
      });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B6D9EB', tid: this.tid, retval: hexPtr(retval) }); }
  });

  addHook(mod, 'sub_5B61D31', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      const n8 = Number(args[1]);
      const srcLen = Number(args[4]);
      jlog({
        event: 'enter_sub_5B61D31', tid: this.tid,
        key_ptr: hexPtr(args[0]), n8, key_hex: dumpHex(ptr(args[0]), n8, 64),
        salt: hexPtr(args[2]),
        src_ptr: hexPtr(args[3]), src_len: srcLen, src_hex: dumpHex(ptr(args[3]), srcLen, 64),
      });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B61D31', tid: this.tid, result: readNativeResult(retval) }); }
  });

  addHook(mod, 'sub_5B7D768', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      this.input = ptr(args[0]);
      this.n = Number(args[1]);
      jlog({
        event: 'enter_sub_5B7D768', tid: this.tid,
        input_ptr: hexPtr(this.input), n: this.n,
        input_hex: dumpHex(this.input, this.n, MAX_DUMP),
        input_minus2_21_hex: dumpHex(this.input.sub(2), 21, 64),
      });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B7D768', tid: this.tid, result: readNativeResult(retval) }); }
  });

  addHook(mod, 'sub_5B7D5DC', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      jlog({ event: 'enter_sub_5B7D5DC', tid: this.tid, format_ptr: hexPtr(args[0]), format: readCStringSafe(args[0], 16), arg0: readArgBlock(args[1]) });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B7D5DC', tid: this.tid, result: readNativeResult(retval) }); }
  });

  addHook(mod, 'sub_5B64F10', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      this.ctx = ptr(args[0]);
      this.program = NULL;
      try { this.program = this.ctx.readPointer(); } catch (_) {}
      const head = dumpHex(this.program, 32, 32);
      jlog({ event: 'enter_sub_5B64F10', tid: this.tid, ctx: hexPtr(this.ctx), program_ptr: hexPtr(this.program), program_head_hex: head });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B64F10', tid: this.tid, program_ptr: hexPtr(this.program), result: readNativeResult(retval) }); }
  });
}

function pollModule() {
  if (installed) return;
  const mod = Process.findModuleByName(TARGET_MODULE);
  if (mod) installHooks(mod);
}

jlog({ event: 'full_safe_loaded', pid: Process.id, argv0: Process.argv ? Process.argv[0] : null });
pollModule();
const timer = setInterval(() => { pollModule(); if (installed) clearInterval(timer); }, 50);
