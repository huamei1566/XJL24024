# DemoUI2 - 遥测遥控上位机软件

## 项目概述

DemoUI2 是一个基于 Qt 开发的上位机软件，用于遥测遥控（Telemetry and Telecommand）系统的监控和控制。该软件支持双发射机管理、安控配置、GNSS 定位等功能。

## 项目信息

- **项目名称**: DemoUI2 / moliqi
- **框架**: Qt 5.x (C++14)
- **目标平台**: Windows
- **构建工具**: qmake

## 核心功能

### 1. 双发射机控制
- 支持发射机1（TX1）和发射机2（TX2）的独立控制
- 频率设置（1750000-1850000 KHz）
- 调制参数配置（调制极性、调制开关、载波开关、调制方式）
- 功率控制
- 模飞文件数据发送

### 2. 遥测参数配置
- **PCM 配置**: 源码率、子帧长度、副帧配置
- **帧格式配置**: 同步码、帧类型、数据类型
- **编码配置**: LDPC、TPC、RS、卷积编码开关
- **异步源配置**: 台阶码/随机码模式

### 3. 安控（安全控制）配置
- DPSK-FM 模式支持
- 主字母模式支持
- 四路（K1-K4）指令配置
- 载波/副载波频率设置
- 指令码率、前导码、同步码配置

### 4. GNSS 定位
- GPS/GLONASS/BDS 多系统支持
- 定位数据实时显示
- 卫星信息监控

### 5. 网络通信
- UDP 协议通信
- 组播支持（224.1.1.4）
- 多线程数据处理
- 数据回放功能

## 项目结构

```
demoUI2/
├── main.cpp                 # 程序入口
├── mainwindow.h/cpp        # 主窗口
├── mstrut.h                # 数据结构定义（通信协议）
├── worker.h/cpp            # UDP 数据接收处理
├── workerprocessing.h/cpp   # 数据回放处理
├── udpmanager.h/cpp        # UDP 通信管理
├── dialogfasheset.h/cpp   # 发射机设置对话框
├── securitycontrolset.h/cpp # 安控设置对话框
├── telemetrychannelset.h/cpp # 遥测通道设置
├── telemetrypcmset.h/cpp   # PCM 参数设置
├── telemetryradiofrequencyset.h/cpp # 射频参数设置
├── machinestatus.h/cpp    # 机器状态显示
├── gnssworker.h/cpp       # GNSS 数据处理
├── mofeiudpbig.h/cpp      # 模飞大数据处理
├── mofeibufferwrite.h/cpp # 模飞缓冲写入
├── logger.h/cpp           # 日志管理
├── notify.h/cpp           # 通知系统
├── dragdroptablewidget.*  # 拖拽表格组件
├── draggabletable.*       # 可拖拽按钮表格
├── roundbtn.*             # 圆角按钮组件
├── intrangedelegate.*      # 整数范围代理
├── maxlengthdelegate.*    # 最大长度代理
├── squeue.*               # 队列数据结构
├── sreplay.*              # 数据回放
├── src/                   # 第三方库（QtXlsx）
└── qrc/                   # 资源文件
```

## 关键数据结构

### 通信协议头
- `PACKET_HEADER`: 通用包头（同步帧头、功能码、数据长度）
- `TELEMETRY_FRAME`: 遥测帧结构
- `TRANSMIT_CONFIG`: 发射源配置
- `SecuritySourceConfig`: 安控配置

### 功能码定义
| 功能码 | 名称 |
|--------|------|
| 0x01 | 遥测帧格式设置 |
| 0x02 | 读取遥测帧格式 |
| 0x03 | 发射源配置 |
| 0x04 | 遥测编码格式设置 |
| 0x05 | 遥测编码配置 |
| 0x06 | 读取编码配置 |
| 0x07 | PCM 嵌入式配置 |
| 0x08 | 读取 PCM 配置 |
| 0x09 | 异步源配置 |
| 0x0A | 读取异步源配置 |
| 0x0B | 安控配置 |
| 0x0C | 读取安控状态 |

## UI 界面

- **主窗口**: 集成所有控制功能
- **发射机设置**: TX 参数配置
-1/TX2 **安控设置**: K1-K4 指令配置
- **遥测通道**: 通道参数设置
- **PCM 参数**: 码率、同步码等
- **机器状态**: 电压、功率、温度监控
- **文件宏对话框**: 模飞文件管理

## 编译说明

### 环境要求
- Qt 5.x 或更高版本
- C++14 编译器
- Windows 7/10/11

### 编译步骤
```bash
qmake demoUI.pro
make 或 nmake
```

### 运行
编译完成后生成 `moliqi.exe`

## 配置说明

### 网络配置
- 本机接收端口: 10004
- 目标机端口: 10001
- 组播地址: 224.1.1.4
- 本机IP: 192.168.0.100
- 目标机IP: 192.168.0.106

### 配置文件
- `dabaosetting0.ini` - `dabaosetting6.ini`: 预设配置
- `settings.ini`: 系统设置

## 技术特点

1. **多线程架构**: 使用 QThread 实现数据接收、处理、发送分离
2. **UDP 组播**: 支持组播模式进行数据分发
3. **双缓冲机制**: 模飞数据使用双缓冲确保流畅播放
4. **协议解析**: 二进制协议解析，支持多种功能码
5. **位域操作**: 大量使用位域进行标志位操作
6. **资源管理**: Qt 资源系统管理图标等资源

## 依赖库

- Qt5 Core
- Qt5 Gui
- Qt5 Widgets
- Qt5 Network
- QtXlsx (用于 Excel 导出)

## 注意事项

1. 确保网络配置正确，防火墙允许 UDP 端口通信
2. 模飞文件需要符合指定格式
3. 安控配置需要严格按照协议要求设置参数
4. 首次运行需配置发射机和安控参数
