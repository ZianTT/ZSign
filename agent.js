/* 
 * Copyright 2025 ZianTT
 * All rights reserved.
 * DO NOT SHARE THIS FILE WITH ANYONE WHO DO NOT HAVE THE ACCESSS
 */
const module = Process.getModuleByName("wrapper.node");
if (module == null)
   throw new Error(`Module wrapper.node not found!`);

const baseAddr = module.base;
console.log('module:', module.name, "base:", baseAddr);

let g_selfPtr = null;
//
class NTStr {
    constructor(p) {
        // 'NativePointer' is assumed to be a globally available object or an import 
        // in the execution environment (like Frida).
        this.p = p;
    }
    get len() {
        // Assuming 'p' is a NativePointer object with a 'readU8' method
        return this.p.readU8() >> 1;
    }

    // Getter for 'data'
    get data() {
        try {
            // Read the first byte to check the "short string" flag (lowest bit)
            if ((this.p.readU8() & 1) === 0) {
                // Short string (SSO - Small String Optimization)
                const length = this.p.readU8() >> 1; // Length is stored in the high 7 bits
                if (length > 0) {
                    const data = this.p.add(1).readByteArray(length);
                    let data_arr = new Uint8Array(data);
                    return this.bytesToHex(data_arr);
                }
                return "";
            } else {
                // Long string
                const size = this.p.add(Process.pointerSize).readPointer().toInt32();
                const ptr = this.p.add(2 * Process.pointerSize).readPointer();
                
                if (size > 0 && !ptr.isNull()) {
                    const data = ptr.readByteArray(size);
                    let data_arr = new Uint8Array(data);
                    return this.bytesToHex(data_arr);
                }
                return "";
            }
        } catch (e) {
            console.log("Error reading string data: " + e);
            return "";
        }
    }

    // 辅助函数：将字节数组转换为十六进制字符串
    bytesToHex(bytes) {
        if (!bytes) return "";
        let hex = '';
        for (let i = 0; i < bytes.length; i++) {
            hex += ('0' + bytes[i].toString(16)).slice(-2);
        }
        return hex;
    }

    // toString method for logging/debugging
    toString() {
        return `NTStr(${this.data})`;
    }
}

class SignReqData {
    constructor(p) {
        this.p = p;
    }
    
    get dataStartPtr() {
        return this.p.readPointer();
    }
    
    get dataEndPtr() {
        return this.p.add(8).readPointer();
    }
    
    get dataSize() {
        const start = this.dataStartPtr;
        const end = this.dataEndPtr;
        return end.sub(start).toInt32();
    }
    
    get data() {
        const startPtr = this.dataStartPtr;
        const size = this.dataSize;
        try {
            return startPtr.readByteArray(size);
        } catch (e) {
            console.log(`Error reading data: ${e}`);
            return null;
        }
    }
    
    toString() {
        const size = this.dataSize;
        const data = this.data;
        if (data === null) {
            return `SignReqData(dataSize=${size}, data=null)`;
        }
        
        let dataHex = "";
        const dataLength = data.byteLength;
        
        // 将 ArrayBuffer 转为 Uint8Array 来访问字节
        const uint8Array = new Uint8Array(data);
        
        for (let i = 0; i < dataLength; i++) {
            dataHex += ("0" + uint8Array[i].toString(16)).slice(-2);
        }
        return `SignReqData(dataSize=${size}, data=${dataHex})`;
    }
}

// CREATOR

function hexToUtf8(hexString) {
    // 移除可能的空格和前缀
    hexString = hexString.replace(/[^0-9A-Fa-f]/g, '');
    
    // 将 HEX 字符串转换为字节数组
    let bytes = [];
    for (let i = 0; i < hexString.length; i += 2) {
        bytes.push(parseInt(hexString.substr(i, 2), 16));
    }
    
    // UTF-8 解码
    let result = '';
    let i = 0;
    
    while (i < bytes.length) {
        let byte1 = bytes[i];
        
        if (byte1 < 0x80) {
            // 单字节字符 (0xxxxxxx)
            result += String.fromCharCode(byte1);
            i += 1;
        } else {
            // do not handle
            i+= 1;
        }
    }
    
    return result;
}

function utf8ByteLength(str) {
    if (!str) return 0;
    return encodeURIComponent(str).replace(/%[0-9A-F]{2}/g, 'x').length;
}

function writeUtf8Safe(dest, str) {
    if (typeof dest.writeUtf8String === 'function') {
        dest.writeUtf8String(str);
        return;
    }
    var encoded = encodeURIComponent(str);
    var bytes = [];
    for (var i = 0; i < encoded.length;) {
        if (encoded[i] === '%') {
            bytes.push(parseInt(encoded.substr(i + 1, 2), 16));
            i += 3;
        } else {
            bytes.push(encoded.charCodeAt(i));
            i++;
        }
    }
    for (var j = 0; j < bytes.length; j++) dest.add(j).writeU8(bytes[j]);
    dest.add(bytes.length).writeU8(0);
}

/* ---------- Creators for NTStr (short/long) and SignReqData ---------- */

let cmdptr = null;

function createShortNTStr(str) {
    // SSO layout: header byte low bit == 0, length stored in high 7 bits >>1
    // We'll store header byte = (len << 1)
    const len = utf8ByteLength(str);
    if (len > 0x7F) throw new Error('String too long for SSO');
    // const p = Memory.alloc(1 + len + 1); // header + data + NUL
    cmdptr = Memory.alloc(1 + len + 1);
    cmdptr.writeU8((len << 1) & 0xFE); // low bit 0, length in high bits
    writeUtf8Safe(cmdptr.add(1), str);
    return cmdptr;
}

function createLongNTStr(str) {
    const size = utf8ByteLength(str);
    const psize = Process.pointerSize;
    const headerSize = 1 + 2 * psize;
    // const p = Memory.alloc(headerSize);
    cmdptr = Memory.alloc(headerSize);
    // header low bit = 1
    cmdptr.writeU8(1);
    for (let i = 1; i < headerSize; i++) cmdptr.add(i).writeU8(0);
    const dataPtr = Memory.alloc(size + 1);
    writeUtf8Safe(dataPtr, str);
    // write size as a pointer value so readPointer().toInt32 returns size (matching original reader)
    cmdptr.add(psize).writePointer(ptr(size));
    cmdptr.add(2 * psize).writePointer(dataPtr);
    return cmdptr;
}

function createNTStrAuto(str) {
    const size = utf8ByteLength(str);
    if (size <= 0x7F) return createShortNTStr(str);
    return createLongNTStr(str);
}

let dataPtr = null;

let dataStructPtr = null;

function createSignReqDataFromByteArray(byteArray) {
    const size = byteArray.length;
    if (dataPtr === null) dataPtr = Memory.alloc(size);
    dataPtr.writeByteArray(byteArray);
    if (dataStructPtr === null) dataStructPtr = Memory.alloc(2 * Process.pointerSize);
    dataStructPtr.writePointer(dataPtr);
    dataStructPtr.add(Process.pointerSize).writePointer(dataPtr.add(size));
    return dataStructPtr;
}

function createSignReqDataFromString(str) {
    // hex str to byte array
    const byteArray = [];
    for (let i = 0; i < str.length; i += 2) {
        byteArray.push(parseInt(str.substr(i, 2), 16));
    }
    return createSignReqDataFromByteArray(byteArray);
}

function cleanUp() {
    if (dataPtr !== null) {
        dataPtr = null;
    }
    if (dataStructPtr !== null) {
        dataStructPtr = null;
    }
    if (cmdptr !== null) {
        cmdptr = null;
    }
}

function analyzeA1Structure(a1) {
    console.log("前16字节内存:");
    console.log(hexdump(a1, { length: 16, header: true, ansi: true }));
    console.log("Calculated values:");
    console.log("  start: " + new NTStr(a1));
    console.log("  v8: " + new NTStr(a1.add(16)));
    console.log("  v9: " + new NTStr(a1.add(40)));
    console.log("  v10: " + new NTStr(a1.add(64)));
    console.log("  v11: " + new NTStr(a1.add(88)));
    console.log("  v12: " + new NTStr(a1.add(112)));

}

let v8 = createNTStrAuto("");
let v9 = createNTStrAuto("");
let v10 = createNTStrAuto("V1_LNX_NQ_3.2.19_39038_GW_B"); //V1_LNX_NQ_3.2.19_39038_GW_B
let v11 = createNTStrAuto("0"); //UIN
let v12 = createNTStrAuto("c36a9912b1eba21237cf0f2e6d74b01c");

function createA1Structure() {
    const a1 = Memory.alloc(128);
    a1.add(8).writeU8(0x01);
    a1.add(16).writePointer(v8);
    a1.add(40).writePointer(v9);
    a1.add(64).writePointer(v10);
    a1.add(88).writePointer(v11);
    a1.add(112).writePointer(v12);
    return a1;
}

let a1s = createA1Structure();


// IDA中的地址 (Adjust this offset based on your architecture if necessary, 0x05ADE231 is large)
const targetAddr = baseAddr.add(0x28F3310); 
console.log('targetAddr:', targetAddr);

Interceptor.attach(targetAddr, {
    onEnter: function (args) {
        // cleanUp();

        console.log('onEnter:');
        console.log(`\targ[0] (Self): ${args[0]}`);
        console.log(`\targ[1] (Cmd): ${args[1]}`);
        console.log(`\targ[2] (Data): ${args[2]}`);

        g_selfPtr = args[0];
        this.a4 = args[3];
        // to uint32
        this.seq = args[4]>>>0;
        console.log(`\targ[4] (Seq): ${this.seq}`);

        if (args[0].isNull()) {
            console.log('\tSelf: [Skipping: Address is null or length is zero]');
        } else {
            analyzeA1Structure(args[0]);
        }
        
        // --- Read and print args[1] content ---
        if (args[1].isNull()) {
            console.log('\tCmd: [Skipping: Address is null or length is zero]');
        } else {
            try {
                console.log('\tCmd Content (Hex Dump):');
                console.log(new NTStr(args[1])); // Read up to 100 bytes for display
            } catch (e) {
                console.error(`\tError reading Cmd at ${args[1]}：${e}`);
            }
        }

        // --- Read and print args[2] content ---
        if (args[2].isNull()) {
            console.log('\tData: [Skipping: Address is null or length is zero]');
        } else {
            try {
                // Assuming args[2] also has the same length args[2]
                console.log('\tData Content (Hex Dump):');
                console.log(new SignReqData(args[2])); // Read up to 100 bytes for display
            } catch (e) {
                console.error(`\tError reading Data at ${args[2]}：${e}`);
            }
        }

        // // try to change cmd and data to self created
        // console.log(`--- Try to change cmd and data to self created ---`);
        // let cmd_hex = new NTStr(args[1]).data;
        // const cmd_utf8 = hexToUtf8(cmd_hex);
        // console.log(`\tCmd (UTF-8): ${cmd_utf8}`);
        // const cmd = createNTStrAuto(cmd_utf8);
        // let data_hex_buf = new SignReqData(args[2]).data;
        // // buffer to hex string
        // let dataHex = "";
        // const dataLength = data_hex_buf.byteLength;
        // const uint8Array = new Uint8Array(data_hex_buf);
        // for (let i = 0; i < dataLength; i++) {
        //     dataHex += ("0" + uint8Array[i].toString(16)).slice(-2);
        // }
        // console.log(`\tData (Hex): ${dataHex}`);
        // const data = createSignReqDataFromString(dataHex);
        // // const data = createSignReqDataFromByteArray(uint8Array);

        // // test if cmd and data are valid
        // console.log(`\tCmd (Created): ${new NTStr(cmd)}`);
        // console.log(`\tData (Created): ${new SignReqData(data)}, addr: ${data}`);

        // // replace args[1] and args[2] with self created
        // args[1] = cmd;
        // args[2] = data;
        
        // --- Print backtrace ---
        console.log('\nBacktrace:');
        console.log(Thread.backtrace(this.context, Backtracer.ACCURATE).map(DebugSymbol.fromAddress).join('\n'));
        console.log('---');
    },
    
    onLeave: function (retval) {
        console.log('onLeave:', retval);
        retval.replace(1)
        console.log('==================================================');
        
        // --- Read and print a3 content ---
        if (!this.a4.isNull()) {
            console.log("\n[Output Buffer Analysis]");
            let part1Str = new NTStr(this.a4);
            console.log("  Token: ")
            console.log(part1Str);
            
            let part2Str = new NTStr(this.a4.add(24));
            console.log("  Extra: ")
            console.log(part2Str);
            
            let part3Str = new NTStr(this.a4.add(48));
            console.log("  Sign: ")
            console.log(part3Str);
        } else {
            console.log("  [Nullptr: Output Buffer is null]");
        }
    }
});

Interceptor.attach(module.findExportByName("dladdr"), {
    onEnter: function (args) {
        this.arg0 = args[0];  // 要查询的地址
        this.arg1 = args[1];  // Dl_info 结构体指针
        
        console.log("[dladdr] called:");
        console.log("  Address to query: " + this.arg0);
        console.log("  Dl_info struct: " + this.arg1);
        
        // 打印调用栈
        console.log("  Backtrace:");
        Thread.backtrace(this.context, Backtracer.ACCURATE)
            .map(DebugSymbol.fromAddress)
            .forEach(function (frame) {
                console.log("    " + frame);
            });
    },
    onLeave: function(retval) {
        console.log("[dladdr] return: " + retval);
        // print Dl_info struct
        console.log("  Dl_info struct content:");
        console.log("    dli_fname: " + this.arg1.readPointer().readCString());
    }
});

rpc.exports = {
    // 获取捕获到的 self 指针
    getself: function() {
        if (g_selfPtr) {
            return g_selfPtr.toString();
        }
        return null;
    },
    
    // 直接调用目标函数
    sign: function(selfPtr, cmdStr, dataStr, seq) {
        try {
            cleanUp();
            // 创建参数
            // const self = ptr(selfPtr);
            const self = a1s;
            const cmd = createNTStrAuto(cmdStr);
            const data = createSignReqDataFromString(dataStr);
            const outputBuffer = Memory.alloc(72); // 分配输出缓冲区
            console.log(`\tCmd (Called): ${new NTStr(cmd)}`);
            console.log(`\tData (Called): ${new SignReqData(data)}, addr: ${data}`);
            
            // 调用函数
            const func = new NativeFunction(targetAddr, 'int', ['pointer', 'pointer', 'pointer', 'pointer', 'uint']);
            const result = func(self, cmd, data, outputBuffer, seq);
            
            // 读取输出结果
            let output = {
                extra: new NTStr(outputBuffer.add(24)).data,
                sign: new NTStr(outputBuffer.add(48)).data,
                token: new NTStr(outputBuffer).data,
            };
            
            return output;
        } catch (e) {
            return {error: e.toString()};
        }
    },
};

console.log('hooked!!!');
console.log('==================================================');
