// Focused trace for sub_5B6D9EB key8 derivation internals.
// Read-only; attaches to internal instruction addresses around the v632 key buffer.

'use strict';

const TARGET_MODULE = 'wrapper.node';
const MAX_DUMP = 1024;

const OFF = {
  sub_5B6D9EB: 0x5B6D9EB,
  // Around the decompiled key derivation tail:
  //   v55 = S[...] ^ seed[k]
  //   seed[k] = v55
  //   v632[k] = v55
  //   ...
  //   v29 = v632
  key_loop_store: 0x5B6EADB,
  seed_ready: 0x5B6E7E3,
  key_tail: 0x5B6EAFA,
  sub_5B61D31: 0x5B61D31,
};

function now() { return (new Date()).toISOString(); }
function jlog(obj) { obj.ts = now(); console.log(JSON.stringify(obj)); }
function cleanStdoutPrompt() {
  // Avoid Frida REPL prompt prefix corrupting the first JSON event after attach.
  try { console.log(''); } catch (_) {}
}
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

function addHook(mod, name, callbacks) {
  const addr = mod.base.add(OFF[name]);
  try {
    Interceptor.attach(addr, callbacks);
    jlog({ event: 'hooked', name, addr: hexPtr(addr), base: hexPtr(mod.base) });
  } catch (e) { jlog({ event: 'hook_error', name, addr: hexPtr(addr), error: String(e) }); }
}

function ctxRegs(ctx) {
  return {
    rip: hexPtr(ctx.rip), rsp: hexPtr(ctx.rsp), rbp: hexPtr(ctx.rbp),
    rax: hexPtr(ctx.rax), rbx: hexPtr(ctx.rbx), rcx: hexPtr(ctx.rcx), rdx: hexPtr(ctx.rdx),
    rsi: hexPtr(ctx.rsi), rdi: hexPtr(ctx.rdi), r8: hexPtr(ctx.r8), r9: hexPtr(ctx.r9),
    r10: hexPtr(ctx.r10), r11: hexPtr(ctx.r11), r12: hexPtr(ctx.r12), r13: hexPtr(ctx.r13),
    r14: hexPtr(ctx.r14), r15: hexPtr(ctx.r15),
  };
}

function install(mod) {
  cleanStdoutPrompt();
  jlog({ event: 'install_keyderive_hooks', module: mod.name, base: hexPtr(mod.base), path: mod.path });

  addHook(mod, 'sub_5B6D9EB', {
    onEnter(args) {
      this.rsp0 = this.context.rsp;
      jlog({
        event: 'enter_sub_5B6D9EB',
        rsp: hexPtr(this.rsp0),
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
    }
  });

  addHook(mod, 'key_loop_store', {
    onEnter() {
      const sp = this.context.rsp;
      jlog({
        event: 'key_loop_store',
        regs: ctxRegs(this.context),
        // Dump several plausible local ranges. Hex-Rays places v632 near rsp+0x248
        // in the decompiled frame, but keep neighboring windows for confirmation.
        stack_1e0: dumpHex(sp.add(0x1e0), 0x100, 0x100),
        stack_220: dumpHex(sp.add(0x220), 0x100, 0x100),
        stack_248: dumpHex(sp.add(0x248), 0x80, 0x80),
      });
    }
  });

  // Immediately before the RC4 KSA setup. IDA stack frame shows the 8-byte
  // mutable seed used by KSA is var_2D0 (rbp-0x2d0).  The older rbp-0x2d8
  // window includes adjacent var_2D8 and is kept only for context.
  addHook(mod, 'seed_ready', {
    onEnter() {
      const rbp = this.context.rbp;
      jlog({
        event: 'seed_ready',
        regs: ctxRegs(this.context),
        seed_context_rbp_2d8: dumpHex(rbp.sub(0x2d8), 0x20, 0x20),
        seed8_rbp_2d0: dumpHex(rbp.sub(0x2d0), 0x8, 0x8),
        seed_pre_rotate_guess_ror_back: dumpHex(rbp.sub(0x2d0).add(2), 0x6, 0x6),
        final_v632_area: dumpHex(rbp.sub(0x268), 0x20, 0x20),
        stack_220: dumpHex(this.context.rsp.add(0x220), 0x120, 0x120),
      });
    }
  });

  addHook(mod, 'key_tail', {
    onEnter() {
      const sp = this.context.rsp;
      jlog({
        event: 'key_tail',
        regs: ctxRegs(this.context),
        seed8_rbp_2d0: dumpHex(this.context.rbp.sub(0x2d0), 0x8, 0x8),
        key8_rbp_268: dumpHex(this.context.rbp.sub(0x268), 0x8, 0x8),
        stack_1e0: dumpHex(sp.add(0x1e0), 0x100, 0x100),
        stack_220: dumpHex(sp.add(0x220), 0x100, 0x100),
        stack_248: dumpHex(sp.add(0x248), 0x80, 0x80),
      });
    }
  });

  addHook(mod, 'sub_5B61D31', {
    onEnter(args) {
      jlog({
        event: 'enter_sub_5B61D31',
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

const mod = Process.findModuleByName(TARGET_MODULE);
if (!mod) jlog({ event: 'module_not_found', module: TARGET_MODULE });
else install(mod);
