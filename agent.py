# ==================================
# Copyright 2025 ZianTT
# All rights reserved.
# DO NOT SHARE THIS FILE WITH ANYONE WHO DO NOT HAVE THE ACCESSS
# ==================================
import ctypes
from flask import Flask, request, jsonify
import sys
import os
import frida
import time
import threading

VERSION = "3.2.19-39038"
WHITELIST_UINS = []
with open('whitelist.txt', 'r') as f:
    for line in f:
        line = line.strip()
        if line.isdigit():
            WHITELIST_UINS.append(int(line))
VERSION_CODE = []
with open('version_code.txt', 'r') as f:
    for line in f:
        line = line.strip()
        if line:
            VERSION_CODE.append(line)

APPINFO = {
  "AppClientVersion": 39038,
  "AppId": 1600001615,
  "AppIdQrCode": 537313942,
  "CurrentVersion": "3.2.19-39038",
  "Kernel": "Linux",
  "SdkInfo": {
    "MainSigMap": 169742560,
    "MiscBitMap": 32764,
    "SdkVersion": "nt.wtlogin.0.0.1",
    "SubSigMap": 0,
    "SdkBuildTime": 0
  },
  "NTLoginType": 1,
  "Os": "Linux",
  "PackageName": "com.tencent.qq",
  "ApkSignatureMd5": "636f6d2e74656e63656e742e7171",
  "PtVersion": "2.0.0",
  "SsoVersion": 19,
  "SubAppId": 537313942,
  "VendorOs": "linux"
}

class TargetFunctionCaller:
    def __init__(self, target_process):
        self.session = None
        self.script = None
        self.target_process = target_process
        self.app = Flask(__name__)
        self.setup_routes()
        
    def setup_routes(self):
        """设置 HTTP 路由"""
        @self.app.route('/', methods=['GET'])
        def index():
            return jsonify({"status": "ok", "msg": "Welcome to ZSIGN API!"})

        @self.app.route('/health', methods=['GET'])
        def health():
            self_ptr = self.get_self_pointer()
            return jsonify({"status": "ok", "process": self.target_process, "self_pointer": self_ptr})

        @self.app.route('/mng/version_code', methods=['GET', 'PUT', 'DELETE'])
        def manage_version_code():
            if request.method == 'GET':
                return jsonify({"status": "ok", "version_code": VERSION_CODE})
            elif request.method == 'PUT':
                data = request.get_json()
                if 'version_code' in data:
                    if data['version_code'] in VERSION_CODE:
                        return jsonify({"status": "error", "message": "版本号已存在"})
                    VERSION_CODE.append(data['version_code'])
                    with open('version_code.txt', 'w') as f:
                        for version_code in VERSION_CODE:
                            f.write(f"{version_code}\n")
                    return jsonify({"status": "ok", "message": "版本号添加成功"})
                return jsonify({"status": "error", "message": "缺少 version_code 参数"})
            elif request.method == 'DELETE':
                data = request.get_json()
                if 'version_code' in data:
                    if data['version_code'] not in VERSION_CODE:
                        return jsonify({"status": "error", "message": "版本号不存在"})
                    VERSION_CODE.remove(data['version_code'])
                    with open('version_code.txt', 'w') as f:
                        for version_code in VERSION_CODE:
                            f.write(f"{version_code}\n")
                    return jsonify({"status": "ok", "message": "版本号删除成功"})
                return jsonify({"status": "error", "message": "缺少 version_code 参数"})
            return jsonify({"status": "error", "message": "不支持的请求方法"})
        
        @self.app.route('/mng/whitelist', methods=['GET', 'PUT', 'DELETE'])
        def manage_whitelist():
            if request.method == 'GET':
                return jsonify({"status": "ok", "whitelist_uins": WHITELIST_UINS})
            elif request.method == 'PUT':
                data = request.get_json()
                if 'uin' in data and isinstance(data['uin'], int):
                    if data['uin'] in WHITELIST_UINS:
                        return jsonify({"status": "error", "message": "UIN 已存在"})
                    WHITELIST_UINS.append(data['uin'])
                    with open('whitelist.txt', 'w') as f:
                        for uin in WHITELIST_UINS:
                            f.write(f"{uin}\n")
                    return jsonify({"status": "ok", "message": "UIN 添加成功"})
                return jsonify({"status": "error", "message": "缺少或无效的 uin 参数"})
            elif request.method == 'DELETE':
                data = request.get_json()
                if data['uin'] not in WHITELIST_UINS:
                    return jsonify({"status": "error", "message": "UIN 不存在"})
                if 'uin' in data and isinstance(data['uin'], int):
                    WHITELIST_UINS.remove(data['uin'])
                    with open('whitelist.txt', 'w') as f:
                        for uin in WHITELIST_UINS:
                            f.write(f"{uin}\n")
                    return jsonify({"status": "ok", "message": "UIN 删除成功"})
                return jsonify({"status": "error", "message": "缺少或无效的 uin 参数"})
            return jsonify({"status": "error", "message": "不支持的请求方法"})


        @self.app.route('/api/sign/<version_code>/appinfo', methods=['GET', 'POST'])
        def appinfo(version_code):
            if version_code not in VERSION_CODE:
                return jsonify({"status": "error", "message": "版本号不匹配"})
            return jsonify(APPINFO)
        
        @self.app.route('/api/sign/<version_code>/appinfo_v2', methods=['GET', 'POST'])
        def appinfo_v2(version_code):
            if version_code not in VERSION_CODE:
                return jsonify({"status": "error", "message": "版本号不匹配"})
            return jsonify(APPINFO)

        @self.app.route('/api/sign/<version_code>', methods=['POST'])
        def call_function_simple_api(version_code):
            """简化调用接口，只返回 sign 和 extra"""
            if version_code not in VERSION_CODE:
                with open('request.log', 'a', encoding='utf-8') as log_file:
                    log_file.write(f"IP {request.remote_addr} - 版本号不匹配: {version_code} 允许的版本号: {VERSION_CODE}\n")
                return jsonify({"status": "error", "message": "版本号不匹配"})
            try:
                # check if self pointer is available
                # self_ptr = self.get_self_pointer()
                # if not self_ptr:
                #     return jsonify({"status": "error", "message": "尚未捕获完成初始化，请联系管理员"})
                data = request.get_json()
                if not data:
                    return jsonify({"status": "error", "message": "缺少 JSON 数据"})
                
                cmd_str = data.get('cmd', '')
                data_str = data.get('src', '')
                seq = data.get('seq', 0)
                with open('request.log', 'a', encoding='utf-8') as log_file:
                    log_file.write(f"IP {request.remote_addr} - CMD: {cmd_str}, SRC: {data_str}, SEQ: {seq}\n")
                
                if not cmd_str or not data_str:
                    return jsonify({"status": "error", "message": "缺少必要参数"})
                
                if cmd_str == "wtlogin.login":
                    if data_str != "0b2d0e":
                        uin_hex = data_str[18:26]
                        uin = int(uin_hex, 16)
                        if uin not in WHITELIST_UINS:
                            return jsonify({"status": "error", "message": "UIN 不在白名单内"})
                
                result = self.call_function(cmd_str, data_str, seq)
                
                if result:
                    response_data = {
                        "platform": "Linux",
                        "value": {
                            "sign": result.get('sign', ''),
                            "extra": result.get('extra', ''),
                            "token": result.get('token', ''),
                        },
                        "version": VERSION,
                    }
                    if 'error' in result:
                        with open('request.log', 'a', encoding='utf-8') as log_file:
                            log_file.write(f"IP {request.remote_addr} - 错误: {result['error']}\n")
                        response_data['error'] = result['error']
                    return jsonify(response_data)
                else:
                    return jsonify({"status": "error", "message": "函数调用失败"})
                    
            except Exception as e:
                with open('request.log', 'a', encoding='utf-8') as log_file:
                    log_file.write(f"IP {request.remote_addr} - 调用异常: {str(e)}\n")
                return jsonify({"status": "error", "message": f"调用异常: {str(e)}"})

    def start_http_server(self, host='0.0.0.0', port=5000):
        """启动 HTTP 服务器"""
        def run_flask():
            self.app.run(host=host, port=port, debug=False, use_reloader=False)
        
        flask_thread = threading.Thread(target=run_flask, daemon=True)
        flask_thread.start()
        print(f"HTTP API 服务器已启动: http://{host}:{port}")
    
    def detach(self):
        """分离进程"""
        if self.session:
            self.session.detach()
            print("已分离进程")

    def attach(self):
        """附加到目标进程"""
        try:
            if self.target_process.isdigit():
                # 按 PID 附加
                self.session = frida.attach(int(self.target_process))
            else:
                # 按进程名附加
                self.session = frida.attach(self.target_process)
                
            with open('agent2.js', 'r', encoding='utf-8') as f:
                script_code = f.read()
                
            self.script = self.session.create_script(script_code)
            self.script.load()
            
            print(f"成功附加到进程: {self.target_process}")
            return True
            
        except Exception as e:
            print(f"附加到进程失败: {e}")
            return False
        
    def get_self_pointer(self):
        """获取从 hook 中捕获的 self 指针"""
        try:
            # self_ptr = self.script.exports_sync.getself()
            self_ptr = "NO SELF POINTER ANYMORE"
            if self_ptr:
                print(f"获取到 self 指针: {self_ptr}")
                return self_ptr
            else:
                print("尚未捕获到 self 指针，请先触发原函数调用")
                return None
        except Exception as e:
            print(f"获取 self 指针失败: {e}")
            return None
    
    def call_function(self, cmd_str, data_str, seq=0):
        """调用目标函数"""
        try:
            # 首先获取 self 指针
            # self_ptr = self.get_self_pointer()
            # if not self_ptr:
            #     return None
            self_ptr = 0x1  # 占位符，实际调用中应使用真实 self 指针
            result = self.script.exports_sync.sign(
                self_ptr, cmd_str, data_str, seq
            )
            
            print("调用结果:")
            print(f"  Sign: {result.get('sign', 'N/A')}")
            print(f"  Extra: {result.get('extra', 'N/A')}")
            print(f"  Token: {result.get('token', 'N/A')}")
            
            if 'error' in result:
                print(f"  错误: {result['error']}")
                
            return result
            
        except Exception as e:
            print(f"调用函数失败: {e}")
            return None

def main():
    if len(sys.argv) < 2:
        print("用法: python call_function.py [端口]")
        return
    
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 5000
    
    target_process = "/opt/QQ/qq"
    def run_qq():
        os.environ['DISPLAY'] = ':1.0'
        os.system(f"{target_process}")
    threading.Thread(target=run_qq, daemon=True).start()
    time.sleep(2)
    # get the pid of the target process
    pid = os.popen(f"pidof {target_process}").read().strip().split()[-1]
    if not pid:
        print("目标进程启动失败")
        return
    
    time.sleep(10)

    caller = TargetFunctionCaller(pid)
    
    if not caller.attach():
        return
    
    
    # 启动 HTTP 服务器
    caller.start_http_server(port=port)

    # print("等待捕获 self 指针...")
    # while not caller.get_self_pointer():
    #     time.sleep(2)

    try:
        while True:
            time.sleep(10)
            with open('whitelist.txt', 'r') as f:
                temp_whitelist = []
                for line in f:
                    line = line.strip()
                    if line.isdigit():
                        temp_whitelist.append(int(line))
                global WHITELIST_UINS
                WHITELIST_UINS = temp_whitelist
            with open('version_code.txt', 'r') as f:
                global VERSION_CODE
                temp_version_code = []
                for line in f:
                    line = line.strip()
                    if line:
                        temp_version_code.append(line)
                VERSION_CODE = temp_version_code
    except KeyboardInterrupt:
        print("收到退出信号，正在关闭...")
        caller.detach()

if __name__ == "__main__":
    main()
