// Frida 17 anti-trace/environment bypass helpers for QQ wrapper.node research.
//
// Load this BEFORE the trace script, e.g.:
//   frida -p <QQ_PID> \
//     -l frida_bypass_antitrace.js \
//     -l frida_trace_ll_safe.js \
//     -o ll_cleanish_trace.jsonl
//
// Goal: make wrapper.node see the same broad environment it expects in a normal
// QQ process while Frida is attached. This is for collecting less-contaminated
// research traces; still validate final byte-identical output independently.

'use strict';

const BYPASS_TARGET_MODULE = 'wrapper.node';

const HIDE_RE = /(frida|gum-js|gum-js-loop|gadget|linjector|re\.frida|memfd:frida|frida-agent|frida-helper)/i;
const FAKE_WRAPPER_PATH = '/opt/QQ/resources/app/wrapper.node';
const FAKE_COMM = 'qq\n';

function now() { return (new Date()).toISOString(); }
function jlog(obj) { obj.ts = now(); console.log(JSON.stringify(obj)); }
function hexPtr(p) { try { return ptr(p).toString(); } catch (_) { return String(p); } }
function readCStringSafe(p, maxLen) {
  if (!p || p.isNull()) return null;
  try { return p.readCString(maxLen || 4096); } catch (e) { return null; }
}

function getTargetModule() {
  try { return Process.findModuleByName(BYPASS_TARGET_MODULE); } catch (_) { return null; }
}

function isInTarget(p) {
  const m = getTargetModule();
  if (!m || !p || p.isNull()) return false;
  const x = ptr(p);
  return x.compare(m.base) >= 0 && x.compare(m.base.add(m.size)) < 0;
}

function findExport(name) {
  let p = null;
  try {
    if (Module.findGlobalExportByName) p = Module.findGlobalExportByName(name);
  } catch (_) {}
  if (!p) {
    try {
      const libc = Process.findModuleByName('libc.so.6') || Process.findModuleByName('libc.so');
      if (libc && libc.findExportByName) p = libc.findExportByName(name);
    } catch (_) {}
  }
  if (!p) {
    try {
      const mods = Process.enumerateModules();
      for (const m of mods) {
        if (m.name.indexOf('libc') !== -1 && m.findExportByName) {
          p = m.findExportByName(name);
          if (p) break;
        }
      }
    } catch (_) {}
  }
  if (!p) jlog({ event: 'bypass_missing_export', name });
  return p;
}

const fakeWrapperPathPtr = Memory.allocUtf8String(FAKE_WRAPPER_PATH);

function installDladdrBypass() {
  const dladdrPtr = findExport('dladdr');
  if (!dladdrPtr) return;
  Interceptor.attach(dladdrPtr, {
    onEnter(args) {
      this.addr = ptr(args[0]);
      this.info = ptr(args[1]);
      this.caller = this.returnAddress;
      this.enabled = isInTarget(this.caller) || isInTarget(this.addr);
    },
    onLeave(retval) {
      if (!this.enabled || !this.info || this.info.isNull()) return;
      try {
        // Linux x86_64 Dl_info:
        //   char *dli_fname; void *dli_fbase; char *dli_sname; void *dli_saddr;
        this.info.writePointer(fakeWrapperPathPtr);
        if (retval.toInt32() === 0) retval.replace(1);
        jlog({ event: 'bypass_dladdr_wrapper_path', caller: hexPtr(this.caller), addr: hexPtr(this.addr) });
      } catch (e) {
        jlog({ event: 'bypass_dladdr_error', error: String(e) });
      }
    }
  });
}

function installMadviseBypass() {
  const madvisePtr = findExport('madvise');
  if (!madvisePtr) return;
  Interceptor.attach(madvisePtr, {
    onEnter(args) {
      this.caller = this.returnAddress;
      this.enabled = isInTarget(this.caller) && args[1].toUInt32() === 0 && args[2].toInt32() === 50;
    },
    onLeave(retval) {
      if (!this.enabled) return;
      retval.replace(0);
      jlog({ event: 'bypass_madvise_success', caller: hexPtr(this.caller) });
    }
  });
}

function writeTempFile(path, text) {
  const f = new File(path, 'w');
  f.write(text);
  f.flush();
  f.close();
}

function sanitizeMaps() {
  const src = '/proc/self/maps';
  const tmp = `/tmp/.qq_maps_clean_${Process.id}.txt`;
  try {
    let text = File.readAllText(src);
    const before = text.split('\n').length;
    const lines = text.split('\n').filter(line => !HIDE_RE.test(line));
    const after = lines.length;
    text = lines.join('\n');
    if (!text.endsWith('\n')) text += '\n';
    writeTempFile(tmp, text);
    jlog({ event: 'bypass_maps_sanitized', tmp, before_lines: before, after_lines: after });
    return tmp;
  } catch (e) {
    jlog({ event: 'bypass_maps_sanitize_failed', error: String(e) });
    return src;
  }
}

let sanitizedMapsPath = null;
let fakeCommPath = null;

function installFopenBypass() {
  const fopenPtr = findExport('fopen');
  if (!fopenPtr) return;
  const realFopen = new NativeFunction(fopenPtr, 'pointer', ['pointer', 'pointer']);

  sanitizedMapsPath = sanitizeMaps();
  fakeCommPath = `/tmp/.qq_comm_clean_${Process.id}.txt`;
  try { writeTempFile(fakeCommPath, FAKE_COMM); } catch (e) { jlog({ event: 'bypass_comm_write_failed', error: String(e) }); }

  const mapsPathPtr = Memory.allocUtf8String(sanitizedMapsPath);
  const commPathPtr = Memory.allocUtf8String(fakeCommPath);

  Interceptor.replace(fopenPtr, new NativeCallback(function (pathPtr, modePtr) {
    const path = readCStringSafe(pathPtr, 4096) || '';
    if (path === '/proc/self/maps') {
      jlog({ event: 'bypass_fopen_maps', original: path, replacement: sanitizedMapsPath });
      return realFopen(mapsPathPtr, modePtr);
    }
    if (/^\/proc\/\d+\/comm$/.test(path)) {
      jlog({ event: 'bypass_fopen_comm', original: path, replacement: fakeCommPath });
      return realFopen(commPathPtr, modePtr);
    }
    return realFopen(pathPtr, modePtr);
  }, 'pointer', ['pointer', 'pointer']));
}

function installBypasses() {
  jlog({ event: 'bypass_script_loaded', pid: Process.id, arch: Process.arch, platform: Process.platform });
  installDladdrBypass();
  installMadviseBypass();
  installFopenBypass();
  jlog({ event: 'bypass_installed', target: BYPASS_TARGET_MODULE });
}

installBypasses();
