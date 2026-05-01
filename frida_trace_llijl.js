// Trace the sub_5B6D9EB -> LLIJL layer used by VM_PROGRAM_MAIN.
// Read-only. No patches.

'use strict';

const TARGET_MODULE = 'wrapper.node';
const MAX_DUMP = 4096;

const OFF = {
  sub_5B62121: 0x5B62121,
  sub_5B6D9EB: 0x5B6D9EB,
  sub_5B61D31: 0x5B61D31,
  sub_5B6CFF4: 0x5B6CFF4,
  sub_5B7D768: 0x5B7D768,
};

function now() { return (new Date()).toISOString(); }
function jlog(obj) { obj.ts = now(); console.log(JSON.stringify(obj)); }
function hexPtr(p) { try { return ptr(p).toString(); } catch (_) { return String(p); } }

function dumpHex(p, len, maxLen) {
  if (!p || p.isNull()) return null;
  const n = Math.max(0, Math.min(Number(len), maxLen || MAX_DUMP));
  try {
    const ab = p.readByteArray(n);
    if (ab === null) return null;
    const u = new Uint8Array(ab);
    let s = '';
    for (let i = 0; i < u.length; i++) s += ('0' + u[i].toString(16)).slice(-2);
    return s;
  } catch (e) { return 'READ_ERROR:' + e; }
}

function readCStringSafe(p, maxLen) {
  if (!p || p.isNull()) return null;
  try { return p.readCString(maxLen || 512); } catch (e) { return 'CSTR_ERROR:' + e; }
}

function readStdString(sp) {
  if (!sp || sp.isNull()) return { ptr: hexPtr(sp), error: 'null' };
  try {
    const data = sp.readPointer();
    const len = Number(sp.add(8).readU64());
    const sane = len >= 0 && len <= 0x100000;
    return {
      ptr: hexPtr(sp),
      data_ptr: hexPtr(data),
      len,
      hex: sane ? dumpHex(data, len, MAX_DUMP) : null,
      text: sane ? readCStringSafe(data, Math.min(len + 1, 512)) : null,
    };
  } catch (e) { return { ptr: hexPtr(sp), error: String(e) }; }
}

// NativeResult recovered layout: +0 uint32 len, +8 data ptr.
function readNativeResult(rp) {
  if (!rp || rp.isNull()) return { ptr: hexPtr(rp), null: true };
  try {
    const len = rp.readU32();
    const data = rp.add(8).readPointer();
    return { ptr: hexPtr(rp), len, data_ptr: hexPtr(data), data_hex: dumpHex(data, len, MAX_DUMP) };
  } catch (e) { return { ptr: hexPtr(rp), error: String(e) }; }
}

function addHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', name, addr: hexPtr(addr), base: hexPtr(mod.base) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function install(mod) {
  jlog({ event: 'install_llijl_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_5B62121', {
    onEnter(args) {
      this.module_id = readStdString(ptr(args[0]));
      this.digest_ptr = ptr(args[1]);
      this.digest_len = Number(args[2]);
      this.extra_ptr = ptr(args[3]);
      this.extra_len = Number(args[4]);
      jlog({
        event: 'enter_sub_5B62121',
        module_id: this.module_id,
        digest_len: this.digest_len,
        digest_hex: dumpHex(this.digest_ptr, this.digest_len, 64),
        extra_len: this.extra_len,
        extra_hex: dumpHex(this.extra_ptr, this.extra_len, MAX_DUMP),
      });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B62121', result: readNativeResult(ptr(retval)) }); }
  });

  addHook(mod, 'sub_5B6D9EB', {
    onEnter(args) {
      this.i1 = ptr(args[0]);
      this.n = Number(args[3]);
      jlog({
        event: 'enter_sub_5B6D9EB',
        i1: hexPtr(this.i1),
        i1_head_hex: dumpHex(this.i1, 64, 64),
        a2_scalar: Number(args[1]) >>> 0,
        a3: hexPtr(args[2]),
        n: this.n,
        mode: Number(args[4]) >>> 0,
        a6: hexPtr(args[5]),
        a7: hexPtr(args[6]),
        p_n: hexPtr(args[7]),
        a9: hexPtr(args[8]),
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B6D9EB', retval: hexPtr(retval), i1_head_hex: dumpHex(this.i1, 64, 64) });
    }
  });

  // sub_5B61D31(src_1/key, n8, salt_or_nonce, src, src_len) -> NativeResult*
  addHook(mod, 'sub_5B61D31', {
    onEnter(args) {
      this.key = ptr(args[0]);
      this.n8 = Number(args[1]);
      this.a3 = ptr(args[2]);
      this.src = ptr(args[3]);
      this.src_len = Number(args[4]);
      jlog({
        event: 'enter_sub_5B61D31',
        key_ptr: hexPtr(this.key),
        n8: this.n8,
        key_hex: dumpHex(this.key, this.n8, 64),
        a3: hexPtr(this.a3),
        src_ptr: hexPtr(this.src),
        src_len: this.src_len,
        src_hex: dumpHex(this.src, this.src_len, MAX_DUMP),
      });
    },
    onLeave(retval) { jlog({ event: 'leave_sub_5B61D31', result: readNativeResult(ptr(retval)) }); }
  });

  // sub_5B6CFF4(out_state, key32, a3, a4) ChaCha-like block helper.
  addHook(mod, 'sub_5B6CFF4', {
    onEnter(args) {
      this.out = ptr(args[0]);
      this.key = ptr(args[1]);
      jlog({
        event: 'enter_sub_5B6CFF4',
        out: hexPtr(this.out),
        key_ptr: hexPtr(this.key),
        key32_hex: dumpHex(this.key, 32, 32),
        a3: hexPtr(args[2]),
        a4: hexPtr(args[3]),
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B6CFF4', retval: hexPtr(retval), out128_hex: dumpHex(this.out, 128, 128) });
    }
  });

  addHook(mod, 'sub_5B7D768', {
    onEnter(args) {
      const input = ptr(args[0]);
      const n = Number(args[1]);
      jlog({ event: 'enter_sub_5B7D768', input_ptr: hexPtr(input), n, input_hex: dumpHex(input, n, 64) });
    }
  });
}

const mod = Process.findModuleByName(TARGET_MODULE);
if (!mod) jlog({ event: 'module_not_found', module: TARGET_MODULE });
else install(mod);
