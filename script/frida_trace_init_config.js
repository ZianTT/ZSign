// Trace A1/self initialization fields and global SDK/security config flow.
// This is read-only: it does not patch behavior.
//
// Usage:
//   frida -p <QQ_PID> -l frida_trace_init_config.js -o init_config_trace.jsonl

'use strict';

const TARGET_MODULE = 'wrapper.node';
const MAX_DUMP = 2048;

const OFF = {
  sub_2BF4E50: 0x2BF4E50,
  sub_5575184: 0x5575184,
  sub_557566C: 0x557566C,
  sub_557E8BA: 0x557E8BA,
  sub_557EAAF: 0x557EAAF,
  sub_5564244: 0x5564244,
  sub_556440D: 0x556440D,
  sub_5555707: 0x5555707,
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
  if (!sp || sp.isNull()) return { ptr: hexPtr(sp), null: true };
  try {
    const data = sp.readPointer();
    const len = Number(sp.add(Process.pointerSize).readU64());
    const sane = len >= 0 && len <= 0x100000;
    return {
      ptr: hexPtr(sp),
      data_ptr: hexPtr(data),
      len,
      hex: sane ? dumpHex(data, len, MAX_DUMP) : null,
      text: sane ? readCStringSafe(data, Math.min(len + 1, 1024)) : null,
    };
  } catch (e) { return { ptr: hexPtr(sp), error: String(e) }; }
}

// ZSign-style NTStr / C++ short-string-ish structure used by sub_2BF4E50 A1.
// If low bit at +0 is set, pointer is at +16; otherwise inline bytes start at +1.
function readA1NtStr(base, off) {
  if (!base || base.isNull()) return { null: true };
  const p = base.add(off);
  try {
    const flag = p.readU8();
    const data = (flag & 1) ? p.add(16).readPointer() : p.add(1);
    return {
      struct_ptr: hexPtr(p),
      flag,
      data_ptr: hexPtr(data),
      text: readCStringSafe(data, 1024),
      head_hex: dumpHex(data, 128, 128),
    };
  } catch (e) { return { struct_ptr: hexPtr(p), error: String(e) }; }
}

function readObjConfig(obj) {
  if (!obj || obj.isNull()) return { ptr: hexPtr(obj), null: true };
  const offsets = [0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 376];
  const strings = {};
  for (const off of offsets) {
    try { strings[String(off)] = readStdString(obj.add(off)); } catch (e) { strings[String(off)] = { error: String(e) }; }
  }
  return { ptr: hexPtr(obj), strings };
}

function addHook(mod, name, callbacks) {
  if (OFF[name] === undefined) {
    jlog({ event: 'hook_skip_missing_offset', name });
    return;
  }
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', name, addr: hexPtr(addr), base: hexPtr(mod.base) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function install(mod) {
  jlog({ event: 'install_init_config_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_2BF4E50', {
    onEnter(args) {
      this.a1 = ptr(args[0]);
      jlog({
        event: 'enter_sub_2BF4E50',
        a1: hexPtr(this.a1),
        cmd_struct: hexPtr(args[1]),
        data_struct: hexPtr(args[2]),
        out: hexPtr(args[3]),
        sign_type: Number(args[4]),
        a1_fields: {
          v8_16: readA1NtStr(this.a1, 16),
          v9_40: readA1NtStr(this.a1, 40),
          qua_64: readA1NtStr(this.a1, 64),
          uin_88: readA1NtStr(this.a1, 88),
          guid_112: readA1NtStr(this.a1, 112),
        }
      });
    }
  });

  addHook(mod, 'sub_5575184', {
    onEnter(args) {
      const d = ptr(args[0]);
      jlog({
        event: 'enter_sub_5575184',
        dest: hexPtr(d),
        dest_ptrs: [0,1,2,3,4].map(i => hexPtr(d.add(i * Process.pointerSize).readPointer())),
        dest_text: [0,1,2,3,4].map(i => readCStringSafe(d.add(i * Process.pointerSize).readPointer(), 1024)),
      });
    }
  });

  addHook(mod, 'sub_557566C', {
    onEnter(args) {
      const d = ptr(args[0]);
      this.dest = d;
      jlog({
        event: 'enter_sub_557566C',
        dest: hexPtr(d),
        n58: Number(args[1]),
        dest_ptrs: [0,1,2,3,4].map(i => hexPtr(d.add(i * Process.pointerSize).readPointer())),
        dest_text: [0,1,2,3,4].map(i => readCStringSafe(d.add(i * Process.pointerSize).readPointer(), 1024)),
      });
    }
  });

  addHook(mod, 'sub_557E8BA', {
    onEnter(args) {
      jlog({
        event: 'enter_sub_557E8BA',
        obj: hexPtr(args[0]),
        args_text: [1,2,3,4,5].map(i => readCStringSafe(ptr(args[i]), 1024)),
        obj_before: readObjConfig(ptr(args[0])),
      });
      this.obj = ptr(args[0]);
    },
    onLeave() { jlog({ event: 'leave_sub_557E8BA', obj_after: readObjConfig(this.obj) }); }
  });

  addHook(mod, 'sub_557EAAF', {
    onEnter(args) { this.p = ptr(args[0]); jlog({ event: 'enter_sub_557EAAF', p: hexPtr(this.p), input_guess: readObjConfig(this.p) }); },
    onLeave() { jlog({ event: 'leave_sub_557EAAF' }); }
  });

  addHook(mod, 'sub_5564244', {
    onLeave(retval) { jlog({ event: 'leave_sub_5564244', obj: readObjConfig(ptr(retval)) }); }
  });

  addHook(mod, 'sub_556440D', {
    onEnter(args) {
      this.out = ptr(args[0]);
      jlog({
        event: 'enter_sub_556440D',
        out: hexPtr(this.out),
        module: readCStringSafe(ptr(args[1]), 512),
        payload_struct: hexPtr(args[2]),
      });
    },
    onLeave() {
      jlog({ event: 'leave_sub_556440D', out_string: readStdString(this.out) });
    }
  });

  // sub_55658EF(p_src, module, sign_type_string, payload_string)
  // p_src is the std::string output holding the wrapped signature bytes.
  addHook(mod, 'sub_55658EF', {
    onEnter(args) {
      this.out = ptr(args[0]);
      jlog({
        event: 'enter_sub_55658EF',
        out: hexPtr(this.out),
        module: readCStringSafe(ptr(args[1]), 512),
        sign_type_string: readStdString(ptr(args[2])),
        payload_string: readStdString(ptr(args[3])),
      });
    },
    onLeave() {
      jlog({ event: 'leave_sub_55658EF', out_string: readStdString(this.out) });
    }
  });

  addHook(mod, 'sub_5555707', {
    onEnter(args) { this.out = ptr(args[0]); jlog({ event: 'enter_sub_5555707', out: hexPtr(this.out) }); },
    onLeave(retval) { jlog({ event: 'leave_sub_5555707', retval: hexPtr(retval), out_string: this.out ? readStdString(this.out) : null }); }
  });
}

function waitForModule(name) {
  const timer = setInterval(function () {
    const mod = Process.findModuleByName(name);
    if (mod) { clearInterval(timer); install(mod); }
  }, 100);
}

waitForModule(TARGET_MODULE);
