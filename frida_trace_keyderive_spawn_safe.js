// Spawn-safe boundary trace. Load at process start; poll until wrapper.node is
// loaded, then install only safe function-boundary hooks.

'use strict';

const TARGET_MODULE = 'wrapper.node';
const OFF = {
  sub_5B6D9EB: 0x5B6D9EB,
  sub_5B61D31: 0x5B61D31,
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

function addHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', name, addr: hexPtr(addr), base: hexPtr(mod.base) });
  } catch (e) {
    jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) });
  }
}

function install(mod) {
  if (installed) return;
  installed = true;
  jlog({ event: 'install_keyderive_spawn_safe_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_5B6D9EB', {
    onEnter(args) {
      this.tid = Process.getCurrentThreadId();
      jlog({
        event: 'enter_sub_5B6D9EB',
        tid: this.tid,
        i1: hexPtr(args[0]),
        scalar: Number(args[1]) >>> 0,
        n: Number(args[3]),
        mode: Number(args[4]) >>> 0,
        a6: hexPtr(args[5]),
        a6_hex: dumpHex(ptr(args[5]), 32, 32),
        a7: hexPtr(args[6]),
        p_n: hexPtr(args[7]),
        p_n_hex: dumpHex(ptr(args[7]), 32, 32),
        salt: hexPtr(args[8]),
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B6D9EB', tid: this.tid, retval: hexPtr(retval) });
    }
  });

  addHook(mod, 'sub_5B61D31', {
    onEnter(args) {
      jlog({
        event: 'enter_sub_5B61D31',
        tid: Process.getCurrentThreadId(),
        key_ptr: hexPtr(args[0]),
        n8: Number(args[1]),
        key_hex: dumpHex(ptr(args[0]), Number(args[1]), 64),
        salt: hexPtr(args[2]),
        src_ptr: hexPtr(args[3]),
        src_len: Number(args[4]),
        src_hex: dumpHex(ptr(args[3]), Number(args[4]), 64),
      });
    }
  });
}

function poll() {
  if (installed) return;
  const mod = Process.findModuleByName(TARGET_MODULE);
  if (mod) install(mod);
}

jlog({ event: 'spawn_safe_loaded', pid: Process.id });
poll();
const timer = setInterval(() => {
  poll();
  if (installed) clearInterval(timer);
}, 50);
