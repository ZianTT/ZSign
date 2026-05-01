// Activity + signing boundary trace for Linux QQ.
// Purpose: distinguish "QQ has no activity" from "activity does not hit the
// recovered wrapper signing chain".
//
// Safe hooks only:
//   - libc/libssl exported function entries (connect/send/write/SSL_write)
//   - wrapper.node function boundaries
// No internal instruction hooks, no patching.

'use strict';

const TARGET_MODULE = 'wrapper.node';
const MAX_DUMP = 256;
const MAX_NET_DUMP = 96;
const MAX_NET_EVENTS = 200;

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
let wrapperInstalled = false;
let netEvents = 0;

function now() { return (new Date()).toISOString(); }
function jlog(obj) { obj.seq = ++seq; obj.ts = now(); console.log(JSON.stringify(obj)); }
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
  if (!sp || sp.isNull()) return { ptr: hexPtr(sp), error: 'null' };
  try {
    const p = ptr(sp);
    const data = p.readPointer();
    const len = Number(p.add(8).readU64());
    const sane = len >= 0 && len <= 0x10000;
    return { ptr: hexPtr(p), data_ptr: hexPtr(data), len, hex: sane ? dumpHex(data, len, MAX_DUMP) : null, text: sane ? readUtf8Safe(data, len) : null, truncated: sane && len > MAX_DUMP };
  } catch (e) { return { ptr: hexPtr(sp), error: String(e) }; }
}
function readNativeResult(rp) {
  if (!rp || rp.isNull()) return { ptr: hexPtr(rp), null: true };
  try {
    const p = ptr(rp);
    const len = p.readU32();
    const data = p.add(8).readPointer();
    return { ptr: hexPtr(p), len, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, MAX_DUMP), truncated: len > MAX_DUMP };
  } catch (e) { return { ptr: hexPtr(rp), error: String(e) }; }
}
function readArgBlock(ap) {
  if (!ap || ap.isNull()) return { ptr: hexPtr(ap), null: true };
  try {
    const p = ptr(ap);
    const len = p.readU32();
    const type = p.add(4).readU16();
    const data = p.add(8).readPointer();
    return { ptr: hexPtr(p), len, type, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, MAX_DUMP), truncated: len > MAX_DUMP };
  } catch (e) { return { ptr: hexPtr(ap), error: String(e) }; }
}

function sockaddrInfo(sa) {
  try {
    const p = ptr(sa);
    const fam = p.readU16();
    if (fam === 2) { // AF_INET, little-endian family in memory; port is network byte order
      const portBE = p.add(2).readU16();
      const port = ((portBE & 0xff) << 8) | (portBE >> 8);
      const b = new Uint8Array(p.add(4).readByteArray(4));
      return { family: 'AF_INET', ip: `${b[0]}.${b[1]}.${b[2]}.${b[3]}`, port };
    }
    if (fam === 10) {
      const portBE = p.add(2).readU16();
      const port = ((portBE & 0xff) << 8) | (portBE >> 8);
      return { family: 'AF_INET6', port, raw: dumpHex(p, 28, 28) };
    }
    return { family: fam, raw: dumpHex(p, 32, 32) };
  } catch (e) { return { error: String(e) }; }
}

function addWrapperHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked_wrapper', name, base: hexPtr(mod.base), addr: hexPtr(addr) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function installWrapperHooks(mod) {
  if (wrapperInstalled) return;
  wrapperInstalled = true;
  jlog({ event: 'install_wrapper_hooks', pid: Process.id, module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addWrapperHook(mod, 'sub_55658EF', {
    onEnter(args) { jlog({ event: 'enter_sub_55658EF', tid: Process.getCurrentThreadId(), args: [0,1,2,3,4,5].map(i => hexPtr(args[i])) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_55658EF', tid: Process.getCurrentThreadId(), retval: hexPtr(retval) }); }
  });
  addWrapperHook(mod, 'sub_5B62121', {
    onEnter(args) { jlog({ event: 'enter_sub_5B62121', tid: Process.getCurrentThreadId(), module_id: readStdString(args[0]), digest_len: Number(args[2]), digest_hex: dumpHex(ptr(args[1]), Number(args[2]), 64), extra_len: Number(args[4]), extra_hex: dumpHex(ptr(args[3]), Number(args[4]), MAX_DUMP) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B62121', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  addWrapperHook(mod, 'sub_5B64F10', {
    onEnter(args) { this.ctx = ptr(args[0]); this.program = NULL; try { this.program = this.ctx.readPointer(); } catch (_) {} jlog({ event: 'enter_sub_5B64F10', tid: Process.getCurrentThreadId(), ctx: hexPtr(this.ctx), program_ptr: hexPtr(this.program), program_head_hex: dumpHex(this.program, 32, 32) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B64F10', tid: Process.getCurrentThreadId(), program_ptr: hexPtr(this.program), result: readNativeResult(retval) }); }
  });
  addWrapperHook(mod, 'sub_5B6D9EB', {
    onEnter(args) { jlog({ event: 'enter_sub_5B6D9EB', tid: Process.getCurrentThreadId(), scalar: Number(args[1]) >>> 0, n: Number(args[3]), mode: Number(args[4]) >>> 0, a6: hexPtr(args[5]), a6_hex: dumpHex(ptr(args[5]), 32, 32), p_n: hexPtr(args[7]), p_n_hex: dumpHex(ptr(args[7]), 32, 32), salt: hexPtr(args[8]) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B6D9EB', tid: Process.getCurrentThreadId(), retval: hexPtr(retval) }); }
  });
  addWrapperHook(mod, 'sub_5B61D31', {
    onEnter(args) { const n8 = Number(args[1]); const srcLen = Number(args[4]); jlog({ event: 'enter_sub_5B61D31', tid: Process.getCurrentThreadId(), key_hex: dumpHex(ptr(args[0]), n8, 64), n8, salt: hexPtr(args[2]), src_len: srcLen, src_hex: dumpHex(ptr(args[3]), srcLen, 64) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B61D31', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  addWrapperHook(mod, 'sub_5B7D768', {
    onEnter(args) { const input = ptr(args[0]); const n = Number(args[1]); jlog({ event: 'enter_sub_5B7D768', tid: Process.getCurrentThreadId(), input_ptr: hexPtr(input), n, input_hex: dumpHex(input, n, MAX_DUMP), input_minus2_21_hex: dumpHex(input.sub(2), 21, 64) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B7D768', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
  addWrapperHook(mod, 'sub_5B7D5DC', {
    onEnter(args) { jlog({ event: 'enter_sub_5B7D5DC', tid: Process.getCurrentThreadId(), format: readCStringSafe(args[0], 16), arg0: readArgBlock(args[1]) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5B7D5DC', tid: Process.getCurrentThreadId(), result: readNativeResult(retval) }); }
  });
}

function hookExport(name, retType, argTypes, onEnterFn) {
  let addr = null;
  try { addr = Module.getGlobalExportByName(name); } catch (_) {}
  if (!addr) { jlog({ event: 'net_export_missing', name }); return; }
  try {
    Interceptor.attach(addr, { onEnter: onEnterFn });
    jlog({ event: 'hooked_net', name, addr: hexPtr(addr) });
  } catch (e) { jlog({ event: 'net_hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function maybeNetLog(obj) {
  if (netEvents >= MAX_NET_EVENTS) return;
  netEvents += 1;
  jlog(obj);
}

function installNetworkHooks() {
  hookExport('connect', 'int', [], function (args) {
    maybeNetLog({ event: 'net_connect', tid: Process.getCurrentThreadId(), fd: Number(args[0]), sockaddr: sockaddrInfo(args[1]), addrlen: Number(args[2]) });
  });
  hookExport('send', 'ssize_t', [], function (args) {
    maybeNetLog({ event: 'net_send', tid: Process.getCurrentThreadId(), fd: Number(args[0]), len: Number(args[2]), data_hex: dumpHex(ptr(args[1]), Number(args[2]), MAX_NET_DUMP) });
  });
  hookExport('write', 'ssize_t', [], function (args) {
    const len = Number(args[2]);
    if (len > 0) maybeNetLog({ event: 'net_write', tid: Process.getCurrentThreadId(), fd: Number(args[0]), len, data_hex: dumpHex(ptr(args[1]), len, MAX_NET_DUMP) });
  });
  hookExport('SSL_write', 'int', [], function (args) {
    maybeNetLog({ event: 'net_SSL_write', tid: Process.getCurrentThreadId(), ssl: hexPtr(args[0]), len: Number(args[2]), data_hex: dumpHex(ptr(args[1]), Number(args[2]), MAX_NET_DUMP) });
  });
}

function pollWrapper() {
  if (wrapperInstalled) return;
  const mod = Process.findModuleByName(TARGET_MODULE);
  if (mod) installWrapperHooks(mod);
}

jlog({ event: 'activity_safe_loaded', pid: Process.id });
installNetworkHooks();
pollWrapper();
const timer = setInterval(() => { pollWrapper(); if (wrapperInstalled) clearInterval(timer); }, 50);
