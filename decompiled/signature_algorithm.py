"""
Clean-room reconstruction of wrapper.node signing flow around sub_2BF4E50.

This file is intentionally written as readable Python instead of a literal
Hex-Rays dump.  It documents the recovered data flow and implements the parts
that are clearly visible in IDA:

    sub_2BF4E50 -> sub_557A6A0 ->
        sub_5555707()             # key/session material provider
        sub_556440D(module, body) # ECDH access auxiliary blob
        sub_55658EF(module, cmd, body) # MD5 + native final wrapping

The final native wrapping routine is sub_5B62121/sub_5B61AFB/... .  It accepts
the module id, the raw 16-byte MD5 digest, and an optional extra string.  The
decompiled code shows it copies a 0x17a-byte static table and interprets a
format string "LLL" before returning an allocated byte buffer.  The recovered
`LLL` path is translated below, including opcode 0x79's environment flag byte.
"""

from __future__ import annotations

from dataclasses import dataclass
from hashlib import md5
from pathlib import Path
import time
from typing import Callable, Optional


SSO_ESTABLISH_SHARE_KEY = "trpc.o3.ecdh_access.EcdhAccess.SsoEstablishShareKey"
SSO_SECURE_ACCESS = "trpc.o3.ecdh_access.EcdhAccess.SsoSecureAccess"

VIPII_ALPHABET_20 = b'"#$()123456FHRSTabcdef789:>ABCDEEghijk*mnrstuvwxyz'
VIPII_ALPHABET_21 = b'"#$()123456abcdefFHRST789:>ABCDEEmnrst*hijkluvwxyz'
SUB_5B6D9EB_CONST_A = b"(eT7*@a$"  # little-endian 0x2461402A37546528
SUB_5B6D9EB_CONST_B = b"9!>6X)&O"  # little-endian 0x4F262958363E2139
CHACHA20_CONSTANT = b"expand 32-byte k"  # xmmword_990380 used by sub_5B6CFF4
SUB_5B63952_MAGIC_BEGIN = b"something magic."
SUB_5B63952_MAGIC_END = b"end magic things"


@dataclass
class PackedThreeStrings768:
    """IDA layout used by sub_557A6A0: three 255-byte strings + 1-byte len."""

    part0_key_material: bytes
    part1_ecdh_blob: bytes
    part2_signature: bytes

    def pack(self) -> bytes:
        return b"".join(_pack_255(x) for x in (
            self.part0_key_material,
            self.part1_ecdh_blob,
            self.part2_signature,
        ))


@dataclass
class SignParts:
    """Logical result returned by sub_2BF4E50 through three std::strings."""

    key_material: bytes
    ecdh_blob: bytes
    signature: bytes


VM_PROGRAM_MAIN = bytes.fromhex(
    "12000200090000009d1b0000b500000002001500750112000000000145010400"
    "020014000202140021231e00010402050c003105030401143100030476041300"
    "000000040d45ff000f550206080031050306140504080d55ff000f5502070900"
    "31050307140504100d55ff000f5502070a0031050307140504180d55ff000f55"
    "02070b0031050307014545011900215e1e00216f1e00014702081400360ce7"
    "fff5a951e2e216234526e628091000280a110026fb7705140005005017215e"
    "1e00216f1e00014702081500360ce334e92993bab714234526e62809100028"
    "0a110026fb7705140005000205100021561e00010740570b00050807043208"
    "0308310806070507070150f678060500560000050d57ff000f770128310703"
    "08140705080d77ff000f770138310703080207150021771e00010801594098"
    "090032090308310907080508080150f7010802090f0040980d000509080605"
    "0a0805320a030a310a07090508080150f27907150007007a07020027000002"
    "6102"
)


VM_PROGRAM_SECONDARY = bytes.fromhex(
    "0800030003000000931e0000ae0000000200f00121001e007b200700700000"
    "050000000600000101320105010202ebff42218f0002011000320205010203"
    "aeff473204005100850021121e002202840000007130020020010001460104"
    "0001c163017c010f00000000010203080032040503310401030203090032"
    "0405033104010302030a00320405033104010302030b003204050331040103"
    "02031400320405033104010302031500320405033104010302031600320405"
    "03310401030203170032040503310401030203300032030003020420003103"
    "01040203310032030003020421003103010402033200320300030204220031"
    "0301040203330032030003020423003103010402033c003203000302042c00"
    "3103010402033d003203000302042d003103010402033e003203000302042e"
    "003103010402033f003203000302042f003103010401f3630301d163010000"
    "0003010010000000616d676f6d2064617461206b6e6f776e"
)


# Nested programs reached from VM_PROGRAM_MAIN opcode 0x77 -> sub_5B6D9EB.
# sub_5B61F70 copies VM_PROGRAM_VIPII (src__0, 0x1bc bytes) and invokes
# sub_5B619E7(format="VIPII").
VM_PROGRAM_VIPII = bytes.fromhex(
    "0c0004000100000088160000d600000002001500020132000122420b41002110"
    "1e0022008100000021231f0022039a000000010434050a0273100800080001"
    "064056170074000700000000071204073232070004050707480f770d77ff00"
    "270707110f77310709060506060150ea010140211500330703013207090705"
    "0707260f770d77ff00270707200f7731070906050101010506060150ec63"
    "0002001400420b400021101e0022006400000021231f0022037d00000001"
    "0434050a0273100800080001064056170074000700000000071204073232"
    "070004050707260f770d77ff00270707200f77310709060506060150ea01"
    "01402115003307030132070907050707480f770d77ff00270707110f7731"
    "070906050101010506060150ec6300000000030100320000002223242829"
    "31323334353646485253546162636465663738393a3e4142434445456768"
    "696a6b2a6d6e72737475767778797a000000030400020000000000000001"
    "000000000301003200000022232428293132333435366162636465664648"
    "5253543738393a3e4142434445456d6e7273742a68696a6b6c7576777879"
    "7a000000030400020000000000000001000000"
)


# sub_5B61D31 copies VM_PROGRAM_LLIJL (src__1, 0x1de bytes) and invokes
# sub_5B61848(format="LLIJL").
VM_PROGRAM_LLIJL = bytes.fromhex(
    "1b00050006000000420f0000e70000002400170028011a00201221231e0002"
    "044000214b0a0002052000405003002305235c020d080021de1f0012050c"
    "044605050034050c04500534050c0405050501235f21f91f000105021018"
    "000211100040f54600330609051507050432071607077630060905150605"
    "040506060140060e003306090515070504050707013207160718d7077630"
    "060905150605040506060240060f00330609051507050405070702320716"
    "0719070710077630060905150605040506060340060f0033060905150705"
    "040507070332071607190707180776300609050505050150b7010540f509"
    "003306090530060e050505050150f80105235a402a6c0034050a40295726"
    "b526e62a1207002a0718002814090024150a002a09120072060500050020"
    "b51505050421551e00010620b74076320015070604050707032b080b061a"
    "0808101b880f883108050715070604050707022b080b061a0808111b88"
    "0f883108050715070604050707012b080b061cd81b880f883108050715"
    "070604050707002b080b061b880f88310805070506060150ce01064046"
    "1900060a1506402a1500060a1506060715063207010732080506098716"
    "7781000d77ff000f773107030a0506060150e8050a1540280914005095"
    "6103"
)


def _load_vm_program_ll() -> bytes:
    """Load final `LL` VM bytecode (src__2 @ 0xD59790, size 0xCC0)."""
    path = Path(__file__).with_name("vm_program_ll_src2_exported.hex")
    data = bytes.fromhex(path.read_text(encoding="ascii"))
    if len(data) != 0xCC0:
        raise ValueError(f"unexpected final LL VM length {len(data):#x}")
    return data


VM_PROGRAM_LL = _load_vm_program_ll()


def _u16(b: bytes, off: int) -> int:
    return int.from_bytes(b[off:off + 2], "little", signed=False)


def _s16(b: bytes, off: int) -> int:
    return int.from_bytes(b[off:off + 2], "little", signed=True)


def _u32(b: bytes, off: int) -> int:
    return int.from_bytes(b[off:off + 4], "little", signed=False)


def _s8(x: int) -> int:
    return x - 0x100 if x & 0x80 else x


def _u32w(x: int) -> int:
    return x & 0xFFFFFFFF


def _s32(x: int) -> int:
    x &= 0xFFFFFFFF
    return x - 0x100000000 if x & 0x80000000 else x


def _u64w(x: int) -> int:
    return x & 0xFFFFFFFFFFFFFFFF


def _rol32(x: int, n: int) -> int:
    x &= 0xFFFFFFFF
    return ((x << n) | (x >> (32 - n))) & 0xFFFFFFFF


def _bswap32(x: int) -> int:
    x &= 0xFFFFFFFF
    return int.from_bytes(x.to_bytes(4, "little"), "big")


def _s8_from_u64(x: int) -> int:
    b = x & 0xFF
    return b - 0x100 if b & 0x80 else b


def _c_s32_rem(lhs: int, rhs: int) -> int:
    """C99-style signed int32 remainder (division truncates toward zero)."""
    a = _s32(lhs)
    b = _s32(rhs)
    if b == 0:
        return 0
    if a == -0x80000000 and b == -1:
        return -0x80000000
    q = abs(a) // abs(b)
    if (a < 0) ^ (b < 0):
        q = -q
    return a - q * b


def _c_s32_div(lhs: int, rhs: int) -> int:
    """C99-style signed int32 division (truncates toward zero)."""
    a = _s32(lhs)
    b = _s32(rhs)
    if b == 0:
        return 0
    if a == -0x80000000 and b == -1:
        return -0x80000000
    q = abs(a) // abs(b)
    return -q if (a < 0) ^ (b < 0) else q


@dataclass
class VMObject:
    """Heap object model for sub_5B64F10 VM values."""

    type: int
    data: bytearray
    logical_length: int | None = None

    @property
    def length(self) -> int:
        return len(self.data) if self.logical_length is None else self.logical_length

    def clone_native_result(self) -> bytes:
        """Equivalent of opcode 0x61 copying an object to NativeResult."""
        return bytes(self.data[:self.length])


@dataclass
class VMInstruction:
    pc: int
    op: int
    raw: bytes
    text: str


@dataclass
class NativeEnvironment:
    """Environment inputs consumed by VM opcode 0x79.

    These fields correspond to concrete native checks, not arbitrary API
    metadata.  Defaults model the normal in-process QQ/wrapper.node path.
    """

    image_path: str = "wrapper.node"
    proc_comm: str = "qq"
    # If set, bypass individual probes and force the exact opcode 0x79 byte.
    # This is useful when replaying a native trace whose environment byte was
    # captured directly.
    env_flags_override: int | None = None
    # VM opcode 0x79 probes `madvise(obj_data, 0, 50) != -1` and writes the
    # result into raw output byte 5.  Native traces from the normal QQ process
    # show this byte is 0, i.e. the probe fails in the observed environment.
    madvise_success: bool = False
    global_i1_52_valid: bool = True
    # Background anti-instrumentation state used by opcode 0x79.  Native starts
    # a thread (`sub_5B7DFCD`) that scans /proc/self/maps; if any line contains
    # "frida-agent" it stores 1 here, and opcode 0x79 ORs raw byte 5 with 0x04.
    # Captured QQ traces used for byte-identical regression all show this bit is
    # clear, but keep it configurable for traces taken after detection fires.
    dword_79ED4F0: int = 0
    # Optional direct override for the wrapper-path tamper global. If omitted,
    # derive it from image_path, matching sub_557A6A0's effective condition.
    dword_79ED398_override: int | None = None

    @property
    def dword_79ED398(self) -> int:
        if self.dword_79ED398_override is not None:
            return int(self.dword_79ED398_override)
        # Initialized elsewhere from image/module path checks. Native sets this
        # to 0 for the normal /opt/QQ/resources/app/wrapper.node mapping; if it
        # is 1, opcode 0x79 ORs raw byte 5 with 0x08.
        return 0 if "wrapper.node" in self.image_path else 1

    def flags_for_module(self, module_id: str) -> int:
        if self.env_flags_override is not None:
            return int(self.env_flags_override) & 0xFF
        flags = 1 if self.madvise_success else 0
        if "login" not in module_id and "Login" not in module_id:
            if not self.global_i1_52_valid:
                flags |= 0x80
            if self.dword_79ED4F0 == 1:
                flags |= 0x04
            if self.dword_79ED398 == 1:
                flags |= 0x08
        if "qq" not in self.proc_comm:
            flags |= 0x02
        return flags & 0xFF


class NativeWrappingVM:
    """Partial independent interpreter for sub_5B64F10's bytecode VM.

    This implements the confirmed VM framing, disassembly, scalar operations,
    object allocation, and final return. Some object/memory opcodes are still
    being devirtualized; they intentionally raise instead of producing a bogus
    signature.
    """

    # Lengths for opcodes observed in VM_PROGRAM_MAIN.  `0x19` is 2 bytes in
    # this program (`19 00; 21 5e 1e 00 ...`), despite one decompiler path
    # looking like a 4-byte shift op.
    LENGTHS = {
        0x00: 2, 0x01: 2, 0x02: 4, 0x03: 4, 0x04: 6, 0x05: 4, 0x06: 4,
        0x07: 2, 0x08: 4, 0x09: 2, 0x0A: 4, 0x0B: 4, 0x0C: 2, 0x0D: 4, 0x0E: 4,
        0x0F: 2, 0x10: 4, 0x12: 4, 0x13: 4, 0x14: 4, 0x15: 4, 0x16: 4,
        0x17: 4, 0x18: 4, 0x19: 2, 0x1A: 4, 0x1B: 4, 0x1C: 4, 0x1D: 4,
        0x1E: 4, 0x1F: 2, 0x20: 2, 0x21: 4, 0x22: 6, 0x23: 2, 0x24: 4,
        0x26: 2, 0x27: 4, 0x28: 4, 0x29: 2, 0x2A: 4, 0x2B: 4, 0x2D: 4,
        0x2E: 4, 0x2F: 4, 0x30: 4, 0x31: 4, 0x32: 4, 0x33: 4, 0x34: 4,
        0x35: 2, 0x36: 10, 0x38: 4, 0x39: 4, 0x3A: 4, 0x40: 4, 0x42: 4, 0x43: 4, 0x45: 4,
        0x46: 4, 0x50: 2, 0x51: 4, 0x55: 2, 0x56: 2, 0x57: 2, 0x61: 2, 0x63: 2,
        0x72: 4, 0x73: 6, 0x74: 6, 0x75: 6, 0x76: 6, 0x77: 6, 0x78: 4,
        0x79: 6, 0x7A: 6, 0x81: 4, 0xFF: 4,
    }

    def __init__(self, program: bytes = VM_PROGRAM_MAIN, env: NativeEnvironment | None = None):
        self.program = program
        self.slot_count = _u16(program, 0)
        self.pc = 0x10
        # Some obfuscated instructions use byte-sized temporary slot indexes
        # outside the declared logical slot count before folding back into the
        # declared VM frame. Keep the storage generously sized.
        self.slots = [0] * max(self.slot_count + 1, 256)
        self.obj_slots: dict[int, int] = {}
        self.obj_indices: dict[int, int] = {}
        self.objects: dict[int, VMObject] = {}
        self.object_table: list[int] = []
        self.object_index: dict[int, int] = {}
        self._next_obj = 1
        self.module_id = ""
        self.env = env or NativeEnvironment()

    def load_lll_args(self, module_id: str, digest16: bytes, extra: bytes = b"") -> None:
        """Model sub_5B62121 + sub_5B62F7E for format `LLL`.

        The native launcher provides module string plus an ArgBlock for the MD5
        digest and an optional empty ArgBlock.  Exact argument slot numbering is
        part of the VM program; we store canonical handles in high slots for
        debugger visibility and let bytecode allocate/copy as it executes.
        """
        self.module_id = module_id
        module_obj = self._new_object(module_id.encode(), 0x1E)
        digest_obj = self._new_object(digest16, 0x1E)
        extra_obj = self._new_object(extra, 0x1E)
        self._bind_new_object_to_slot(0, module_obj)
        self._bind_new_object_to_slot(1, digest_obj)
        self._bind_new_object_to_slot(2, extra_obj)
        self._alias_object_slot(16, 1)
        self._alias_object_slot(17, 2)

    def load_ll_args(self, tail_input20: bytes) -> None:
        """Model sub_5B7D5DC(format="LL", argblock) for final tail VM.

        `sub_5B7D768` constructs one ArgBlock of type 0x20 and length 20, then
        tail-calls `sub_5B7D5DC("LL", argblock)`.  `sub_5B636DE("LL")` skips the
        first format byte and counts one object argument, so the native loader
        seeds slot `slot_count - 1` (0x34 for src__2).
        """
        if len(tail_input20) != 20:
            raise ValueError("final LL VM expects the 20-byte sub_5B7D768 object")
        self.module_id = "LL"
        arg = self._new_object(tail_input20, 0x20)
        self._bind_new_object_to_slot(0x34, arg)

    def run(self, module_id: str, digest16: bytes, extra: bytes = b"") -> bytes:
        if len(digest16) != 16:
            raise ValueError("digest must be 16 bytes")
        self.load_lll_args(module_id, digest16, extra)
        while self.pc < len(self.program):
            ins = self.decode_one(self.pc)
            result = self.step(ins)
            if result is not None:
                return result
        raise RuntimeError("VM program terminated without opcode 0x61")

    def run_ll(self, tail_input20: bytes) -> bytes:
        self.load_ll_args(tail_input20)
        while self.pc < len(self.program):
            ins = self.decode_one(self.pc)
            result = self.step(ins)
            if result is not None:
                return result
        raise RuntimeError("LL VM program terminated without opcode 0x61")

    def run_llijl(self, key8: bytes, salt64: int, src: bytes) -> bytes:
        """Model sub_5B61D31(format="LLIJL", key8, salt64, src)."""
        if len(key8) != 8:
            raise ValueError("LLIJL key object length must be 8 bytes")
        self.slots[23] = len(key8)
        self.slots[24] = salt64 & 0xFFFFFFFFFFFFFFFF
        self._bind_new_object_to_slot(22, self._new_object(key8, 0x1E))
        self._bind_new_object_to_slot(26, self._new_object(src, 0x1E))
        while self.pc < len(self.program):
            ins = self.decode_one(self.pc)
            result = self.step(ins)
            if result is not None:
                return result
        raise RuntimeError("LLIJL VM program terminated without opcode 0x61")

    def disassemble(self) -> list[VMInstruction]:
        out: list[VMInstruction] = []
        pc = 0x10
        while pc < len(self.program):
            ins = self.decode_one(pc)
            out.append(ins)
            if ins.op == 0x61:
                break
            pc += len(ins.raw)
        return out

    def decode_one(self, pc: int) -> VMInstruction:
        op = self.program[pc]
        length = self.LENGTHS.get(op, 4)
        if op == 0x19 and self.program in (VM_PROGRAM_LL, VM_PROGRAM_LLIJL):
            length = 4
        raw = self.program[pc:pc + length]
        b1 = raw[1] if len(raw) > 1 else 0
        text = f"op_{op:02x}"
        if op == 0x00:
            text = "nop"
        elif op == 0x01:
            text = f"r{b1 & 0xf} = {int.from_bytes(raw, 'little', signed=True) >> 12}"
        elif op == 0x02:
            text = f"r{b1} = {_s16(raw, 2)}"
        elif op == 0x04:
            text = f"r{b1} = 0x{_u32(raw, 2):08x}"
        elif op == 0xFF:
            word = int.from_bytes(raw[2:4], "little") if len(raw) >= 4 else 0
            text = f"r{((word >> 5) & 0x78) // 8} &= 0xff  # prefixed qword mask"
        elif op == 0x05:
            text = f"r{b1} = r{raw[2]} + {_s8(raw[3])}"
        elif op == 0x07:
            word = int.from_bytes(raw, "little")
            text = f"r{((word >> 5) & 0x78) // 8} += r{((word >> 9) & 0x78) // 8}"
        elif op == 0x09:
            word = int.from_bytes(raw[:2], "little")
            text = f"r{((word >> 5) & 0x78) // 8} ^= r{((word >> 9) & 0x78) // 8}"
        elif op == 0x0D:
            text = f"r{b1 & 0xf} = r{int.from_bytes(raw[:2], 'little') >> 12} & 0x{_u16(raw, 2):04x}"
        elif op == 0x0F:
            word = int.from_bytes(raw, "little")
            text = f"r{((word >> 5) & 0x78) // 8} = sign8(r{((word >> 9) & 0x78) // 8})"
        elif op == 0x10:
            text = f"r{raw[3]} = r{raw[2]} & r{raw[1]}"
        elif op == 0x21:
            text = f"obj r{b1 & 0xf} = alloc(len=r{b1 >> 4}, type=0x{_u16(raw, 2):x})"
        elif op == 0x22:
            text = f"fill obj r{b1 & 0xf} from program data ref 0x{_u32(raw, 2):x}"
        elif op == 0x19:
            if len(raw) == 2:
                text = "vm_marker/noop"
            else:
                text = f"r{raw[1]} = r{raw[2]} << {raw[3] & 0x1f}"
        elif op == 0x23:
            word = int.from_bytes(raw, "little")
            text = f"r{b1 & 0xf} = r{word >> 12}"
        elif op == 0x26:
            word = int.from_bytes(raw, "little")
            text = f"obj r{b1 & 0xf} = clone(r{word >> 12})"
        elif op == 0x28:
            text = f"obj r{b1} = clone(r{_u16(raw, 2)})"
        elif op == 0x31:
            text = f"obj[r{raw[2]}][r{raw[3]}] = r{b1}"
        elif op == 0x14:
            text = f"r{b1} = r{raw[2]} >> {raw[3] & 0x1f}"
        elif op == 0x08:
            word = int.from_bytes(raw, "little")
            text = f"r{((word >> 5) & 0x78) // 8} -= r{((word >> 9) & 0x78) // 8}"
        elif op == 0x12:
            text = f"r{b1} = r{raw[2]} % {raw[3]}"
        elif op == 0x06:
            text = f"r{raw[1]} = r{raw[2]} + r{raw[3]}"
        elif op == 0x0B:
            text = f"r{b1} = r{raw[2]} % r{raw[3]}"
        elif op == 0x0E:
            word = int.from_bytes(raw, "little")
            text = f"r{b1 & 0xf} = r{((word >> 9) & 0x78) // 8} % {_s16(raw, 2)}"
        elif op == 0x15:
            text = f"r{b1} = r{raw[2]} * {int.from_bytes(raw[3:4], 'little', signed=True)}"
        elif op == 0x16:
            text = f"r{b1 & 0xf} = r{(int.from_bytes(raw, 'little') >> 12)} & 0x{_u16(raw, 2):04x}"
        elif op == 0x1A:
            text = f"r{b1} = r{raw[2]} >> (r{raw[3]} & 0x3f)"
        elif op == 0x1B:
            word = int.from_bytes(raw, "little")
            text = f"r{(word >> 8) & 0xf} = int32(r{((word >> 9) & 0x78) // 8})"
        elif op == 0x1C:
            text = "qword right shift: r[dst] >>= int32(r[src])"
        elif op in (0x0C, 0x13, 0x17, 0x18, 0x1D, 0x1F, 0x2D, 0x2E, 0x2F, 0x38, 0x39, 0x3A):
            if op == 0x0C:
                word = int.from_bytes(raw, "little")
                text = f"r{((word >> 7) & 0x1e) // 2} %= r{((word >> 9) & 0x78) // 8}"
            elif op == 0x2D:
                text = f"qword_obj[r{raw[2]}][r{raw[3]}] = r{raw[1]}"
            elif op == 0x1D:
                text = f"r{raw[1]} = r{raw[2]} << {raw[3] & 0x1f}"
            elif op == 0x1F:
                text = "default/no-op padding (no explicit switch case)"
            elif op == 0x2E:
                text = f"r{raw[1]} = {_s16(raw, 2)}  # qword imm16"
            elif op == 0x2F:
                text = f"r{raw[1]} = r{raw[3]} & r{raw[2]}  # qword"
            elif op == 0x13:
                text = f"r{raw[1]} = {int.from_bytes(raw[3:4], 'little', signed=True)} - r{raw[2]}"
            elif op == 0x17:
                text = f"r{raw[1]} = r{raw[2]} & {int.from_bytes(raw[3:4], 'little', signed=True)}"
            elif op == 0x18:
                word = int.from_bytes(raw, "little")
                text = f"r{raw[1] & 0xf} <<= (r{((word >> 9) & 0x78) // 8} & 0x1f)"
            elif op == 0x38:
                text = f"r{raw[1]} = r{raw[3]} ^ r{raw[2]}  # qword"
            elif op == 0x39:
                text = f"r{raw[1]} = r{raw[2]} << low8(r{raw[3]})  # qword"
            elif op == 0x3A:
                text = f"r{raw[1]} = r{raw[3]} | r{raw[2]}  # qword"
            else:
                text = f"untranslated scalar/arithmetic op_{op:02x} raw={raw.hex()}"
        elif op == 0x20:
            word = int.from_bytes(raw[:2], "little")
            text = f"r{b1 & 0xf} = header_len(obj r{word >> 12})"
        elif op == 0x24:
            word = int.from_bytes(raw, "little")
            text = f"r{b1 & 0xf} = r{b1 & 0xf} << (r{((word >> 9) & 0x78) // 8} & 0x1f)"
        elif op == 0x27:
            text = f"r{b1} = r{raw[2]} ^ {raw[3]:#x}"
        elif op == 0x2A:
            text = f"r{b1} = r{_u16(raw, 2)}  # qword copy"
        elif op == 0x2B:
            text = f"r{b1} = qword_obj[r{raw[2]}][r{raw[3]}]"
        elif op == 0x29:
            word = int.from_bytes(raw, "little")
            text = f"r{raw[1] & 0xf} = int32(r{word >> 12})"
        elif op == 0x30:
            text = f"obj[r{raw[2]}][r{raw[3]}] = r{b1}"
        elif op == 0x32:
            text = f"r{b1} = obj[r{raw[2]}][r{raw[3]}]"
        elif op == 0x33:
            text = f"r{b1} = obj[r{raw[2]}][r{raw[3]}]  # read variant"
        elif op == 0x34:
            text = f"r{b1} = r{raw[2]} / {int.from_bytes(raw[3:4], 'little', signed=True)}"
        elif op == 0x35:
            word = int.from_bytes(raw, "little")
            text = f"r{((word >> 5) & 0x78) // 8} &= r{((word >> 9) & 0x78) // 8}  # qword compact"
        elif op == 0x36:
            text = f"r{b1} = 0x{int.from_bytes(raw[2:10], 'little'):016x}"
        elif op == 0x40:
            text = f"if r{((int.from_bytes(raw, 'little') >> 5) & 0x78) // 8} >= r{((int.from_bytes(raw, 'little') >> 9) & 0x78) // 8}: branch {raw[2:4].hex()}"
        elif op == 0x42:
            text = f"if r{((int.from_bytes(raw, 'little') >> 5) & 0x78) // 8} != r{int.from_bytes(raw, 'little') >> 12}: branch {raw[2:4].hex()}"
        elif op == 0x43:
            text = f"if r{b1} <= 0: branch {_s16(raw, 2)} words"
        elif op == 0x46:
            text = f"if r{raw[1]} != 0: branch {raw[2:4].hex()}"
        elif op == 0x50:
            text = f"branch {int.from_bytes(raw[1:2], 'little', signed=True)} words"
        elif op in (0x51, 0x55, 0x56, 0x57):
            if op == 0x51:
                text = f"branch {_s16(raw, 2)} words"
            elif op == 0x55:
                word = int.from_bytes(raw, "little")
                text = f"r{((word >> 5) & 0x78) // 8} |= r{((word >> 9) & 0x78) // 8}  # qword"
            elif op == 0x56:
                word = int.from_bytes(raw, "little")
                text = f"r{((word >> 5) & 0x78) // 8} ^= r{((word >> 9) & 0x78) // 8}  # qword"
            elif op == 0x57:
                word = int.from_bytes(raw, "little")
                text = f"r{raw[1] & 0xf} <<= low8(r{((word >> 9) & 0x78) // 8})  # qword compact"
        elif op == 0x63:
            text = "return null/stop nested VM"
        elif op == 0x72:
            text = "call fixed helper sub_5B6CFF4(obj5.data, obj6.data, slot7, slot9)"
        elif op == 0x73:
            text = "srand(decoded slot operand)"
        elif op == 0x74:
            text = f"r{b1} = rand()"
        elif op == 0x75:
            text = f"r{b1 & 0xf} = 0"
        elif op == 0x76:
            text = f"r{b1 & 0xf} = bswap32(usec_time)"
        elif op == 0x77:
            text = "call sub_5B6D9EB transform"
        elif op == 0x7A:
            text = f"r{raw[2]} = sub_5B7D768(obj r{raw[1] & 0xf}.data + 2)"
        elif op == 0x61:
            text = f"return clone(r{b1})"
        return VMInstruction(pc, op, raw, text)

    def step(self, ins: VMInstruction) -> Optional[bytes]:
        raw = ins.raw
        op = ins.op
        b1 = raw[1] if len(raw) > 1 else 0
        next_pc = ins.pc + len(raw)

        if op == 0x00:
            pass
        elif op == 0xFF:
            # Prefixed compact qword mask.  In src__2 the concrete form is
            # `ff 00 35 d4`, which masks the compact destination register to a
            # byte before an int32 truncation and refreshes the compact source
            # register as the byte mask used by the following expanded qword
            # ANDs.  Treating this as padding lets high qword bits leak into
            # the later object byte writes.
            word = int.from_bytes(raw[2:4], "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_scalar(dst, self.slots[dst] & 0xFF)
            self._set_scalar(src, 0xFF)
        elif op == 0x01:
            self._set_dword(b1 & 0xF, int.from_bytes(raw, "little", signed=True) >> 12)
        elif op == 0x02:
            self._set_dword(b1, _s16(raw, 2))
        elif op == 0x03:
            self._set_dword(b1, _u16(raw, 2) << 16)
        elif op == 0x04:
            self._set_dword(b1, _u32(raw, 2))
        elif op == 0x05:
            self._set_dword(b1, self.slots[raw[2]] + _s8(raw[3]))
        elif op == 0x06:
            self._set_dword(raw[1], self.slots[raw[2]] + self.slots[raw[3]])
        elif op == 0x07:
            word = int.from_bytes(raw, "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_dword(dst, self.slots[dst] + self.slots[src])
        elif op == 0x09:
            word = int.from_bytes(raw[:2], "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_dword(dst, self.slots[dst] ^ self.slots[src])
        elif op == 0x0C:
            word = int.from_bytes(raw, "little")
            dst = ((word >> 7) & 0x1E) // 2
            rhs = ((word >> 9) & 0x78) // 8
            denom = self.slots[rhs] & 0xFFFFFFFF
            if denom == 0:
                self._set_dword(dst, 0)
            elif self.slots[dst] == 0x80000000 and denom == 0xFFFFFFFF:
                self._set_dword(dst, 0x80000000)
            else:
                self._set_dword(dst, _c_s32_rem(self.slots[dst], denom))
        elif op == 0x0D:
            word = int.from_bytes(raw[:2], "little")
            self._set_dword(b1 & 0xF, self.slots[word >> 12] & _u16(raw, 2))
        elif op == 0x0E:
            word = int.from_bytes(raw, "little")
            dst = b1 & 0xF
            src = ((word >> 9) & 0x78) // 8
            denom = _s16(raw, 2)
            self._set_dword(dst, 0 if denom == 0 else (self.slots[src] & 0xFFFFFFFF) % denom)
        elif op == 0x0F:
            word = int.from_bytes(raw, "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_dword(dst, _s8_from_u64(self.slots[src]))
        elif op == 0x10:
            self._set_dword(raw[3], self.slots[raw[2]] & self.slots[raw[1]])
        elif op == 0x12:
            denom = raw[3]
            self._set_dword(b1, 0 if denom == 0 else (self.slots[raw[2]] & 0xFFFFFFFF) % denom)
        elif op == 0x14:
            self._set_dword(b1, self.slots[raw[2]] >> (raw[3] & 0x1F))
        elif op == 0x15:
            self._set_dword(b1, self.slots[raw[2]] * _s8(raw[3]))
        elif op == 0x16:
            dst = b1 & 0xF
            if self.program is VM_PROGRAM_LLIJL and raw == b"\x16\x77\x81\x00":
                self._set_dword(dst, (self.slots[dst] & 0xFFFFFFFF) ^ 0x81)
            else:
                imm = 0xFFFFFFFF if raw[2] & 0x80 else _u16(raw, 2)
                self._set_dword(dst, self.slots[dst] & imm)
        elif op == 0x29:
            word = int.from_bytes(raw[:2], "little")
            dst = raw[1] & 0xF
            src = word >> 12
            self._set_scalar(dst, _u64w(_s32(self.slots[src])))
        elif op == 0x2A:
            self._copy_slot(raw[1], _u16(raw, 2), mask=0xFFFFFFFFFFFFFFFF)
        elif op == 0x13:
            self._set_dword(raw[1], _s8(raw[3]) - (self.slots[raw[2]] & 0xFFFFFFFF))
        elif op == 0x17:
            self._set_dword(raw[1], (self.slots[raw[2]] & 0xFFFFFFFF) & _s8(raw[3]))
        elif op == 0x18:
            word = int.from_bytes(raw, "little")
            dst = raw[1] & 0xF
            shift_src = ((word >> 9) & 0x78) // 8
            shifted = (self.slots[dst] & 0xFFFFFFFF) << (self.slots[shift_src] & 0x1F)
            if self.program is VM_PROGRAM_LLIJL and raw == b"\x18\xd7\x07\x76":
                self._set_dword(6, (self.slots[6] & 0xFFFFFFFF) + shifted)
            else:
                self._set_dword(dst, shifted)
        elif op == 0x1A:
            self._set_scalar(raw[1], _u64w(self.slots[raw[2]] >> (self.slots[raw[3]] & 0x3F)))
        elif op == 0x1B:
            word = int.from_bytes(raw, "little")
            dst = (word >> 8) & 0xF
            src = ((word >> 9) & 0x78) // 8
            self._set_dword(dst, self.slots[src])
        elif op == 0x1C:
            word = int.from_bytes(raw, "little")
            dst = raw[1] & 0xF
            src = ((word >> 9) & 0x78) // 8
            self._set_dword(dst, self.slots[dst] >> (self.slots[src] & 0x3F))
        elif op == 0x24:
            if raw == b"\x24\x15\x0a\x00":
                self._set_dword(5, self._slot_object(11).length)
            elif len(raw) >= 4 and raw[2] == 0x0A:
                word = int.from_bytes(raw, "little")
                dst = raw[1] & 0xF
                shift_src = ((word >> 9) & 0x78) // 8
                self._set_dword(dst, (self.slots[dst] & 0xFFFFFFFF) << (self.slots[shift_src] & 0x1F))
            else:
                self._set_dword(raw[1], self.slots[_u16(raw, 2)])
        elif op == 0x21:
            dst = b1 & 0x0F
            len_slot = b1 >> 4
            obj_type = _u16(raw, 2)
            count = self.slots[len_slot] & 0xFFFF
            # Native ArgBlock/Object len is a byte length for byte/string-like
            # types, but integer array types store element count in the header
            # and allocate element-width backing storage.
            if obj_type == 10:
                logical_count = count // 4 if self.program is VM_PROGRAM_LLIJL and count % 4 == 0 else count
                size = logical_count * 8
                count = logical_count
            elif obj_type in (31, 33, 51):
                size = count * 4
            else:
                size = count
            self._bind_new_object_to_slot(dst, self._new_object(b"\0" * size, obj_type, logical_length=count))
        elif op == 0x33:
            obj = self._slot_object(raw[2])
            index = self.slots[raw[3]] & 0xFFFFFFFF
            dst = b1
            if obj.type in (31, 33, 51):
                self._set_dword(dst, self._read_obj_dword(obj, index, ins, raw[2]))
            else:
                self._set_dword(dst, self._read_obj_byte(obj, index, ins, raw[2]))
        elif op == 0x22:
            obj = self._slot_object(b1)
            table = _vm_inline_table(self.program, ins.pc, _u32(raw, 2))
            # Native copies `count * width` bytes from the inline table into
            # the object's data pointer without checking the object's header
            # length.  src__2 intentionally uses this for slot2: header len is
            # 36, while the inline table is 4*36 = 144 bytes and later dword
            # reads address the overflowed backing memory.  Keep the logical
            # header length unchanged, but preserve the copied backing bytes.
            obj.data[:len(table)] = table
        elif op == 0x19:
            if len(raw) == 2:
                # In VM_PROGRAM_MAIN this is a 2-byte marker before object setup.
                pass
            elif self.program is VM_PROGRAM_LLIJL:
                # LLIJL uses compact byte-shift forms such as `19 07 10 00`
                # and `19 07 18 00`: r7 <<= 16 / r7 <<= 24 while packing key
                # bytes into dwords.
                self._set_dword(raw[1], (self.slots[raw[1]] & 0xFFFFFFFF) << (raw[3] & 0x1F))
            else:
                self.slots[raw[1]] = _u32w(self.slots[raw[2]] << (raw[3] & 0x1F))
        elif op == 0x23:
            word = int.from_bytes(raw, "little")
            dst = b1 & 0xF
            src = word >> 12
            self._copy_slot(dst, src)
        elif op == 0x26:
            word = int.from_bytes(raw, "little")
            dst = b1 & 0xF
            src = word >> 12
            self._bind_clone_from_slot(dst, src)
        elif op == 0x28:
            src = _u16(raw, 2)
            self._bind_clone_from_slot(b1, src)
        elif op == 0x31:
            obj = self._slot_object(raw[2])
            index = self.slots[raw[3]] & 0xFFFFFFFF
            value = self.slots[b1] & 0xFFFFFFFF
            if obj.type in (31, 33, 51):
                self._write_obj_dword(obj, index, value, ins, raw[2])
            else:
                self._write_obj_byte(obj, index, value, ins, raw[2])
        elif op == 0x30:
            obj = self._slot_object(raw[2])
            index = self.slots[raw[3]] & 0xFFFFFFFF
            value = self.slots[b1] & 0xFFFFFFFF
            if obj.type in (31, 33, 51):
                self._write_obj_dword(obj, index, value, ins, raw[2])
            else:
                self._write_obj_byte(obj, index, value, ins, raw[2])
        elif op == 0x36:
            self._set_scalar(b1, int.from_bytes(raw[2:10], "little"))
        elif op == 0x40:
            word = int.from_bytes(raw, "little")
            lhs = ((word >> 5) & 0x78) // 8
            rhs = ((word >> 9) & 0x78) // 8
            if (self.slots[lhs] & 0xFFFFFFFF) >= (self.slots[rhs] & 0xFFFFFFFF):
                next_pc = ins.pc + 2 * _s16(raw, 2)
        elif op == 0x43:
            if _s32(self.slots[b1]) <= 0:
                next_pc = ins.pc + 2 * _s16(raw, 2)
        elif op == 0x45:
            # Conditional branch-on-zero. The signed branch word is stored at
            # pc+2; native advances by two uint16 words on the non-taken path.
            if self.slots[b1] == 0:
                next_pc = ins.pc + 2 * _s16(self.program, ins.pc + 2)
            else:
                next_pc = ins.pc + 4
        elif op == 0x46:
            if self.slots[b1] != 0:
                next_pc = ins.pc + 2 * _s16(raw, 2)
            else:
                next_pc = ins.pc + 4
        elif op == 0x50:
            next_pc = ins.pc + 2 * int.from_bytes(raw[1:2], "little", signed=True)
        elif op == 0x51:
            next_pc = ins.pc + 2 * _s16(raw, 2)
        elif op == 0x32:
            obj = self._slot_object(raw[2])
            index = self.slots[raw[3]] & 0xFFFFFFFF
            dst = raw[1]
            if obj.type in (31, 33, 51):
                self._set_dword(dst, self._read_obj_dword(obj, index, ins, raw[2]))
            else:
                self._set_dword(dst, self._read_obj_byte(obj, index, ins, raw[2]))
        elif op == 0x34:
            denom = _s8(raw[3])
            self._set_dword(b1, 0 if denom == 0 else _c_s32_div(self.slots[raw[2]], denom))
        elif op == 0x1F:
            pass
        elif op == 0x20:
            word = int.from_bytes(raw[:2], "little")
            obj = self._slot_object(word >> 12)
            self._set_dword(b1 & 0xF, obj.length)
        elif op == 0x2B:
            obj = self._slot_object(raw[2])
            index = self.slots[raw[3]] & 0xFFFFFFFF
            if obj.type != 10:
                raise RuntimeError(f"opcode 0x2b expected qword-array object type 10, got {obj.type}")
            self._set_scalar(raw[1], self._read_obj_qword(obj, index, ins, raw[2]))
        elif op == 0x1D:
            self._set_dword(raw[1], self.slots[raw[2]] << (raw[3] & 0x1F))
        elif op == 0x2D:
            obj_slot = raw[2]
            index_slot = raw[3]
            obj = self._slot_object(obj_slot)
            index = self.slots[index_slot] & 0xFFFFFFFF
            value = self.slots[raw[1]] & 0xFFFFFFFFFFFFFFFF
            if obj.type == 10:
                self._write_obj_qword(obj, index, value, ins, obj_slot)
        elif op == 0x2E:
            self._set_scalar(raw[1], _u64w(_s16(raw, 2)))
        elif op == 0x2F:
            self._set_scalar(raw[1], _u64w(self.slots[raw[3]] & self.slots[raw[2]]))
        elif op == 0x35:
            word = int.from_bytes(raw, "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_scalar(dst, _u64w(self.slots[dst] & self.slots[src]))
        elif op == 0x38:
            self._set_scalar(raw[1], _u64w(self.slots[raw[3]] ^ self.slots[raw[2]]))
        elif op == 0x39:
            self._set_scalar(raw[1], _u64w(self.slots[raw[2]] << (self.slots[raw[3]] & 0x3F)))
        elif op == 0x3A:
            self._set_scalar(raw[1], _u64w(self.slots[raw[3]] | self.slots[raw[2]]))
        elif op == 0x55:
            word = int.from_bytes(raw, "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_scalar(dst, _u64w(self.slots[dst] | self.slots[src]))
        elif op == 0x57:
            word = int.from_bytes(raw, "little")
            dst = raw[1] & 0xF
            shift_src = ((word >> 9) & 0x78) // 8
            self._set_scalar(dst, _u64w(self.slots[dst] << (self.slots[shift_src] & 0xFF)))
        elif op == 0x75:
            self._set_dword(b1 & 0xF, 0)
        elif op == 0x72:
            # Fixed helper sub_5B6CFF4(obj5.data, obj6.data, slot7, slot9).
            # It writes a ChaCha block as 16 qword cells whose low dword holds
            # the block word and high dword is zero.  IDA shows a3 is placed in
            # state words 14..15 (nonce) and a4 in words 12..13 (counter).
            out_obj = self._slot_object(5)
            key_obj = self._slot_object(6)
            key32 = bytes(key_obj.data[:32]).ljust(32, b"\0")
            block = chacha20_block_64_64(key32, self.slots[9], self.slots[7])
            qwords = bytearray()
            for off in range(0, 64, 4):
                word = int.from_bytes(block[off:off + 4], "little")
                qwords.extend(word.to_bytes(8, "little"))
            out_obj.data[:len(qwords)] = qwords
        elif op == 0x76:
            usec = (time.time_ns() % 1_000_000_000) // 1000
            self._set_dword(b1 & 0xF, _bswap32(usec))
        elif op == 0x77:
            header = self._slot_object(3)
            transformed = sub_5B6D9EB_transform_skeleton(
                bytes(header.data),
                scalar=self.slots[5],
                out4=bytes(self._slot_object(6).data),
                n=self.slots[7],
                mode=self.slots[8],
                input_obj=bytes(self._slot_object(9).data),
                aux_obj=bytes(self._slot_object(10).data),
                out8=bytes(self._slot_object(11).data),
                salt64=self.slots[12],
            )
            header.data[:] = transformed[:len(header.data)]
        elif op == 0x78:
            obj = self._slot_object(raw[1])
            self._set_dword(raw[2], native_crc16_from_crc32(bytes(obj.data)))
        elif op == 0x56:
            word = int.from_bytes(raw, "little")
            dst = ((word >> 5) & 0x78) // 8
            src = ((word >> 9) & 0x78) // 8
            self._set_scalar(dst, _u64w(self.slots[dst] ^ self.slots[src]))
        elif op == 0x79:
            obj = self._slot_object(b1 & 0xF)
            if len(obj.data) <= 5:
                raise RuntimeError("opcode 0x79 expects output object length >= 6")
            obj.data[5] = self.env.flags_for_module(self.module_id)
        elif op == 0x7A:
            obj = self._slot_object(raw[1] & 0x0F)
            n = 20
            if obj.length < 21 or len(obj.data) < 21:
                raise RuntimeError("opcode 0x7a expects source object length >= 21")
            # sub_5B7D768 receives (obj.data + 2, n), copies n-1 bytes, writes
            # 0x04 to the last byte, then runs the final `LL` VM.
            ll_input = bytearray(n)
            ll_input[:n - 1] = obj.data[2:2 + n - 1]
            ll_input[n - 1] = 0x04
            handle = self._new_object(NativeWrappingVM(VM_PROGRAM_LL).run_ll(bytes(ll_input)), 0x20)
            self._bind_new_object_to_slot(raw[2], handle)
        elif op == 0x61:
            obj = self._slot_object(b1)
            return obj.clone_native_result()
        else:
            raise NotImplementedError(f"VM opcode 0x{op:02x} at pc=0x{ins.pc:x}: {ins.raw.hex()} ({ins.text})")

        self.pc = next_pc
        return None

    def _new_object(self, data: bytes, obj_type: int, logical_length: int | None = None) -> int:
        handle = self._next_obj
        self._next_obj += 1
        self.objects[handle] = VMObject(obj_type, bytearray(data), logical_length)
        return handle

    def _clone_object_handle(self, handle: int) -> int:
        obj = self._object(handle)
        return self._new_object(bytes(obj.data), obj.type, obj.logical_length)

    def _object(self, handle: int) -> VMObject:
        if handle not in self.objects:
            raise RuntimeError(f"invalid VM object handle {handle!r}")
        return self.objects[handle]

    def _slot_object(self, slot: int) -> VMObject:
        if slot not in self.obj_slots:
            raise RuntimeError(f"VM slot {slot} does not hold an object")
        index = self.obj_indices[slot]
        if index < 0 or index >= len(self.object_table):
            raise RuntimeError(f"VM slot {slot} object table index {index!r} is invalid")
        handle = self.object_table[index]
        return self._object(handle)

    def _set_slot_object(self, slot: int, handle: int) -> None:
        self._bind_new_object_to_slot(slot, handle)

    def _bind_new_object_to_slot(self, slot: int, handle: int) -> None:
        self.obj_slots[slot] = 1
        # Native sub_5B63780 stores the index returned by sub_5B749DE.  The
        # latter is a vector find+append helper: it returns an existing index
        # for the exact same object pointer, or appends the new pointer.  It
        # does not replace the previous vector entry when rebinding a VM slot.
        # Keeping old entries matters for src__2 where many slots are rebound
        # while other aliases still refer to earlier objects.
        self.obj_indices[slot] = self._register_object(handle)

    def _alias_object_slot(self, dst: int, src: int) -> None:
        if src not in self.obj_slots:
            raise RuntimeError(f"VM slot {src} does not hold an object")
        self.obj_slots[dst] = 1
        self.obj_indices[dst] = self.obj_indices[src]

    def _register_object(self, handle: int) -> int:
        if handle in self.object_index:
            return self.object_index[handle]
        index = len(self.object_table)
        self.object_table.append(handle)
        self.object_index[handle] = index
        return index

    def _set_scalar(self, slot: int, value: int) -> None:
        self.slots[slot] = value & 0xFFFFFFFFFFFFFFFF

    def _set_dword(self, slot: int, value: int) -> None:
        """Write only the low 32 bits of an 8-byte native scalar slot.

        sub_5B64F10 stores scalar slots at 8-byte stride, but many opcodes use
        `*(_DWORD *)(slot_base + 8 * slot) = ...`.  Those writes preserve the
        high dword; qword opcodes later read the full 64-bit slot.  Modeling all
        32-bit writes as full 64-bit assignments loses that high-half state.
        """
        self.slots[slot] = (self.slots[slot] & 0xFFFFFFFF00000000) | (value & 0xFFFFFFFF)

    def _copy_slot(self, dst: int, src: int, mask: int | None = None) -> None:
        value = self.slots[src]
        if mask is not None:
            value &= mask
        self.slots[dst] = value

    def _bind_clone_from_slot(self, dst: int, src: int) -> None:
        if src not in self.obj_slots:
            self._set_scalar(dst, self.slots[src])
        else:
            # Native 0x26/0x28 bind the source object pointer via
            # sub_5B63780/sub_5B749DE; they are pointer aliases.  Deep-copy
            # semantics are used by separate allocator/copy paths and by the
            # return opcode, not by these compact slot-transfer opcodes.
            self._alias_object_slot(dst, src)

    def _replace_slot_with_object(self, slot: int, handle: int) -> None:
        """Model sub_5B63780's replacement side effect for allocator paths.

        Native sub_5B63780 receives the previous object pointer in its `a4`
        parameter for opcodes that allocate a fresh object into an object slot.
        sub_5B749DE first returns the table index for that previous pointer;
        sub_5B63780 then updates the same vector entry to the new object and
        stores that index in the slot's object-index bank.  Alias/copy opcodes
        that pass a4=0 keep pure find+append semantics and use
        `_bind_new_object_to_slot` instead.
        """
        if slot in self.obj_slots and self.obj_indices[slot] < len(self.object_table):
            idx = self.obj_indices[slot]
            old = self.object_table[idx]
            self.object_index.pop(old, None)
            self.object_table[idx] = handle
            self.object_index[handle] = idx
            self.obj_slots[slot] = 1
            self.obj_indices[slot] = idx
        else:
            self._bind_new_object_to_slot(slot, handle)


    def _bounds_error(self, ins: VMInstruction, obj_slot: int, obj: VMObject, index: int, width: int) -> RuntimeError:
        return RuntimeError(
            f"VM object bounds error at pc=0x{ins.pc:x} op=0x{ins.op:02x} raw={ins.raw.hex()} "
            f"slot={obj_slot} type={obj.type} index={index} width={width} len={len(obj.data)}"
        )

    def _check_obj_bounds(self, obj: VMObject, index: int, width: int, ins: VMInstruction, obj_slot: int) -> int:
        if index < 0:
            raise self._bounds_error(ins, obj_slot, obj, index, width)
        start = index * width
        if start + width > len(obj.data):
            raise self._bounds_error(ins, obj_slot, obj, index, width)
        return start

    def _read_obj_byte(self, obj: VMObject, index: int, ins: VMInstruction, obj_slot: int) -> int:
        start = self._check_obj_bounds(obj, index, 1, ins, obj_slot)
        return obj.data[start]

    def _write_obj_byte(self, obj: VMObject, index: int, value: int, ins: VMInstruction, obj_slot: int) -> None:
        start = self._check_obj_bounds(obj, index, 1, ins, obj_slot)
        obj.data[start] = value & 0xFF

    def _read_obj_dword(self, obj: VMObject, index: int, ins: VMInstruction, obj_slot: int) -> int:
        start = self._check_obj_bounds(obj, index, 4, ins, obj_slot)
        return int.from_bytes(obj.data[start:start + 4], "little")

    def _write_obj_dword(self, obj: VMObject, index: int, value: int, ins: VMInstruction, obj_slot: int) -> None:
        start = self._check_obj_bounds(obj, index, 4, ins, obj_slot)
        obj.data[start:start + 4] = (value & 0xFFFFFFFF).to_bytes(4, "little")

    def _read_obj_qword(self, obj: VMObject, index: int, ins: VMInstruction, obj_slot: int) -> int:
        start = self._check_obj_bounds(obj, index, 8, ins, obj_slot)
        return int.from_bytes(obj.data[start:start + 8], "little")

    def _write_obj_qword(self, obj: VMObject, index: int, value: int, ins: VMInstruction, obj_slot: int) -> None:
        start = self._check_obj_bounds(obj, index, 8, ins, obj_slot)
        obj.data[start:start + 8] = (value & 0xFFFFFFFFFFFFFFFF).to_bytes(8, "little")


def disassemble_native_vm_program(program: bytes = VM_PROGRAM_MAIN) -> str:
    """Return a readable linear disassembly of the known VM bytecode."""
    return "\n".join(
        f"{ins.pc:04x}: {ins.raw.hex():<20} {ins.text}"
        for ins in NativeWrappingVM(program).disassemble()
    )


def rc4_crypt_8(key8: bytes) -> bytes:
    """RC4 KSA/PRGA over exactly 8 bytes as recovered in sub_5B6D9EB."""
    if len(key8) != 8:
        raise ValueError("sub_5B6D9EB RC4 helper expects an 8-byte key")
    s = list(range(256))
    j = 0
    for i in range(256):
        j = (j + s[i] + key8[i & 7]) & 0xFF
        s[i], s[j] = s[j], s[i]
    out = bytearray(8)
    i = j = 0
    for n in range(8):
        i = (i + 1) & 0xFF
        j = (j + s[i]) & 0xFF
        s[i], s[j] = s[j], s[i]
        out[n] = key8[n] ^ s[(s[i] + s[j]) & 0xFF]
    return bytes(out)


def _ror_bytes(data: bytes, count: int) -> bytes:
    count %= len(data)
    return data[-count:] + data[:-count]


def derive_sub_5B6D9EB_key8(input_obj: bytes, aux_obj: bytes, scalar: int, n: int, mode: int) -> bytes:
    """Recover the 8-byte key selection/derivation before RC4 in sub_5B6D9EB.

    If `aux_obj` is exactly 8 bytes, native uses it directly. Otherwise it
    builds an 8-byte seed from the same VIPII token generated earlier in
    sub_5B6D9EB, combines that token with two rotated constants, rotates the
    resulting 8-byte pre-seed right by two bytes, then RC4-whitens the seed.

    Confirmed native samples:
      * scalar=0x1ece0400 -> seed d0c36124286585d3 -> key 26370781f10f4a4d
      * scalar=0x8a2f0700 -> seed deb66124286587de -> key 63dc954152130e40
    """
    if len(aux_obj) == 8:
        return aux_obj
    a = _ror_bytes(SUB_5B6D9EB_CONST_A, 2)
    b = _ror_bytes(SUB_5B6D9EB_CONST_B, 2)
    token = vipii_generate_token(scalar, n, mode)
    pre_seed = bytearray(8)
    pre_seed[:4] = a[:4]
    for i in range(4):
        pre_seed[4 + i] = b[i] ^ token[i]
    seed = _ror_bytes(bytes(pre_seed), 2)
    return rc4_crypt_8(seed)


class GlibcRand:
    """Small pure-Python model of glibc `srand`/`rand` used by VIPII.

    Native VIPII calls libc `srand(seed)` once and then repeatedly calls
    `rand()`.  glibc's `rand()` is backed by the same additive generator as
    `random()` for the default state size.  This implementation is included so
    the recovered VIPII token generator can run without wrapper.node.
    """

    def __init__(self, seed: int):
        seed &= 0xFFFFFFFF
        if seed == 0:
            seed = 1
        self._state: list[int] = [seed]
        for i in range(1, 31):
            prev = self._state[i - 1]
            # Park-Miller step used by glibc seeding; treat previous value as
            # signed 32-bit before multiplying.
            if prev >= 0x80000000:
                prev -= 0x100000000
            self._state.append((16807 * prev) % 2147483647)
        self._state.extend(self._state[i - 31] for i in range(31, 34))
        for i in range(34, 344):
            self._state.append((self._state[i - 31] + self._state[i - 3]) & 0xFFFFFFFF)

    def rand(self) -> int:
        i = len(self._state)
        value = (self._state[i - 31] + self._state[i - 3]) & 0xFFFFFFFF
        self._state.append(value)
        return value >> 1


def _vm_inline_table(program: bytes, pc: int, rel_words: int) -> bytes:
    """Parse a VM inline table referenced by opcode 0x22.

    Native computes `table = current_u16_ip + rel_words`, then copies
    `table[1] * *((uint32_t*)table + 1)` bytes from `table + 4` VM words.
    """
    off = pc + 2 * rel_words

    # src__2 / final "LL" contains an obfuscated table reference at
    # pc=0x40 (`22 05 f4 05 00 00`).  The decompiled generic path appears to
    # land on the preceding zero table at 0xc28, but native safe tracing shows
    # slot 5 is populated from the 48-byte table beginning at 0xc90.  Model
    # that concrete native reference here while keeping the generic decoder for
    # the other inline tables (VIPII and the remaining LL tables).
    if program is VM_PROGRAM_LL and pc == 0x40 and rel_words == 0x5F4:
        # Runtime safe trace shows the copied 48-byte slot5 table differs from
        # the raw IDB/exported bytes at 0xc90 (likely runtime-patched static
        # data).  Embed the traced native table so the pure interpreter follows
        # the actual process behavior.
        return bytes.fromhex(
            "21442100010504060dc7438e30060405"
            "011504069f4d88f53006040501260407"
            "e438bdc630070406013604072ef0aa59"
        )

    count = _u16(program, off + 2)
    width = _u32(program, off + 4)
    size = count * width
    return program[off + 8:off + 8 + size]


VIPII_INDEX_TABLE = (0, 1)


def _vipii_transform_byte(value: int, add: int, xor: int) -> int:
    return (((value & 0xFF) + add) & 0xFF) ^ xor


def vipii_generate_token(seed: int, length: int, mode: int) -> bytes:
    """Recover `sub_5B61F70(..., format="VIPII")` side-effect token bytes.

    `sub_5B61F70` passes format `VIPII` into the VM.  The first format byte is
    a return marker; the remaining args initialize slots as:

      * r8  = integer seed for `srand`
      * r9  = mutable output object
      * r10 = output length
      * r11 = mode selector

    Mode 21 uses `VIPII_ALPHABET_20` and applies transform A to random alphabet
    bytes, then transform B to bytes at indices 0 and 1.  Mode 20 uses
    `VIPII_ALPHABET_21` and swaps the transforms.  Native callers observed so
    far request length 4, making `length // 2` random bytes plus two indexed
    bytes.
    """
    if length < 2:
        raise ValueError("VIPII length must be at least 2")
    if mode == 21:
        alphabet = _vm_inline_table(VM_PROGRAM_VIPII, 0x22, 0x81)
        first = (0x48, 0x11)
        second = (0x26, 0x20)
    elif mode == 20:
        alphabet = _vm_inline_table(VM_PROGRAM_VIPII, 0xA8, 0x64)
        first = (0x26, 0x20)
        second = (0x48, 0x11)
    else:
        raise ValueError(f"unsupported VIPII mode {mode}; expected 20 or 21")
    if len(alphabet) != 50:
        raise RuntimeError("bad recovered VIPII alphabet length")

    rng = GlibcRand(seed)
    out = bytearray(length)
    first_count = length // 2
    for i in range(first_count):
        out[i] = _vipii_transform_byte(alphabet[rng.rand() % 50], *first)
    for j, idx in enumerate(VIPII_INDEX_TABLE):
        pos = first_count + j
        if pos >= length:
            break
        out[pos] = _vipii_transform_byte(out[idx], *second)
    return bytes(out)


def chacha20_block_64_64(key32: bytes, counter64: int, nonce64: int) -> bytes:
    """ChaCha20 block function matching `sub_5B6CFF4`.

    IDA shows `sub_5B6CFF4(a1, a2, a3, a4)` initializes 16 little-endian words
    as:

      * words 0..3:  `b"expand 32-byte k"` (`xmmword_990380`)
      * words 4..11: 32-byte key from `a2`
      * words 12..13: `a4` low/high 32-bit words
      * words 14..15: `a3` low/high 32-bit words

    It then runs 10 ChaCha double rounds and adds the original state.  This is
    the IETF-style ChaCha core with a 64-bit counter + 64-bit nonce layout.
    """
    if len(key32) != 32:
        raise ValueError("ChaCha helper requires a 32-byte key/state tail")
    state = [int.from_bytes(CHACHA20_CONSTANT[i:i + 4], "little") for i in range(0, 16, 4)]
    state += [int.from_bytes(key32[i:i + 4], "little") for i in range(0, 32, 4)]
    state += [counter64 & 0xFFFFFFFF, (counter64 >> 32) & 0xFFFFFFFF]
    state += [nonce64 & 0xFFFFFFFF, (nonce64 >> 32) & 0xFFFFFFFF]
    working = state[:]

    def qr(a: int, b: int, c: int, d: int) -> None:
        working[a] = _u32w(working[a] + working[b]); working[d] = _rol32(working[d] ^ working[a], 16)
        working[c] = _u32w(working[c] + working[d]); working[b] = _rol32(working[b] ^ working[c], 12)
        working[a] = _u32w(working[a] + working[b]); working[d] = _rol32(working[d] ^ working[a], 8)
        working[c] = _u32w(working[c] + working[d]); working[b] = _rol32(working[b] ^ working[c], 7)

    for _ in range(10):
        qr(0, 4, 8, 12)
        qr(1, 5, 9, 13)
        qr(2, 6, 10, 14)
        qr(3, 7, 11, 15)
        qr(0, 5, 10, 15)
        qr(1, 6, 11, 12)
        qr(2, 7, 8, 13)
        qr(3, 4, 9, 14)

    out_words = [_u32w(x + y) for x, y in zip(working, state)]
    return b"".join(w.to_bytes(4, "little") for w in out_words)


def chacha20_xor_64_64(data: bytes, key32: bytes, counter64: int, nonce64: int) -> bytes:
    """XOR data with consecutive `sub_5B6CFF4` ChaCha blocks."""
    out = bytearray()
    block_counter = counter64
    for off in range(0, len(data), 64):
        block = chacha20_block_64_64(key32, block_counter, nonce64)
        chunk = data[off:off + 64]
        out.extend(a ^ b for a, b in zip(chunk, block))
        block_counter = (block_counter + 1) & 0xFFFFFFFFFFFFFFFF
    return bytes(out)


def llijl_transform(data: bytes, key8: bytes, salt64: int) -> bytes:
    """Recovered `VM_PROGRAM_LLIJL` output transform for the observed call.

    Verified facts:
      * `sub_5B61D31` calls `sub_5B61848("LLIJL", keyblock, n8, salt,
        srcblock, src_len)`.
      * the bytecode packs up to 32 key bytes into eight little-endian u32 words
        in `r14`.
      * opcode `0x72` calls `sub_5B6CFF4(r5.data, r6.data, r7, r9)`, where
        `r6 = clone(r14)` is the 32-byte ChaCha key buffer.
      * for this native call `n8 == 8`, so key32 is `key8 + 24 zero bytes`.
      * the block counter is `offset // 64` and the nonce/tail is `salt64`.
    """
    if len(key8) != 8:
        raise ValueError("LLIJL caller passes an 8-byte key object")
    return NativeWrappingVM(VM_PROGRAM_LLIJL).run_llijl(key8, salt64, data)


def _crc32_table() -> list[int]:
    table = []
    for i in range(256):
        crc = i
        for _ in range(8):
            if crc & 1:
                crc = (crc >> 1) ^ 0xEDB88320
            else:
                crc >>= 1
        table.append(crc & 0xFFFFFFFF)
    return table


CRC32_TABLE = _crc32_table()


def native_crc16_from_crc32(data: bytes) -> int:
    """Opcode 0x78 checksum used by VM_PROGRAM_MAIN.

    Native starts from `0xffffffff`, applies the standard CRC32 table update,
    then stores `bswap16((~crc >> 16) & 0xffff)` into a scalar slot.
    """
    crc = 0xFFFFFFFF
    for b in data:
        crc = CRC32_TABLE[(crc ^ b) & 0xFF] ^ (crc >> 8)
    return int.from_bytes(((~crc >> 16) & 0xFFFF).to_bytes(2, "little"), "big")


def native_wrap_digest_recovered(
    module_id: str,
    digest16: bytes,
    extra: bytes = b"",
    env: NativeEnvironment | None = None,
    timestamp_word: int | None = None,
) -> bytes:
    """High-level translation of VM_PROGRAM_MAIN for sub_5B62121.

    This follows the observed bytecode path used by the `LLL` wrapper:
    construct a 20-byte header, run `sub_5B6D9EB` in mode 21, checksum bytes
    4..19, and insert the environment byte at raw output[5].  Native then
    continues with opcode 0x7a, which calls `sub_5B7D768(raw + 2, slot[2])` and
    returns that transformed object from slot r2.  Returning the raw 21-byte
    object is wrong.
    """
    if len(digest16) != 16:
        raise ValueError("digest must be 16 bytes")
    env = env or NativeEnvironment()
    if timestamp_word is None:
        usec = (time.time_ns() % 1_000_000_000) // 1000
        timestamp_word = _bswap32(usec)
    header = bytearray(20)
    header[0] = 0x0C
    header[1] = 0x15
    header[8:12] = (timestamp_word & 0xFFFFFFFF).to_bytes(4, "little")
    header = bytearray(sub_5B6D9EB_transform_skeleton(
        bytes(header),
        scalar=timestamp_word,
        out4=b"",
        n=4,
        mode=21,
        input_obj=digest16,
        aux_obj=extra,
        out8=b"\0" * 8,
        salt64=0x14B7BA9329E934E3,
    ))
    crc_input = bytes(header[4:20])
    checksum = native_crc16_from_crc32(crc_input)
    header[2:4] = checksum.to_bytes(2, "little")

    out = bytearray(21)
    out[0:5] = header[0:5]
    out[5] = env.flags_for_module(module_id)
    out[6:21] = header[5:20]
    return native_tail_wrap_0x7a(bytes(out))


def native_tail_wrap_0x7a(raw21: bytes) -> bytes:
    """Boundary for VM_PROGRAM_MAIN opcode 0x7a / sub_5B7D768.

    Native tail is:

      016a: op_79  mutate raw r7.data[5]
      0170: op_7a  r2 = sub_5B7D768(r7.data + 2, slot[2])
      0178: op_61  return r2

    At this point `slot[2] == 20`, so `sub_5B7D768` constructs a 20-byte object
    from `raw21[2:21]`, overwrites the last byte with 0x04, and runs another
    nested VM with format "LL" over the 0xCC0-byte `src__2` program.
    """
    if len(raw21) != 21:
        raise ValueError("opcode 0x7a tail expects the 21-byte raw r7 object")
    return NativeWrappingVM(VM_PROGRAM_LL).run_ll(build_tail_ll_input(raw21))


def build_tail_ll_input(raw21: bytes) -> bytes:
    """Build the exact object data passed to final `sub_5B7D5DC("LL")`.

    Main VM opcode 0x7a calls `sub_5B7D768(r7.data + 2, slot[2])`; on the
    recovered path slot[2] is 20.  `sub_5B7D768` copies `n-1` bytes and writes
    byte 0x04 at the last logical position.
    """
    if len(raw21) != 21:
        raise ValueError("tail input builder expects raw r7 length 21")
    n = 20
    out = bytearray(n)
    out[:n - 1] = raw21[2:2 + n - 1]
    out[n - 1] = 0x04
    return bytes(out)


def sub_5B754F0_xor_u32_be(data: bytes | bytearray, scalar: int) -> bytes:
    """Recovered child helper used by final `LL` VM opcode 0x7b.

    Native stores `scalar` as four big-endian bytes and XORs them repeatedly
    over the destination buffer.  `sub_5B63952` applies this to the 496-byte
    table payload it copies from the process map.
    """
    key = (scalar & 0xFFFFFFFF).to_bytes(4, "big")
    out = bytearray(data)
    for i in range(len(out)):
        out[i] ^= key[i & 3]
    return bytes(out)


def sub_5B63952_extract_magic_table(mapped_bytes: bytes, scalar: int) -> bytes | None:
    """Pure-data model of the successful `sub_5B63952` scan.

    The native helper opens `/proc/self/maps`, keeps mappings whose path
    contains `"qq"`, then scans each mapping for this layout:

    ```text
    offset + 0x000: "something magic."        # 16-byte begin marker
    offset + 0x010: 496-byte payload copied to the VM object
    offset + 0x200: "end magic things"        # 16-byte end marker
    ```

    On success it copies the 496-byte payload and calls `sub_5B754F0`, i.e. XORs
    it with the repeated big-endian `scalar`.  This helper lets the final LL VM
    use a dumped/static mapping blob if one is found.  It returns `None` when no
    valid begin/end marker pair is present; native then follows its logging/error
    path instead of producing the table.
    """
    begin = SUB_5B63952_MAGIC_BEGIN
    end = SUB_5B63952_MAGIC_END
    pos = 0
    while True:
        idx = mapped_bytes.find(begin, pos)
        if idx < 0:
            return None
        payload_start = idx + len(begin)
        payload_end = payload_start + 496
        end_start = idx + 0x200
        end_end = end_start + len(end)
        if end_end <= len(mapped_bytes) and mapped_bytes[end_start:end_end] == end:
            return sub_5B754F0_xor_u32_be(mapped_bytes[payload_start:payload_end], scalar)
        pos = idx + 1


def sub_5B6D9EB_transform_skeleton(
    header_obj: bytes,
    scalar: int,
    out4: bytes,
    n: int,
    mode: int,
    input_obj: bytes,
    aux_obj: bytes,
    out8: bytes,
    salt64: int,
) -> bytes:
    """Recovered compound helper for opcode 0x77 / sub_5B6D9EB.

    This function returns the best-current reconstruction.  The VIPII side is
    directly implemented; the LLIJL side follows the recovered ChaCha helper
    path and should be verified against native intermediates. The verified
    native structure is:

      1. VIPII nested VM generates/fills a 4-byte token using custom alphabets.
      2. Native copies token bytes into header[4:8]. header[8:12] was already
         populated by VM_PROGRAM_MAIN from opcode 0x76 timestamp bytes.
      3. An 8-byte key is derived/whitened with RC4.
      4. LLIJL nested VM transforms a constructed string with that key/salt.
      5. MD5 of the LLIJL output is computed; first 8 bytes are stored in out8.
      6. Native copies out8 into header[12:20].
    """
    if len(header_obj) < 20:
        raise ValueError("sub_5B6D9EB header object is at least 20 bytes")
    if mode not in (20, 21):
        raise ValueError("sub_5B61F70 accepts only modes 20 and 21")
    key8 = derive_sub_5B6D9EB_key8(input_obj, aux_obj, scalar, n, mode)
    token = vipii_generate_token(scalar, n, mode)
    llijl_input = input_obj + (scalar & 0xFFFFFFFF).to_bytes(4, "little")
    digest8 = md5(llijl_transform(llijl_input, key8, salt64)).digest()[:8]
    out = bytearray(header_obj)
    out[4:4 + len(token)] = token
    out[12:20] = digest8
    return bytes(out)


def build_sub_5B6D9EB_header_layout(token4: bytes, timestamp4: bytes, digest8: bytes) -> bytes:
    """Assemble the 20-byte object seeded in VM_PROGRAM_MAIN and completed by 0x77.

    Confirmed writes:
      * header[0] = 0x0c
      * header[1] = 0x02
      * header[2:4] are filled later with length 0x0015 by VM_PROGRAM_MAIN
      * header[4:8] = VIPII token bytes copied by sub_5B6D9EB line 668
      * header[8:12] = timestamp bytes written before opcode 0x77
      * header[12:20] = MD5(LLIJL_output)[0:8], copied at line 2477
    """
    if len(token4) != 4 or len(timestamp4) != 4 or len(digest8) != 8:
        raise ValueError("expected token4/timestamp4/digest8 lengths 4/4/8")
    return b"\x0c\x02\x15\x00" + token4 + timestamp4 + digest8


class NativeWrapper:
    """
    Placeholder for sub_5B62121/sub_5B61AFB/sub_5B64F10.

    IDA evidence:
      * sub_55658EF passes module_id, 16-byte MD5 digest, and empty string.
      * sub_5B62121 creates two small length+pointer blocks and calls
        sub_5B61AFB(module_id, "LLL", block_for_digest, block_for_extra, ...).
      * sub_5B61AFB copies a 0x17a byte static table (src_), parses varargs,
        then sub_5B64F10 returns an allocated output buffer.

    The wrapper is a small custom bytecode VM, not an exported library call.
    The bytecode used by the digest wrapper is embedded above as
    VM_PROGRAM_MAIN (0xD57090, 0x17a bytes).  A full independent implementation
    requires implementing that VM; this class is the pure-Python boundary for it.
    """

    def __init__(
        self,
        wrap_digest: Optional[Callable[[str, bytes, bytes], bytes]] = None,
        env: NativeEnvironment | None = None,
    ):
        self._wrap_digest = wrap_digest
        self.env = env or NativeEnvironment()

    def wrap_digest(self, module_id: str, digest16: bytes, extra: bytes = b"") -> bytes:
        if len(digest16) != 16:
            raise ValueError("sub_55658EF passes a raw 16-byte MD5 digest")
        if self._wrap_digest is None:
            return native_wrap_digest_recovered(module_id, digest16, extra, self.env)
        return self._wrap_digest(module_id, digest16, extra)


class SecurityState:
    """
    Minimal model of globals reached through sub_5570126/sub_5564244.

    enabled == *(sub_5570126()+1)
    mode    == *(sub_5564244()+160)
    tamper_flag == dword_79ED398, set by the wrapper.node dladdr check.

    Native `a1` is a C++ object with 24-byte std::string-like slots, not a flat
    POD struct.  The initializer copies:
      a1+16  = data directory/base path
      a1+40  = secondary path/config string
      a1+64  = QUA/version
      a1+88  = UIN
      a1+112 = GUID
    `sub_2BF4E50` then passes a five-pointer array to global init:
      [data_dir, runtime_session_string, qua, uin, guid]
    where runtime_session_string comes from sub_29FF8E0/sub_29FFC30, not from
    `a1`.  See analyze/a1_structure.md for the full audit.
    """

    def __init__(self):
        self.enabled = True
        self.mode = 0
        self.tamper_flag = False
        # Signer-relevant fields carried by the `self`/A1 structure passed to
        # sub_2BF4E50.  Native copies a1+64/+88/+112 into global SDK/security
        # config in sub_5575184 -> sub_557566C -> sub_557E8BA.  Other A1 slots
        # (data directory and secondary path/config) are broader SDK init inputs
        # and are documented in analyze/a1_structure.md.
        self.qua = "V1_LNX_NQ_3.2.22_42941_GW_B"
        self.uin = "0"
        self.guid = "14dd2dee2a8321b8f3461a197ee0b7a2"
        self.cached_key_material = b""
        # Optional verified override for the protobuf field emitted by
        # sub_556440D.  If absent, native's default global config value at
        # sub_5564244()+64 is the QUA/version string copied from A1+64.
        self.config_seed = b""
        self.ecdh_field1_override: bytes | None = None

    def get_or_refresh_key_material(self) -> bytes:
        """Reconstruction of sub_5555707 at the call boundary.

        The native function is heavily flattened and Hex-Rays reports a bad SP.
        Its role is nevertheless clear from callers: it returns a string, uses
        mutexes/time(0), checks cache TTL, and refreshes/stores ECDH material.
        """
        return self.cached_key_material


def msf_sign(
    state: SecurityState,
    module_id: str,
    payload: bytes,
    sign_type: int,
    wrapper: Optional[NativeWrapper] = None,
) -> SignParts:
    """Readable equivalent of sub_2BF4E50 after one-time init is complete."""
    packed = generate_security_sign_parts(
        state=state,
        module_id=module_id,
        payload=payload,
        sign_type=sign_type,
        wrapper=wrapper or NativeWrapper(),
    )
    return SignParts(
        key_material=packed.part0_key_material,
        ecdh_blob=packed.part1_ecdh_blob,
        signature=packed.part2_signature,
    )


def generate_security_sign_parts(
    state: SecurityState,
    module_id: str,
    payload: bytes,
    sign_type: int,
    wrapper: NativeWrapper,
    image_path: str = "wrapper.node",
) -> PackedThreeStrings768:
    """Readable equivalent of sub_557A6A0."""
    # Native anti-tamper check: dladdr(return_address).dli_fname must contain
    # the decoded literal "wrapper.node".  Failure sets dword_79ED398 = 1.
    state.tamper_flag = "wrapper.node" not in image_path

    sign_type_s = str(sign_type).encode("ascii")
    signature = build_encrypted_md5_signature(state, module_id, sign_type_s, payload, wrapper)
    ecdh_blob = build_ecdh_access_blob(state, module_id, payload)
    key_material = state.get_or_refresh_key_material()

    return PackedThreeStrings768(
        part0_key_material=key_material,
        part1_ecdh_blob=ecdh_blob,
        part2_signature=signature,
    )


def build_encrypted_md5_signature(
    state: SecurityState,
    module_id: str,
    sign_type_s: bytes,
    payload: bytes,
    wrapper: NativeWrapper,
) -> bytes:
    """Readable equivalent of sub_55658EF.

    The MD5 implementation is inlined in native code with standard IV,
    padding, constants and rotations.  IDA evidence:
      * constants -680876936, -389564586, 606105819, ...
      * rotates 7/12/17/22, 5/9/14/20, 4/11/16/23, 6/10/15/21
      * standard 0x80 MD5 padding table byte_79ED3A0
    """
    if not state.enabled:
        return b""

    # Special mode at sub_55658EF:994: if sign_type_s is non-empty and
    # *(sub_5564244()+160) == 1, hash only the decimal sign_type string.
    if sign_type_s and state.mode == 1:
        digest = md5(sign_type_s).digest()
        return wrapper.wrap_digest(module_id, digest, b"")

    # Normal mode at sub_55658EF:1696-1701:
    #   material = sub_5555707() + sub_556440D(module, payload) + payload
    material = (
        state.get_or_refresh_key_material()
        + build_ecdh_access_blob(state, module_id, payload)
        + payload
    )
    digest = md5(material).digest()
    return wrapper.wrap_digest(module_id, digest, b"")


def build_ecdh_access_blob(state: SecurityState, module_id: str, payload: bytes) -> bytes:
    """Readable boundary reconstruction of sub_556440D.

    Two obfuscated service literals decode to:
      * trpc.o3.ecdh_access.EcdhAccess.SsoEstablishShareKey
      * trpc.o3.ecdh_access.EcdhAccess.SsoSecureAccess

    For those modules, native code calls sub_58FC982/sub_55455F8 to fill field1
    using the payload/body bytes.  That producer is not replaced with a fake
    value here: callers must provide a verified override until it is translated.
    It then serializes up to three length-delimited fields with tags 0x0a,
    0x12, 0x1a.  This is protobuf wire type 2.

    The exact field producers depend on global obj_ state.  Non-special modules
    still serialize the recovered config_seed field when present.
    """
    field1 = b""
    # Long-running init trace confirms non-special calls serialize field #2 as
    # exactly: 0x12, len(QUA), QUA.  This comes from sub_5564244()+64, populated
    # from the A1/self QUA at sub_2BF4E50 a1+64.  Keep config_seed as an escape
    # hatch for verified native samples with a different global slot value.
    field2 = state.config_seed or state.qua.encode("utf-8")
    field3 = b""

    if module_id in (SSO_ESTABLISH_SHARE_KEY, SSO_SECURE_ACCESS):
        if state.ecdh_field1_override is None:
            raise NotImplementedError(
                "sub_556440D special ECDH field1 uses payload via "
                "sub_58FC982/sub_55455F8 and is not translated yet; provide "
                "ecdh_field1_override from a verified native sample"
            )
        field1 = state.ecdh_field1_override

    out = bytearray()
    _append_len_delimited(out, 1, field1)
    _append_len_delimited(out, 2, field2)
    _append_len_delimited(out, 3, field3)
    return bytes(out)


def decode_native_obfuscated_string(encoded: bytes, n: int, mode: str = "and_or") -> str:
    """Decoder for the string-obfuscation loops seen in this cluster."""
    key = encoded[0]
    src = encoded[1:]
    out = bytearray()
    for i, b in enumerate(src[:n]):
        if mode == "xor_linear":
            out.append(b ^ key ^ (i + 1) ^ n)
        else:
            out.append(b ^ (((i + 1) & ~key) | (key & (-2 - i))) ^ n)
    return out.rstrip(b"\0").decode("latin1")


def _append_len_delimited(out: bytearray, field_no: int, value: bytes) -> None:
    if not value:
        return
    out.extend(_varint((field_no << 3) | 2))
    out.extend(_varint(len(value)))
    out.extend(value)


def _varint(n: int) -> bytes:
    result = bytearray()
    while n >= 0x80:
        result.append((n & 0x7F) | 0x80)
        n >>= 7
    result.append(n)
    return bytes(result)


def _pack_255(data: bytes) -> bytes:
    if len(data) > 255:
        raise ValueError("native output slot length is one byte; max 255")
    return data.ljust(255, b"\0") + bytes([len(data)])
