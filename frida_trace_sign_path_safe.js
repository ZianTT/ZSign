// Safe upper-level signing path trace.
// Function-entry hooks only; no internal instruction hooks and no complex C++
// return-object parsing. Use this to discover which signing path is active.

'use strict';

const TARGET_MODULE = 'wrapper.node';
const OFF = {
  sub_5B62121: 0x5B62121,
  sub_5B6D9EB: 0x5B6D9EB,
  sub_5B61D31: 0x5B61D31,
  sub_5B7D768: 0x5B7D768,
  sub_5B7D5DC: 0x5B7D5DC,
};

let installed = false;
function now() { return (new Date()).toISOString(); }
function jlog(obj) { obj.ts = now(); console.log(JSON.stringify(obj)); }
function hexPtr(p) { try { return ptr(p).toString(); } catch (_) { return String(p); } }
function dumpHex(p, len, maxLen) {
  if (!p || p.isNull()) return null;
  const n = Math.max(0, Math.min(Number(len), maxLen || 128));
  try {
    const ab = p.readByteArray(n);
    if (ab === null) return null;
    const u = new Uint8Array(ab);
    let s = '';
    for (let i = 0; i < u.length; i++) s += ('0' + u[i].toString(16)).slice(-2);
    return s;
  } catch (e) { return 'READ_ERROR:' + e; }
}
function dumpUtf8(p, len) {
  if (!p || p.isNull()) return null;
  try { return ptr(p).readUtf8String(Math.min(Number(len) || 0, 128)); }
  catch (e) { return 'READ_ERROR:' + e; }
}
function stdStringInfo(p) {
  try {
    const pp = ptr(p);
    const data = pp.readPointer();
    const len = pp.add(8).readU64().toNumber();
    return { ptr: hexPtr(data), len, hex: dumpHex(data, len, 64), utf8: dumpUtf8(data, len) };
  } catch (e) { return { error: String(e) }; }
}
function addHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', name, addr: hexPtr(addr), base: hexPtr(mod.base) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}
function install(mod) {
  if (installed) return;
  installed = true;
  jlog({ event: 'install_sign_path_safe_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_5B62121', {
    onEnter(args) {
      jlog({
        event: 'enter_sub_5B62121', tid: Process.getCurrentThreadId(),
        module_id: stdStringInfo(args[0]),
        digest_ptr: hexPtr(args[1]), digest_len: Number(args[2]), digest_hex: dumpHex(ptr(args[1]), Number(args[2]), 64),
        extra_ptr: hexPtr(args[3]), extra_len: Number(args[4]), extra_hex: dumpHex(ptr(args[3]), Number(args[4]), 64),
      });
    }
  });
  addHook(mod, 'sub_5B6D9EB', {
    onEnter(args) {
      jlog({ event: 'enter_sub_5B6D9EB', tid: Process.getCurrentThreadId(), scalar: Number(args[1]) >>> 0, n: Number(args[3]), mode: Number(args[4]) >>> 0, salt: hexPtr(args[8]) });
    }
  });
  addHook(mod, 'sub_5B61D31', {
    onEnter(args) {
      jlog({ event: 'enter_sub_5B61D31', tid: Process.getCurrentThreadId(), key_hex: dumpHex(ptr(args[0]), Number(args[1]), 64), n8: Number(args[1]), salt: hexPtr(args[2]), src_len: Number(args[4]), src_hex: dumpHex(ptr(args[3]), Number(args[4]), 64) });
    }
  });
  addHook(mod, 'sub_5B7D768', {
    onEnter(args) {
      const n = Number(args[1]);
      jlog({ event: 'enter_sub_5B7D768', tid: Process.getCurrentThreadId(), input_ptr: hexPtr(args[0]), n, input_hex: dumpHex(ptr(args[0]), n, 64) });
    }
  });
  addHook(mod, 'sub_5B7D5DC', {
    onEnter(args) {
      jlog({ event: 'enter_sub_5B7D5DC', tid: Process.getCurrentThreadId(), format_ptr: hexPtr(args[0]), format: dumpUtf8(ptr(args[0]), 8) });
    }
  });
}
function poll() {
  if (installed) return;
  const mod = Process.findModuleByName(TARGET_MODULE);
  if (mod) install(mod);
}
jlog({ event: 'sign_path_safe_loaded', pid: Process.id });
poll();
const timer = setInterval(() => { poll(); if (installed) clearInterval(timer); }, 50);
