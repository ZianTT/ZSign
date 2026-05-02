# rewrapper

`rewrapper` 是一个面向 Linux QQ / Lagrange 的本地签名服务实现，用于在不加载
`wrapper.node`、不依赖 Frida 的情况下，提供与 ZSign / Lagrange 签名接口形态兼容的
HTTP API。

> 注意：本项目包含逆向分析结果和签名链重建代码，仅限授权研究与内部部署使用。

## 重要声明

1. **部署实例必须提前知会作者。**
   - 任何公网、内网共享、容器化托管、多人共用实例，均需在部署前告知作者实例用途、部署位置和访问范围。
2. **严禁泄露本项目的存在和源码。**
   - 不得公开仓库地址、源码片段、实现细节、接口地址、分析文档或部署方式。
   - 不得转发给无关人员，不得上传到公开代码平台、网盘、论坛、聊天群或任何第三方服务。
3. **严禁将本项目用于未授权用途。**
   - 使用者需要自行确保使用场景合法、合规，并承担全部后果。
4. **不要公开暴露签名服务。**
   - 默认建议只监听 `127.0.0.1`。
   - 如确需远程访问，必须加访问控制、网络隔离和最小权限策略。

## 功能

- 提供 ZSign 风格接口：
  - `POST /api/sign/<version_code>`
- 提供 Lagrange.Milky 兼容接口：
  - `POST /api/sign/sec-sign`
- 提供基础管理/调试接口：
  - `GET /`
  - `GET /health`
  - `GET/PUT/DELETE /mng/version_code`
  - `GET/POST /api/sign/<version_code>/appinfo`
  - `GET/POST /api/sign/<version_code>/appinfo_v2`
- 支持显式控制 native opcode `0x79` 环境检测字节：
  - `env_flags`
  - `madvise_success`
  - `proc_comm`
  - `dword_79ED4F0`
  - `dword_79ED398`
  - `global_i1_52_valid`

## 环境要求

- Python 3.11+
- Flask

安装依赖示例：

```bash
pip install flask
```

## 启动服务

推荐仅本机监听：

```bash
python api_server.py --host 127.0.0.1 --port 5000 --allow-unverified-sign --env-flags 0x00
```

使用 tmux 后台运行：

```bash
tmux new-session -d -s rewrapper-api "python api_server.py --host 127.0.0.1 --port 5000 --allow-unverified-sign --env-flags 0x00"
```

查看日志：

```bash
tmux attach -t rewrapper-api
```

或：

```bash
tmux capture-pane -t rewrapper-api -p -S -100
```

停止服务：

```bash
tmux kill-session -t rewrapper-api
```

健康检查：

```bash
curl http://127.0.0.1:5000/health
```

## Lagrange.Core 使用方式

`Lagrange.Core/Common/BotSignProvider.cs` 兼容的接口地址为：

```text
http://127.0.0.1:5000/api/sign/42941
```

请求格式：

```json
{
  "cmd": "wtlogin.trans_emp",
  "seq": 1,
  "src": "020164"
}
```

返回格式：

```json
{
  "value": {
    "sign": "...",
    "token": "...",
    "extra": "..."
  }
}
```

## Lagrange.Milky 使用方式

`Lagrange.Milky/Utility/Signer.cs` 会自动拼接 `/api/sign/sec-sign`，因此配置中的
Signer URL 填服务根地址即可：

```text
http://127.0.0.1:5000
```

最终请求地址为：

```text
http://127.0.0.1:5000/api/sign/sec-sign
```

Milky 请求格式：

```json
{
  "uin": 10000,
  "command": "wtlogin.trans_emp",
  "seq": 1,
  "body": "020164",
  "guid": "14dd2dee2a8321b8f3461a197ee0b7a2",
  "qua": "V1_LNX_NQ_3.2.22_42941_GW_B"
}
```

Milky 返回格式：

```json
{
  "code": 0,
  "message": "ok",
  "value": {
    "sec_sign": "...",
    "sec_token": "...",
    "sec_extra": "..."
  }
}
```

## 环境检测位说明

默认推荐使用：

```bash
--env-flags 0x00
```

这是正常 Linux QQ / `wrapper.node` 环境下当前确认的环境字节。

如需逐项模拟 native 检测，可通过请求体传入：

```json
{
  "cmd": "wtlogin.trans_emp",
  "seq": 1,
  "src": "020164",
  "env": {
    "env_flags": 0,
    "image_path": "wrapper.node",
    "proc_comm": "qq",
    "madvise_success": false,
    "global_i1_52_valid": true,
    "dword_79ED4F0": 0,
    "dword_79ED398": 0
  }
}
```

位含义：

| Mask | 含义 |
| ---: | --- |
| `0x01` | `madvise(obj_data, 0, 50) != -1` |
| `0x02` | `/proc/<pid>/comm` 不包含 `qq` |
| `0x04` | `/proc/self/maps` 检测到 `frida-agent` |
| `0x08` | 当前映射路径不包含 `wrapper.node` |
| `0x80` | 非 login 模块且全局状态检查失败 |

详细分析见：

```text
analyze/environment_detection.md
```

## 日志

服务会打印签名请求摘要：

```text
[sign] endpoint=milky status=ok cmd=wtlogin.trans_emp seq=1 uin=10000 body_len=3 env_flags=0x00
```

字段说明：

- `endpoint`: `zsign` 或 `milky`
- `status`: `ok` 或 `error`
- `cmd`: 命令名
- `seq`: 序列号
- `uin`: 账号
- `body_len`: 请求体字节长度
- `env_flags`: opcode `0x79` 环境字节

## 项目结构

```text
api_server.py                     # HTTP API 服务
decompiled/signature_algorithm.py # Python 签名链重建实现
script/                           # Frida 研究脚本，仅用于分析验证
analyze/                          # 逆向分析文档
```

关键分析文档：

- `analyze/signing_pipeline.md`
- `analyze/environment_detection.md`
- `analyze/a1_structure.md`

## 注意事项

- `script/` 中 Frida 脚本仅用于研究和 trace，不是运行时依赖。
- 不要使用 Frida attach 状态下的样本作为最终 byte-identical 结论。
- 默认 API 适配当前 Linux QQ 42941 / QUA：
  - `V1_LNX_NQ_3.2.22_42941_GW_B`
- 如修改 QUA、GUID、UIN、环境位或 key material，应重新做 native 对照验证。
