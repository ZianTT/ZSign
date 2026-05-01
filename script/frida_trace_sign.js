// Frida 17 compatible trace script for Linux QQ host process / wrapper.node signing.
//
// Usage examples:
//   Local Linux attach by process name:
//     frida -n <QQ_PROCESS_NAME> -l frida_trace_sign.js -o sign_trace.jsonl
//
//   Local Linux attach by PID:
//     frida -p <PID> -l frida_trace_sign.js -o sign_trace.jsonl
//
//   Remote Linux frida-server, if the QQ host is on another machine/container:
//     frida -H <host>:27042 -p <PID> -l frida_trace_sign.js -o sign_trace.jsonl
//
// The script does not patch behavior. It only logs VM/signing boundaries needed
// for byte-for-byte comparison with the offline Python reconstruction.

'use strict';

const TARGET_MODULE = 'wrapper.node';
const MAX_DUMP = 4096;

const OFF = {
  sub_55658EF: 0x55658EF,
  sub_5B62121: 0x5B62121,
  sub_5B64F10: 0x5B64F10,
  sub_5B7D5DC: 0x5B7D5DC,
  sub_5B7D768: 0x5B7D768,
};

function now() {
  return (new Date()).toISOString();
}

function jlog(obj) {
  obj.ts = now();
  console.log(JSON.stringify(obj));
}

function hexPtr(p) {
  if (p === null || p === undefined) return 'null';
  try { return ptr(p).toString(); } catch (_) { return String(p); }
}

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
  } catch (e) {
    return 'READ_ERROR:' + e;
  }
}

function safeU32(p, off) {
  try { return p.add(off).readU32(); } catch (_) { return null; }
}

function safeU64Num(p, off) {
  try { return Number(p.add(off).readU64()); } catch (_) { return null; }
}

function safePtr(p, off) {
  try { return p.add(off).readPointer(); } catch (_) { return NULL; }
}

function readCStringSafe(p, maxLen) {
  if (!p || p.isNull()) return null;
  try { return p.readCString(maxLen || 512); } catch (e) { return 'CSTR_ERROR:' + e; }
}

// libstdc++ basic_string on the observed Linux build:
//   +0 data pointer
//   +8 length
//   +16 inline/capacity area
function readStdString(sp) {
  if (!sp || sp.isNull()) return { ptr: hexPtr(sp), error: 'null' };
  try {
    const data = sp.readPointer();
    const len = Number(sp.add(8).readU64());
    const sane = len >= 0 && len <= 0x100000;
    return {
      ptr: hexPtr(sp),
      data_ptr: hexPtr(data),
      len: len,
      hex: sane ? dumpHex(data, len, MAX_DUMP) : null,
      text: sane ? readCStringSafe(data, Math.min(len + 1, 512)) : null,
      truncated: sane && len > MAX_DUMP,
    };
  } catch (e) {
    return { ptr: hexPtr(sp), error: String(e) };
  }
}

// NativeResult recovered layout:
//   +0 uint32 len
//   +8 uint8_t *data
function readNativeResult(rp) {
  if (!rp || rp.isNull()) return { ptr: hexPtr(rp), null: true };
  try {
    const len = rp.readU32();
    const data = rp.add(8).readPointer();
    return {
      ptr: hexPtr(rp),
      len: len,
      data_ptr: hexPtr(data),
      data_hex: dumpHex(data, len, MAX_DUMP),
      truncated: len > MAX_DUMP,
    };
  } catch (e) {
    return { ptr: hexPtr(rp), error: String(e) };
  }
}

// ArgBlock recovered layout:
//   +0 uint32 len
//   +4 uint16 type
//   +8 uint8_t *data
function readArgBlock(ap) {
  if (!ap || ap.isNull()) return { ptr: hexPtr(ap), null: true };
  try {
    const len = ap.readU32();
    const type = ap.add(4).readU16();
    const data = ap.add(8).readPointer();
    return {
      ptr: hexPtr(ap),
      len: len,
      type: type,
      data_ptr: hexPtr(data),
      data_hex: dumpHex(data, len, MAX_DUMP),
      truncated: len > MAX_DUMP,
    };
  } catch (e) {
    return { ptr: hexPtr(ap), error: String(e) };
  }
}

function addHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', module: mod.name, base: hexPtr(mod.base), name: name, addr: hexPtr(addr) });
  } catch (e) {
    jlog({ event: 'hook_error', name: name, addr: hexPtr(addr), error: String(e) });
  }
}

function installHooks(mod) {
  jlog({ event: 'install_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  // sub_5B62121(module_id std::string*, digest16, digest_len, extra, extra_len)
  addHook(mod, 'sub_5B62121', {
    onEnter(args) {
      this.module_id = readStdString(args[0]);
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
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B62121', result: readNativeResult(retval) });
    }
  });

  // sub_5B7D768(input_ptr, n): final tail wrapper before nested "LL" VM.
  addHook(mod, 'sub_5B7D768', {
    onEnter(args) {
      this.input = ptr(args[0]);
      this.n = Number(args[1]);
      jlog({
        event: 'enter_sub_5B7D768',
        input_ptr: hexPtr(this.input),
        n: this.n,
        input_hex: dumpHex(this.input, this.n, MAX_DUMP),
        // Useful for reconstructing raw21 if input == raw21 + 2.
        input_minus2_21_hex: dumpHex(this.input.sub(2), 21, 64),
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B7D768', result: readNativeResult(retval) });
    }
  });

  // sub_5B7D5DC(format, argblock...): final nested VM launcher.
  addHook(mod, 'sub_5B7D5DC', {
    onEnter(args) {
      jlog({
        event: 'enter_sub_5B7D5DC',
        format_ptr: hexPtr(args[0]),
        format: readCStringSafe(args[0], 16),
        arg0: readArgBlock(args[1]),
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B7D5DC', result: readNativeResult(retval) });
    }
  });

  // VM interpreter. Logs program pointer and result. Keep this coarse to avoid huge logs.
  addHook(mod, 'sub_5B64F10', {
    onEnter(args) {
      this.ctx = ptr(args[0]);
      let program = NULL;
      try { program = this.ctx.readPointer(); } catch (_) {}
      this.program = program;
      jlog({
        event: 'enter_sub_5B64F10',
        ctx: hexPtr(this.ctx),
        program_ptr: hexPtr(program),
        program_head_hex: dumpHex(program, 32, 32),
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_5B64F10', program_ptr: hexPtr(this.program), result: readNativeResult(retval) });
    }
  });

  // High-level MD5/signature builder. Args are complex C++ objects, so log raw pointers only.
  addHook(mod, 'sub_55658EF', {
    onEnter(args) {
      jlog({
        event: 'enter_sub_55658EF',
        args: [hexPtr(args[0]), hexPtr(args[1]), hexPtr(args[2]), hexPtr(args[3]), hexPtr(args[4]), hexPtr(args[5])]
      });
    },
    onLeave(retval) {
      jlog({ event: 'leave_sub_55658EF', retval: hexPtr(retval) });
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

  // Frida 17 compatible polling fallback. This is safe for attach-to-running QQ.
  const timer = setInterval(function () {
    if (tryInstall()) clearInterval(timer);
  }, 250);
}

jlog({ event: 'script_loaded', pid: Process.id, arch: Process.arch, platform: Process.platform });
waitForModule(TARGET_MODULE, installHooks);
