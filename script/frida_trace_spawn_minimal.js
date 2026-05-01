// Minimal spawn-safe wrapper.node trace.
// Designed to reduce Frida footprint / detection surface:
//   - no network hooks
//   - no internal instruction hooks
//   - no large stack dumps
//   - installs wrapper hooks only when wrapper.node is observed through dlopen
//
// Usage:
//   frida -q -f /opt/QQ/qq -l frida_trace_spawn_minimal.js > spawn_minimal_trace.jsonl

'use strict';

const TARGET = 'wrapper.node';
const MAX_DUMP = 256;
const OFF = {
  sub_55658EF: 0x55658EF,
  sub_5B62121: 0x5B62121,
  sub_5B64F10: 0x5B64F10,
  sub_5B6D9EB: 0x5B6D9EB,
  sub_5B61D31: 0x5B61D31,
  sub_5B7D768: 0x5B7D768,
  sub_5B7D5DC: 0x5B7D5DC,
};

let seq = 0;
let installed = false;

function now() { return (new Date()).toISOString(); }
function jlog(o) { o.seq = ++seq; o.ts = now(); console.log(JSON.stringify(o)); }
function hexPtr(p) { try { return ptr(p).toString(); } catch (_) { return String(p); } }
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
  try { return ptr(p).readCString(maxLen || 128); } catch (e) { return 'CSTR_ERROR:' + e; }
}
function readUtf8Safe(p, len) {
  if (!p || p.isNull()) return null;
  try { return ptr(p).readUtf8String(Math.min(Number(len) || 0, 256)); } catch (e) { return 'UTF8_ERROR:' + e; }
}
function readStdString(sp) {
  try {
    const p = ptr(sp);
    const data = p.readPointer();
    const len = Number(p.add(8).readU64());
    const sane = len >= 0 && len <= 0x10000;
    return { ptr: hexPtr(p), data_ptr: hexPtr(data), len, hex: sane ? dumpHex(data, len, MAX_DUMP) : null, text: sane ? readUtf8Safe(data, len) : null };
  } catch (e) { return { ptr: hexPtr(sp), error: String(e) }; }
}
function readNativeResult(rp) {
  try {
    const p = ptr(rp);
    const len = p.readU32();
    const data = p.add(8).readPointer();
    return { ptr: hexPtr(p), len, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, MAX_DUMP), truncated: len > MAX_DUMP };
  } catch (e) { return { ptr: hexPtr(rp), error: String(e) }; }
}
function readArgBlock(ap) {
  try {
    const p = ptr(ap);
    const len = p.readU32();
    const type = p.add(4).readU16();
    const data = p.add(8).readPointer();
    return { ptr: hexPtr(p), len, type, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, MAX_DUMP), truncated: len > MAX_DUMP };
  } catch (e) { return { ptr: hexPtr(ap), error: String(e) }; }
}

function addHook(mod, name, cb) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, cb);
    jlog({ event: 'hooked', name, base: hexPtr(mod.base), addr: hexPtr(addr) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function tryInstall(reason) {
  if (installed) return true;
  const mod = Process.findModuleByName(TARGET);
  if (!mod) return false;
  installed = true;
  jlog({ event: 'install_wrapper', reason, pid: Process.id, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_55658EF', {
    onEnter(args) { jlog({ event: 'enter_sub_55658EF', tid: Process.getCurrentThreadId(), args: [0,1,2,3,4,5].map(i => hexPtr(args[i])) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_55658EF', tid: Process.getCurrentThreadId(), retval: hexPtr(retval) }); }
  });
  addHook(mod, 'sub_5B62121', {
    onEnter(args) { jlog({ event: 'enter_sub_5B62121', tid: Process.getCurrentThreadId(), module_id: readStdString(args[0]), digest_len: Number(args[2]), digest_hex: dumpHex(ptr(args[1]), Number(args[2]), 64), extra_len: Number(args[4]), extra_hex: dumpHex(ptr(args[3]), Number(args[4]), MAX_DUMP) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B62121', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  addHook(mod, 'sub_5B64F10', {
    onEnter(args) { this.ctx = ptr(args[0]); this.program = NULL; try { this.program = this.ctx.readPointer(); } catch (_) {} jlog({ event: 'enter_sub_5B64F10', tid: Process.getCurrentThreadId(), program_ptr: hexPtr(this.program), program_head_hex: dumpHex(this.program, 32, 32) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B64F10', tid: Process.getCurrentThreadId(), program_ptr: hexPtr(this.program), result: readNativeResult(retval) }); }
  });
  addHook(mod, 'sub_5B6D9EB', {
    onEnter(args) { jlog({ event: 'enter_sub_5B6D9EB', tid: Process.getCurrentThreadId(), scalar: Number(args[1]) >>> 0, n: Number(args[3]), mode: Number(args[4]) >>> 0, a6: hexPtr(args[5]), a6_hex: dumpHex(ptr(args[5]), 32, 32), p_n: hexPtr(args[7]), p_n_hex: dumpHex(ptr(args[7]), 32, 32), salt: hexPtr(args[8]) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B6D9EB', tid: Process.getCurrentThreadId(), retval: hexPtr(retval) }); }
  });
  addHook(mod, 'sub_5B61D31', {
    onEnter(args) { const n8 = Number(args[1]); const srcLen = Number(args[4]); jlog({ event: 'enter_sub_5B61D31', tid: Process.getCurrentThreadId(), key_hex: dumpHex(ptr(args[0]), n8, 64), n8, salt: hexPtr(args[2]), src_len: srcLen, src_hex: dumpHex(ptr(args[3]), srcLen, 64) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B61D31', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  addHook(mod, 'sub_5B7D768', {
    onEnter(args) { const input = ptr(args[0]); const n = Number(args[1]); jlog({ event: 'enter_sub_5B7D768', tid: Process.getCurrentThreadId(), n, input_hex: dumpHex(input, n, MAX_DUMP), input_minus2_21_hex: dumpHex(input.sub(2), 21, 64) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B7D768', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  addHook(mod, 'sub_5B7D5DC', {
    onEnter(args) { jlog({ event: 'enter_sub_5B7D5DC', tid: Process.getCurrentThreadId(), format: readCStringSafe(args[0], 16), arg0: readArgBlock(args[1]) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B7D5DC', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  return true;
}

function hookDlopen(name) {
  let addr = null;
  try { addr = Module.getGlobalExportByName(name); } catch (_) {}
  if (!addr) { jlog({ event: 'dlopen_missing', name }); return; }
  try {
    Interceptor.attach(addr, {
      onEnter(args) {
        this.path = readCStringSafe(args[0], 512);
        if (this.path && this.path.indexOf(TARGET) !== -1) jlog({ event: 'dlopen_enter_wrapper', name, path: this.path });
      },
      onLeave(retval) {
        if (this.path && this.path.indexOf(TARGET) !== -1) {
          jlog({ event: 'dlopen_leave_wrapper', name, path: this.path, retval: hexPtr(retval) });
          tryInstall('dlopen:' + name);
        }
      }
    });
    jlog({ event: 'hooked_dlopen', name, addr: hexPtr(addr) });
  } catch (e) { jlog({ event: 'dlopen_hook_error', name, error: String(e) }); }
}

jlog({ event: 'spawn_minimal_loaded', pid: Process.id });
tryInstall('initial');
hookDlopen('dlopen');
hookDlopen('__libc_dlopen_mode');
hookDlopen('dlmopen');
// Low-frequency fallback in case module is mapped by a loader path not using exported dlopen.
let ticks = 0;
const timer = setInterval(function () {
  ticks += 1;
  if (tryInstall('timer')) clearInterval(timer);
  else if (ticks % 100 === 0) jlog({ event: 'waiting_wrapper', ticks });
  if (ticks > 2400) clearInterval(timer);
}, 50);
