#ifndef MSTRUT_H
#define MSTRUT_H

#include <QtCore>
#include "squeue.h"
#include <QValidator>


class ChannelTrackingStatus;

// 通用包头结构（注意：需要手动处理字节序）
#pragma pack(push, 1)
typedef struct PACKET_HEADER {
      quint32 syncHeader;    // 同步帧头 0xEF91AA55
      quint8  functionCode;  // 功能区分码
      quint32 dataLength;    // 数据长度（小端）
      quint32 totalPackets;  // 总包数（小端）
      quint32 currentPacket; // 当前包号（小端）
  }*PPACKET_HEADER;
#pragma pack(pop)


// set 0x01
#pragma pack(push, 1)
typedef struct TELEMETRY_FRAME {
    quint8  txSelector;        // 发射机选择 [1B]
    quint32 pcmRate;           // PCM信号源码率 [4B]
    union {
        quint16 rawValue;        // 完整的16位值
        struct{
            quint16 length : 15;    // 低15位表示子帧长度-1
            quint16 moFeiFlag : 1;   // 最高位(Bit_15)表示模飞状态标志
        } bit;    // 位域视图
    }subFrameLength;
    quint8  subFrameCount;     // 副帧长 [1B]
    union  {
        quint8 raw;   // 原始的8位数据
        struct {
            quint8 codeType : 4;   // 低4位: 码型 (Bit0~Bit3)
            quint8 wordLengthMinusOne : 4; // 高4位: 字长-1 (Bit4~Bit7)
        } bits;
    }WordConfig;

    quint16 featurePosition;   // 特征副帧位置 [2B]

    quint16 loopSyncCode;      // 循环副帧同步码 [2B]
    quint64 syncCode;          // 子帧同步码[8B]
    quint8  frameType;         // 副帧类型 [1B]
    quint8  reserved1[5];      // 保留字段 [5B]
    quint8  dataType;          // 数据类型 [1B]
    quint16 stepValue;         // 台阶码步进 [2B]
    quint16 initStep;          // 台阶码初始值 [2B]
    union  {
        quint16 value; // 整个16位值
        struct {

            // Bit14 ~ Bit0: 表示帧计数低字节的路序号（实际值减一存储）
            quint16 frameCountLowByteIndex : 15; // 低15位
            // Bit15: 0表示使能计数，1表示不使能计数
            quint16 notCountEnable : 1;   // 第15位（最高位）
        } bits;
    }FrameCalcChannel;
    union  {
        quint16 value; // 整个16位值
        struct {

            // Bit14 ~ Bit0: 表示帧计数低字节的路序号（实际值减一存储）
            quint16 frameCountLowByteIndex : 15; // 低15位
            // Bit15: 0表示使能计数，1表示不使能计数
            quint16 notCountEnable : 1;   // 第15位（最高位）
        } bits;
    }frameCalcChannelhigh;
    
    quint8  reserved2[4];      // 保留字段 [4B]
    union {
        quint8 raw;   // 整个字节
        struct {
            // 我们定义两个位域，分别对应bit0和bit1。
            // 假设bit0在bit0（最低位），bit1在bit1（次低位）
            quint8 bit0 : 1;   // 第0位（最低位）
            quint8 bit1 : 1;   // 第1位
            quint8 reserved : 6; // 保留剩下的6位，这样整个字节就是8位了
        } bits;
    };       // ID码副帧特征 [1B]
    quint8  codingPosition;    // 编码位置 [1B]
    quint8  reserved3[22];     // 保留字段 [22B]
}*PTELEMETRY_FRAME;
#pragma pack(pop)

//反馈指令格式 0x11
#pragma pack(push, 1)
typedef struct TELEMETRY_FRAME_RES {
    quint8  Tpackagenum_RES;
    quint8  Rpackagenum_RES;
    quint8   result;
   
}*PTELEMETRY_FRAME_RES;
#pragma pack(pop)

//反馈指令格式 0x02
#pragma pack(push, 1)
typedef struct READ_FRAMEFORMAT {
    quint8   fashe;
   
}*PREAD_FRAMEFORMAT;
#pragma pack(pop)

//反馈指令格式 0x12
#pragma pack(push, 1)
typedef struct READ_FRAMEFORMAT_RES {
    quint8  txSelector;        // 发射机选择 [1B]
    quint32 pcmRate;           // PCM信号源码率 [4B]
//    quint16 subFrameLength;    // 子帧长 [2B]
    // 定义union实现两种访问方式
    union {
        quint16 rawValue;        // 完整的16位值
        struct{
            quint16 length : 15;    // 低15位表示子帧长度-1
            quint16 moFeiFlag : 1;   // 最高位(Bit_15)表示模飞状态标志
        } bit;    // 位域视图
    }subFrameLength;
    quint8  subFrameCount;     // 副帧长 [1B]
    union  {
        quint8 raw;   // 原始的8位数据
        struct {
            quint8 codeType : 4;   // 低4位: 码型 (Bit0~Bit3)
            quint8 wordLengthMinusOne : 4; // 高4位: 字长-1 (Bit4~Bit7)
        } bits;
    }WordConfig;
    quint16 featurePosition;   // 特征副帧位置 [2B]

    quint16 loopSyncCode;      // 循环副帧同步码 [2B]
    quint64 syncCode;          // 子帧同步码高位 [8B]
    quint8  frameType;         // 副帧类型 [1B]
    quint8  reserved1[5];      // 保留字段 [5B]
    quint8  dataType;          // 数据类型 [1B]
    quint16 stepValue;         // 台阶码步进 [2B]
    quint16 initStep;          // 台阶码初始值 [2B]
    union  {
        quint16 value; // 整个16位值
        struct {

            // Bit14 ~ Bit0: 表示帧计数低字节的路序号（实际值减一存储）
            quint16 frameCountLowByteIndex : 15; // 低15位
            // Bit15: 0表示使能计数，1表示不使能计数
            quint16 notCountEnable : 1;   // 第15位（最高位）
        } bits;
    }FrameCalcChannel;
    union  {
        quint16 value; // 整个16位值
        struct {

            // Bit14 ~ Bit0: 表示帧计数低字节的路序号（实际值减一存储）
            quint16 frameCountLowByteIndex : 15; // 低15位
            // Bit15: 0表示使能计数，1表示不使能计数
            quint16 notCountEnable : 1;   // 第15位（最高位）
        } bits;
    }frameCalcChannelhigh;

    quint8  reserved2[4];      // 保留字段 [4B]
    union {
        quint8 raw;   // 整个字节
        struct {
            // 我们定义两个位域，分别对应bit0和bit1。
            // 假设bit0在bit0（最低位），bit1在bit1（次低位）
            quint8 bit0 : 1;   // 第0位（最低位）
            quint8 bit1 : 1;   // 第1位
            quint8 reserved : 6; // 保留剩下的6位，这样整个字节就是8位了
        } bits;
    }  idtreatrue ;       // ID码副帧特征 [1B]
    quint8  codingPosition;    // 编码位置 [1B]
    quint8  reserved3[22];     // 保留字段 [23B]
   
}*PREAD_FRAMEFORMAT_RES;
#pragma pack(pop)

// 功能区分码：0x03。
#pragma pack(push, 1)
typedef struct TRANSMIT_CONFIG {
    //================ 发射源1配置 ================//
    quint8  txSelector;        // 发射机选择 [1B] 1-发射机1 2-发射机2
    quint32 freq1;             // 发射频率1 [4B] 单位KHz
    quint32 detF1;             // 调制频偏1 [4B] DetF = (N×f0)/2^32
    quint16 reserved1;         // 保留字段 [2B]
    union {                    // 发射源1控制 [1B]
        quint8 ctrl1;
        struct {
            quint8 bit0 :1;      //未使用 ,值永远为0
            quint8 modPolarity1 :1; // Bit1 调制极性 0-正 1-负
            quint8 modSwitch1   :1; // Bit2 调制开关 0-关 1-开
            quint8 carrier1     :1; // Bit3 载波开关
            quint8 modType1     :4; // Bit7-4 调制方式
        } bits1;
    };
    quint8 powerCtrl1;         // 发射源1功率控制 [1B] 0-不衰减
    quint8 powerCtrl1_UI;      // 发射源1功率控制 [1B] UI显示值

    quint8 reserved3[50];      // 保留区域 [25B]
}*PTRANSMIT_CONFIG;
#pragma pack(pop)

// 功能区分码：0x13。
#pragma pack(push, 1)
typedef struct TRANSMIT_CONFIG_RES {
    quint8  Tpackagenum_RES;
    quint8  Rpackagenum_RES;
    quint8   result;
    
}*PTRANSMIT_CONFIG_RES;
#pragma pack(pop)

//反馈指令格式 0x04
#pragma pack(push, 1)
typedef struct READ_yaocFRAMEFORMAT {
    quint8   fashe;
   
}*PREAD_yaocFRAMEFORMAT;
#pragma pack(pop)

//反馈指令格式 0x14
#pragma pack(push, 1)
typedef struct READ_yaocFRAMEFORMAT_RES {
    //================ 发射源1配置 ================//
    quint8  txSelector;        // 发射机选择 [1B] 1-发射机1 2-发射机2
    quint32 freq1;             // 发射频率1 [4B] 单位KHz
    quint32 detF1;             // 调制频偏1 [4B] DetF = (N×f0)/2^32
    quint16 reserved1;         // 保留字段 [2B]
    union {                    // 发射源1控制 [1B]
        quint8 ctrl1;
        struct {
            quint8 bit0 :1;      //未使用 ,值永远为0
            quint8 modPolarity1 :1; // Bit1 调制极性 0-正 1-负
            quint8 modSwitch1   :1; // Bit2 调制开关 0-关 1-开
            quint8 carrier1     :1; // Bit3 载波开关
            quint8 modType1     :4; // Bit7-4 调制方式
        } bits1;
    };
    quint8 powerCtrl1;         // 发射源1功率控制 [1B] 0-不衰减
    quint8 powerCtrl1_UI;         // 发射源1功率控制 UI显示值

    quint8 reserved3[50];      // 保留区域 [25B]

   
}*PREAD_yaocFRAMEFORMAT_RES;
#pragma pack(pop)


//指令格式 0x05
#pragma pack(push, 1)
typedef struct TELEMETRY_ENCODING_CONFIG {
    //========= 编码控制段 =========//
    quint8 txSelector;     // 发射机选择 [1B]
    union {
        quint8 codeSwitch; // 编码开关 [1B]
        struct {
            quint8 ldpcEnable  :1;  // Bit0: LDPC编码开关
            quint8 tpcEnable   :1;  // Bit1: TPC编码开关
            quint8 rsEnable    :1;  // Bit2: RS编码开关
            quint8 convEnable  :1;  // Bit3: 卷积编码开关
            quint8 reserved1   :2;  // Bit4-5: 保留位
            quint8 reserved2   :2;  // Bit6-7: 保留位
        } codeBits;
    };
    quint8 reserved[3];    // 保留字段 [3B]

    //========= TPC配置段 =========//
    quint32 tpcSyncCode;    // TPC块同步码 [4B]
    quint16 tpcValidFlag;   // TPC有效标志 [2B]
    
    //========= 扩展保留段 =========//
    quint8 padding[53];     // 填充保留区 [53B]
    
} *PTELEMETRY_ENCODING_CONFIG;
#pragma pack(pop)

//指令格式 0x15
#pragma pack(push, 1)
typedef struct TELEMETRY_ENCODING_CONFIG_RES {
    quint8  Tpackagenum_RES;
    quint8  Rpackagenum_RES;
    quint8   result;
     
} *PTELEMETRY_ENCODING_CONFIG_RES;
#pragma pack(pop)

//指令格式 0x06owner->m_PREAD_yaocFRAMEFORMAT_RES = new READ_yaocFRAMEFORMAT_RES;
#pragma pack(push, 1)
typedef struct READ_ENCODING_CONFIG {
     quint8   fashe;
     
} *PREAD_ENCODING_CONFIG;
#pragma pack(pop)

//指令格式 0x16
#pragma pack(push, 1)
typedef struct READ_ENCODING_CONFIG_RES {
    //========= 编码控制段 =========//
    quint8 txSelector;     // 发射机选择 [1B]
    union {
        quint8 codeSwitch; // 编码开关 [1B]
        struct {
            quint8 ldpcEnable  :1;  // Bit0: LDPC编码开关
            quint8 tpcEnable   :1;  // Bit1: TPC编码开关
            quint8 rsEnable    :1;  // Bit2: RS编码开关
            quint8 convEnable  :1;  // Bit3: 卷积编码开关
            quint8 reserved1   :2;  // Bit4-5: 保留位
            quint8 reserved2   :2;  // Bit6-7: 保留位
        } codeBits;
    };
    quint8 reserved[3];    // 保留字段 [3B]

    //========= TPC配置段 =========//
    quint32 tpcSyncCode;    // TPC块同步码 [4B]
    quint16 tpcValidFlag;   // TPC有效标志 [2B]

    //========= 扩展保留段 =========//
    quint8 padding[53];     // 填充保留区 [53B]
    
} *PREAD_ENCODING_CONFIG_RES;
#pragma pack(pop)

#pragma pack(push, 1)
// 配置条目结构（增强可读性）
typedef struct ConfigEntry {
    // 控制字位域（使用类型安全操作）
    union {
        quint8 rawCtrl;
        struct {
            quint8     mode   :1;  // 帧模式选择
            quint8    reserved:7;  // 保留位
        } ctrlBits;
    };

    quint8    subFramePos;    // 副帧位置
    quint16   childFramePos;  // 子帧位置（网络字节序）
    quint8    dataSource;     // 数据源标识
    quint8    entryReserved;  // 条目保留字段
    quint16   dataLength;     // 数据长度（网络字节序）

}  *PConfigEntry;
#pragma pack(pop)

//0X07
#pragma pack(push, 1)
// 主配置结构（显式内存布局）
typedef struct PCMEMBEDCONfIG {
    //==== 配置头 ====//
    quint8 txSelector;      // 发射机选择（1/2）
    quint8 entryCount;      // 有效条目数（0-10）

    //==== 配置主体 ====//
    ConfigEntry entries[10]; // 配置条目池


    quint8 baoli[46];

//    // 构造函数（C++11语法）
//       PCMEMBEDCONfIG() : txSelector(0), entryCount(0)

 } *PPCMEMBEDCONfIG;
#pragma pack(pop)

// 0x17
#pragma pack(push, 1)
// 主配置结构（显式内存布局）
typedef struct PCMEMBEDCONfIG_RES {
    quint8  Tpackagenum_RES;
    quint8  Rpackagenum_RES;
    quint8   result;

 } *PPCMEMBEDCONfIG_RES;
#pragma pack(pop)


//指令格式 0x08
#pragma pack(push, 1)
typedef struct READ_PCM_CONFIG {
     quint8   fashe;
     
} *PREAD_PCM_CONFIG;
#pragma pack(pop)

//指令格式 0x18
#pragma pack(push, 1)
typedef struct READ_PCM_CONFIG_RES {
    //==== 配置头 ====//
    quint8 txSelector;      // 发射机选择（1/2）
    quint8 entryCount;      // 有效条目数（0-10）

    //==== 配置主体 ====//
    ConfigEntry entries[10]; // 配置条目池



} *PREAD_PCM_CONFIG_RES;
#pragma pack(pop)

enum class AsyncDataType : quint8 {
    STEP_CODE    = 0x00,  // 台阶码
    RANDOM_CODE  = 0x01   // 随机码
};

#pragma pack(push, 1)
typedef struct AsyncSourceEntry {
    quint8 frameLength;       // 帧长度（单位：字）
    quint8 Securitycontrolposition;       // 安控位置
    quint8 dataType;    // 数据类型
    quint8 stepIncrement;      // 台阶码步进
    quint8 initialValue;       // 台阶码初始值
    quint32 syncCode;         // 同步码（实际使用根据syncCodeLength截取）
    quint8 syncCodeLength;     // 同步码长度（1-4字节）
    quint8 frameCounterLength; // 帧计数长度（1-4字节） -1下发
    quint8 zhenlv;             // 帧率
    
    // 获取有效同步码（根据长度截取）
        quint32 getValidSyncCode() const {
            switch(syncCodeLength) {
            case 1: return syncCode & 0xFF;
            case 2: return syncCode & 0xFFFF;
            case 3: return syncCode & 0xFFFFFF;
            default: return syncCode;
            }
        }
} *PAsyncSourceEntry;
#pragma pack(pop)

#pragma pack(push, 1)
// 功能区分码：0x09。
typedef struct AsyncSourceConfig {
    quint8 txSelector;         // 发射机选择（1/2）
    quint8 entryCount;       // 使能异步源个数（最大10）
    AsyncSourceEntry entries[10]; // 配置条目池
    quint8 baoli[6];

    // 构造函数（C++11语法）
       AsyncSourceConfig() : txSelector(0), entryCount(0) {


       }
}* PAsyncSourceConfig;
#pragma pack(pop)

#pragma pack(push, 1)
// 功能区分码：0x19。
typedef struct AsyncSourceConfig_RES {
    quint8  Tpackagenum_RES;
    quint8  Rpackagenum_RES;
    quint8   result;
}* PAsyncSourceConfig_RES;
#pragma pack(pop)

// 功能区分码：0x0a
#pragma pack(push, 1)
typedef struct READ_ASY_CONFIG {
     quint8   fashe;
     
} *PREAD_ASY_CONFIG;
#pragma pack(pop)

// 功能区分码：0x1a
#pragma pack(push, 1)
typedef struct READ_ASY_CONFIG_RES {
    quint8 txSelector;         // 发射机选择（1/2）
    quint8 entryCount;       // 使能异步源个数（最大10）
    AsyncSourceEntry entries[10]; // 配置条目池
    quint8 baoli[6];

    // 构造函数（C++11语法）
       READ_ASY_CONFIG_RES() : txSelector(0), entryCount(0)
       {

       }

} *PREAD_ASY_CONFIG_RES;
#pragma pack(pop)

// 功能区分码：0x0b
#pragma pack(push, 1)
typedef struct SecuritySourceConfig {
    //======= 基本配置段 =======//
    quint8  subcarrierTocoderate;              // 保留 [1B] 必须置0
    
    //======= 频率配置段 =======//
    quint32 carrierFrequency;     // 载波频率 [4B] 1750000-1850000KHz（小端）
    quint32 subcarrierFrequency;   // 副载波频率 [4B] DetF=(N×f0)/2^32（小端）
    
    //======= 安控模式段 =======//
    union {
        quint8 controlMode;       // 安控模式 [1B]
        struct {
            quint8 modeSelect :1;  // 0:DPSK-FM 1:主字母
            quint8 reserved   :7;  // 保留位
        } modeBits;
    };
    
    //======= DPSK-FM参数段 =======//
    quint8 dpskFmBandwidth;      // 带宽 [1B]
    quint32 dpskFmInstructionRate; // 指令码率 [4B] Rf=f0·N/2（小端）
    quint16 dpskFmInstructionLength; // 指令长度 [2B] 实际值=值+1
    quint8  dpskFmPreamble[3];    // 前导码 [3B] 默认{0xFF,0xFF,0xFF}
    quint16 dpskFmInstructionSyncCode; // 指令同步码 [2B] 默认0xEB90
    union {
        quint8 codeType;          // 码型 [1B]
        struct {
            quint8 codeScheme :4; // 码型选择（0000:NRZ-L等）
            quint8 reserved   :4; // 保留位
        } codeBits;
    };
    
    quint8 DPSK_K1_Address_Code;
    quint16 DPSK_K1_Function_Code;
    quint8 DPSK_K1_Fill_Code;

    quint8 DPSK_K2_Address_Code;
    quint16 DPSK_K2_Function_Code;
    quint8 DPSK_K2_Fill_Code;

    quint8 DPSK_K3_Address_Code;
    quint16 DPSK_K3_Function_Code;
    quint8 DPSK_K3_Fill_Code;

    quint8 DPSK_K4_Address_Code;
    quint16 DPSK_K4_Function_Code;
    quint8 DPSK_K4_Fill_Code;

    quint16 MainLetter_Self_check[7];
    quint16 MainLetter_Reset[7];
    quint16 MainLetter_Unlocked[7];
    quint16 MainLetter_Self_destruct[7];


    quint8 baliu2[33];



} *PSecuritySourceConfig;
#pragma pack(pop)

#pragma pack(push, 1)
// 功能区分码：0x1b
typedef struct SecuritySourceConfig_RES {
    quint8  Tpackagenum_RES;
    quint8  Rpackagenum_RES;
    quint8   result;
}* PSecuritySourceConfig_RES;
#pragma pack(pop)



// 功能区分码：
#pragma pack(push, 1)
typedef struct daimoall {
    quint8  id;
    QString  wenjianname;
    quint8  txSelector;        // 发射机选择 [1B]
    quint32 pcmRate;           // PCM信号源码率 [4B]
    union {
        quint16 rawValue;        // 完整的16位值
        struct{
            quint16 length : 15;    // 低15位表示子帧长度-1
            quint16 moFeiFlag : 1;   // 最高位(Bit_15)表示模飞状态标志
        } bit;    // 位域视图
    }subFrameLength;
    quint8  subFrameCount;     // 副帧长 [1B]
    union  {
        quint8 raw;   // 原始的8位数据
        struct {
            quint8 codeType : 4;   // 低4位: 码型 (Bit0~Bit3)
            quint8 wordLengthMinusOne : 4; // 高4位: 字长-1 (Bit4~Bit7)
        } bits;
    }WordConfig;
    quint16 featurePosition;   // 特征副帧位置 [2B]

    quint16 loopSyncCode;      // 循环副帧同步码 [2B]
    quint64 syncCode;          // 子帧同步码高位 [8B]
    union  {
        quint8 bit;   // 原始的8位数据
        struct {
            quint8 bitnumberlength : 6;   // 低4位: 子帧码组
            quint8 fhuframe : 2; // 高4位:副帧类型 (Bit4~Bit7)
        } bits;
    }frameType;
    quint8  reserved1[5];      // 保留字段 [5B]
    quint8  dataType;          // 数据类型 [1B]
    quint16 stepValue;         // 台阶码步进 [2B]
    quint16 initStep;          // 台阶码初始值 [2B]
    union  {
        quint16 value; // 整个16位值
        struct {

            // Bit14 ~ Bit0: 表示帧计数低字节的路序号（实际值减一存储）
            quint16 frameCountLowByteIndex : 15; // 低15位
            // Bit15: 0表示使能计数，1表示不使能计数
            quint16 notCountEnable : 1;   // 第15位（最高位）
        } bits;
    }FrameCalcChannel;
    union  {
        quint16 value; // 整个16位值
        struct {

            // Bit14 ~ Bit0: 表示帧计数低字节的路序号（实际值减一存储）
            quint16 frameCountLowByteIndex : 15; // 低15位
            // Bit15: 0表示使能计数，1表示不使能计数
            quint16 notCountEnable : 1;   // 第15位（最高位）
        } bits;
    }frameCalcChannelhigh;

    quint8  reserved2[4];      // 保留字段 [4B]
    union {
        quint8 raw;   // 整个字节
        struct {
            // 我们定义两个位域，分别对应bit0和bit1。
            // 假设bit0在bit0（最低位），bit1在bit1（次低位）
            quint8 jishuqidian : 1;   // 第0位（最低位）
            quint8 jishuaddorred : 1;   // 第1位
            quint8 reserved : 6; // 保留剩下的6位，这样整个字节就是8位了
        } bits;
    }  idtreatrue ;       // ID码副帧特征 [1B]
    quint8  codingPosition;    // 编码位置 [1B]
    quint8  reserved3[22];     // 保留字段 [22B]

    quint32 freq;             // 发射频率1 [4B] 单位KHz
    quint32 detF;             // 调制频偏1 [4B] DetF = (N×f0)/2^32
    union {                    // 发射源1控制 [1B]
        quint8 ctrl;
        struct {
            quint8 bit0 :1;      //未使用 ,值永远为0
            quint8 modPolarity :1; // Bit1 调制极性 0-正 1-负
            quint8 modSwitch   :1; // Bit2 调制开关 0-关 1-开
            quint8 carrier     :1; // Bit3 载波开关
            quint8 modType     :4; // Bit7-4 调制方式
        } bits;
    } alltiaoz;
    quint8 powerCtrl;         // 发射源1功率控制 [1B] 0-不衰减



    union {
        quint8 codeSwitchValue; // 编码开关 [1B]
        struct {
            quint8 ldpcEnable  :1;  // Bit0: LDPC编码开关
            quint8 tpcEnable   :1;  // Bit1: TPC编码开关
            quint8 rsEnable    :1;  // Bit2: RS编码开关
            quint8 convEnable  :1;  // Bit3: 卷积编码开关
            quint8 reserved1   :2;  // Bit4-5: 保留位
            quint8 reserved2   :2;  // Bit6-7: 保留位
        } codeBits;
    }codeSwitch;
    quint8 reserved[3];    // 保留字段 [3B]

    //========= TPC配置段 =========//
    quint32 tpcSyncCode;    // TPC块同步码 [4B]
    quint16 tpcValidFlag;   // TPC有效标志 [2B]

    //========= pcm =========//
    quint8 entryCount;      // 有效条目数（0-10)
    ConfigEntry entries[10]; // 配置条目池
    quint8 baoli[46];

    //========= 异步源 =========//
    quint8 entryCount2;       // 使能异步源个数（最大10）
    AsyncSourceEntry entries2[10]; // 配置条目池
    quint8 baoli2[6];


    //========= 安控 =========//
    quint8  ankongreserved;
    quint32 carrierFrequency;     // 载波频率 [4B] 1750000-1850000KHz（小端）
    quint32 subcarrierFrequency;   // 副载波频率 [4B] DetF=(N×f0)/2^32（小端）


    union {
        quint8 controlMode;       // 安控模式 [1B]
        struct {
            quint8 modeSelect :1;  // 0:DPSK-FM 1:主字母
            quint8 reserved   :7;  // 保留位
        } modeBits;
    };


    quint8  dpskFmBandwidth;      // 带宽 [1B]
    quint32 dpskFmInstructionRate; // 指令码率 [4B] Rf=f0·N/2（小端）
    quint16 dpskFmInstructionLength; // 指令长度 [2B] 实际值=值+1
    quint8  dpskFmPreamble[3];    // 前导码 [3B] 默认{0xFF,0xFF,0xFF}
    quint16 dpskFmInstructionSyncCode; // 指令同步码 [2B] 默认0xEB90
    union {
        quint8 codeBit;          // 码型 [1B]
        struct {
            quint8 codeScheme :4; // 码型选择（0000:NRZ-L等）
            quint8 reserved   :4; // 保留位
        } codeBits;
    }codeType;

    quint8 DPSK_K1_Address_Code;
    quint16 DPSK_K1_Function_Code;
    quint8 DPSK_K1_Fill_Code;

    quint8 DPSK_K2_Address_Code;
    quint16 DPSK_K2_Function_Code;
    quint8 DPSK_K2_Fill_Code;

    quint8 DPSK_K3_Address_Code;
    quint16 DPSK_K3_Function_Code;
    quint8 DPSK_K3_Fill_Code;

    quint8 DPSK_K4_Address_Code;
    quint16 DPSK_K4_Function_Code;
    quint8 DPSK_K4_Fill_Code;

    quint16 MainLetter_Self_check[7];
    quint16 MainLetter_Reset[7];
    quint16 MainLetter_Unlocked[7];
    quint16 MainLetter_Self_destruct[7];


    quint8 baliu2[33];


} *Pdaimoall;
#pragma pack(pop)





// 安控模式枚举
enum SecurityMode : quint8 {
    DPSK_FM   = 0x00,  // DPSK-FM模式
    MAIN_CHAR = 0x01   // 主字母模式
};

// 主字母音调编码规则
struct CharTone {
    quint8 tone1 :4;  // 音1（0-15，对应6.4kHz~12.0kHz）
    quint8 tone2 :4;   // 音2
    quint8 tone3 :4;   // 音3
    quint8 tone4 :4;   // 音4
};

// 主字母配置单元
struct MainCharConfig {
    quint16 rawValue;  // 原始编码值owner->m_PREAD_ASY_CONFIG_RE
    CharTone tones;     // 音调分解

    // 从界面值转换（示例：E517 -> 0x40A2）
    void fromUI(quint16 uiValue) {
        rawValue = ((uiValue & 0xF000) << 4) |  // 第一个音
                  ((uiValue & 0x0F00) << 3) |  // 第二个音
                  ((uiValue & 0x00F0) << 2) |  // 第三个音
                  ((uiValue & 0x000F) << 1);    // 第四个音
    }
};




//注意区分 0x0c 0x1D 和 0x1c 的名称

#pragma pack(push, 1)
// 功能区分码: (0x0C) Read the security control
typedef struct READSECURITYCONTROL {

    quint8   result;
}* PREADSECURITYCONTROL;
#pragma pack(pop)



// 功能区分码：0x1C
#pragma pack(push, 1)
typedef struct READankongpeiz_RES {
    //======= 基本配置段 =======//
    quint8  reserved;              // 保留 [1B] 必须置0

    //======= 频率配置段 =======//
    quint32 carrierFrequency;     // 载波频率 [4B] 1750000-1850000KHz（小端）
    quint32 subcarrierFrequency;   // 副载波频率 [4B] DetF=(N×f0)/2^32（小端）

    //======= 安控模式段 =======//
    union {
        quint8 controlMode;       // 安控模式 [1B]
        struct {
            quint8 modeSelect :1;  // 0:DPSK-FM 1:主字母
            quint8 reserved   :7;  // 保留位
        } modeBits;
    };

    //======= DPSK-FM参数段 =======//
    quint8 dpskFmBandwidth;      // 带宽 [1B]
    quint32 dpskFmInstructionRate; // 指令码率 [4B] Rf=f0·N/2（小端）
    quint16 dpskFmInstructionLength; // 指令长度 [2B] 实际值=值+1
    quint8  dpskFmPreamble[3];    // 前导码 [3B] 默认{0xFF,0xFF,0xFF}
    quint16 dpskFmInstructionSyncCode; // 指令同步码 [2B] 默认0xEB90
    union {
        quint8 codeType;          // 码型 [1B]
        struct {
            quint8 codeScheme :4; // 码型选择（0000:NRZ-L等）
            quint8 reserved   :4; // 保留位
        } codeBits;
    };

    quint8 DPSK_K1_Address_Code;
    quint16 DPSK_K1_Function_Code;
    quint8 DPSK_K1_Fill_Code;

    quint8 DPSK_K2_Address_Code;
    quint16 DPSK_K2_Function_Code;
    quint8 DPSK_K2_Fill_Code;

    quint8 DPSK_K3_Address_Code;
    quint16 DPSK_K3_Function_Code;
    quint8 DPSK_K3_Fill_Code;

    quint8 DPSK_K4_Address_Code;
    quint16 DPSK_K4_Function_Code;
    quint8 DPSK_K4_Fill_Code;

    quint16 MainLetter_Self_check[7];
    quint16 MainLetter_Reset[7];
    quint16 MainLetter_Unlocked[7];
    quint16 MainLetter_Self_destruct[7];


    quint8 baliu2[33];



} *PREADankongpeiz_RES;
#pragma pack(pop)


// 功能区分码: (0x1D) Read the security control
// 完整安控指令结构
typedef struct READSECURITYCONTROL_RES {
    //==== 公共头 ====//
    quint32 reserved      :32;  // 保留字段 [4B]
    quint16 commandCount;       // 指令个数 [2B] (1-1000)
    quint8  commandLength;      // 指令长度 [1B]（实际长度=值+1）
    quint8 mode;          // 安控模式 [1B]

    //==== 模式专有配置 ====//
    union {
        // DPSK-FM模式
        struct {
            quint16 syncCode;     // 同步码 [4B] 默认0xA1B2C3D4
            quint8  addressCode;  // 地址码 [2B]
            quint16 functionCode; // 功能码 [1B]
            quint8  padding;  // 填充码 [12B]
        } dpskem;

        // 主字母模式
        struct {
            quint16 chars[7]; // 7个字母 [14B]
            quint16 controlWord;     // 控制字 [2B] 如0x40A2
            quint8  reserved2[8];    // 保留区 [8B]
        } mainchar;
    };



    // 构造函数
    READSECURITYCONTROL_RES() :
        reserved(0),
        commandCount(0),
        commandLength(5),  // 默认DPSK-FM长度6-1
        mode(DPSK_FM)
    {
        memset(&dpskem, 0, sizeof(dpskem));
        dpskem.syncCode = 0xA1B2C3D4;
    }
} *PREADSECURITYCONTROL_RES;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct TransceiverConfig_RES {
    //======= 发射机1配置段 =======//
    quint32 tx1_freq;       // 频点 [4B] 单位：KHz
    union {
        quint8 tx1_rf_status;  // 射频状态 [1B]
        struct {
            quint8 tx1_carrier  :1;  // Bit0: 载波开关(0:关 1:开)
            quint8 tx1_mod      :1;  // Bit1: 调制开关
            quint8 tx1_reserved :6;  // 保留位
        } tx1_bits;
    };
    quint16 tx1_cache_size;  // 模飞缓存容量 [2B] 实际容量=值*4KB
    quint8  tx1_reserved[25]; // 保留区 [25B]

    //======= 发射机2配置段 =======//
    quint32 tx2_freq;        // 频点 [4B]
    union {
        quint8 tx2_rf_status;  // 射频状态 [1B]
        struct {
            quint8 tx2_carrier  :1;  // Bit0
            quint8 tx2_mod      :1;  // Bit1
            quint8 tx2_reserved :6;
        } tx2_bits;
    };
    quint16 tx2_cache_size;  // 模飞缓存容量 [2B]
    quint8  tx2_reserved[25];

    //======= 安控模块段 =======//
    quint8  sec_rx_power;    // 接收功率 [1B] 0-100%
    union {
        quint8 sec_rx_status; // 接收状态 [1B]
        struct {
            quint8 frame_lock  :1;  // Bit0: 帧锁定(0:未锁定 1:锁定)
            quint8 sec_reserved :7;
        } sec_bits;
    };
    quint8  final_reserved[62]; // 最终填充 [2B]

    // 构造函数初始化保留区
    TransceiverConfig_RES() : tx1_reserved{0}, tx2_reserved{0},
                         final_reserved{0} {}
} *PTransceiverConfig_RES;
#pragma pack(pop)


#pragma pack(push, 1)
struct TransmissionDataBegin {
    union {
        quint8 data;  // 射频状态 [1B]
        struct {
            quint8 bit0  :1;  // Bit0: 发射机1是否回传
            quint8 bit1  :1;  // Bit1: 发射机2是否回传
        } bits;
    };
};
#pragma pack(pop)



// 主字母配置单元
struct ankongjiegong {
  quint8 SecurityMode;
  int    kValue;

  quint8  addressCode;  // 地址码 [2B]
  quint16 functionCode; // 功能码 [1B]
  quint8  padding;  // 填充码 [12B]

  quint16 chars[7]; // 7个字母 [14B]
  quint16 controlWord;     // 控制字 [2B] 如0x40A2
  quint8  reserved2[8];    // 保留区 [8B]



  ankongjiegong() : SecurityMode{0}, kValue{0}
                    {}

};

struct GpsData {
    QDateTime time;     // GPS时间
    double latitude;    // 十进制纬度
    double longitude;   // 十进制经度
    double altitude;    // 海拔高度（米）
    QString GPS;
    QString PRNCount;   // 卫星数
};

struct RmcData {
    QDateTime datetime;      // 完整的日期和时间
    QString status;           // 定位状态 (A=有效, V=无效)
    double latitude;         // 纬度 (十进制度)
    double longitude;        // 经度 (十进制度)
    double speed;            // 地面速率 (节)
    double course;           // 航向 (度)
    QString magneticVariation; // 磁偏角 (度和方向)
    QString mode;            // 定位模式 (A=自主, D=差分, E=估算, N=无效)
};




#pragma pack(push, 1)
typedef struct RES_TransmitterData {
    // ========== 发射机1部分 (32字节) ==========
    quint32 tx1_freq_point;      // 频点 (4B)

    union {
        quint8 tx1_rf_status;  // 射频状态 [1B]
        struct {
            quint8 tx1_carrier  :1;  // Bit0: 载波开关(0:关 1:开)
            quint8 tx1_mod      :1;  // Bit1: 调制开关
            quint8 tx1_reserved :6;  // 保留位
        } tx1_bits;
    };              // 射频状态 (1B)

    quint16 tx1_buffer_capacity;   // 模飞缓存容量 (2B)
    quint8 tx1_MofeiCumulativeNumber;
    quint8 tx1_reserved[24];        // 保留区域 (25B)

    // ========== 发射机2部分 (32字节) ==========
    quint32 tx2_freq_point;      // 频点 (4B)

    union {
        quint8 tx2_rf_status;  // 射频状态 [1B]
        struct {
            quint8 tx2_carrier  :1;  // Bit0
            quint8 tx2_mod      :1;  // Bit1
            quint8 tx2_reserved :6;
        } tx2_bits;
    };

    quint16 tx2_buffer_capacity;   // 模飞缓存容量 (2B)
    quint8 tx2_MofeiCumulativeNumber;

    // ========== 安控部分 (2字节) ==========
    quint8 security_recv_power;    // 接收功率 (1B)

    union {
        quint8 sec_rx_status; // 接收状态 [1B]
        struct {
            quint8 frame_lock  :1;  // Bit0: 帧锁定(0:未锁定 1:锁定)
            quint8 sec_reserved :7;
        } sec_bits;
    };

    union {
        quint8 Security_control_status; // 接收状态 [1B]
        struct {
            quint8 K1  :1;  // Bit0: 帧锁定(0:未锁定 1:锁定)
            quint8 K2  :1;  // Bit1: 帧锁定(0:未锁定 1:锁定)
            quint8 K3  :1;  // Bit2: 帧锁定(0:未锁定 1:锁定)
            quint8 K4  :1;  // Bit3: 帧锁定(0:未锁定 1:锁定)
            quint8 reserved :4;
        } Security_control_status_bits;
       };


       quint16 Power_input_voltage; 
       quint16 Output_voltage_12V;
       quint16 Power_amplifier_28V_supply_voltage;
       quint16 Input_current_power_supply;
       quint16 Output_current_12V;
       quint16 Power_amplifier1;
       quint16 Power_amplifier2;
       quint16 Detection_voltage1;
       quint16 Detection_voltage2;
       quint8  Temperature;
       quint16 Version_number;
       




} *PRES_TransmitterData;

#pragma pack(pop)  // 恢复默认对齐方式




#pragma pack(push, 1)
typedef struct _Decode
{
    bool bDecode;//是否以太网解密
    //本机->解密机
    char mSendLocalIp[20];
    int mSendLocalPort;
    char mSendTargetIp[20];
    int mSendTargetPort;
    //解密机->本机
    char mRcvLocalIp[20];
    int mRcvLocalPort;


    _Decode()
    {
        bDecode = false;
        memset(mSendLocalIp,0x00,20);
        memset(mSendTargetIp,0x00,20);
        memset(mRcvLocalIp,0x00,20);
    }
}DECODE,*PDECODE;
#pragma pack(pop)

typedef struct _Demodulator   //解调器
{
    unsigned char nChannel;             //接收通道
    float nReceivingFrequency;   //接收频率
    char nReceiveBandwidth[10];           //接收带宽
    unsigned char nDemodulationMode;    //解调模式
    unsigned char nAFCTimeConstant;     //AFC时间常数
    unsigned char nAGCTimeConstant;     //AFC时间常数
    unsigned int nAzimuthSlope;         //方位斜率
    unsigned int nPitchSlope;           //俯仰斜率
    float nAzimuthPhase;                 //方位相位
    float nPitchPhase;                  //俯仰相位
    unsigned int nAzimuth;              //方位极性
    unsigned int nAzimuthalPolarity;    //俯仰极性
    unsigned int nPitchPolarity;        //基准输入方式

    unsigned char nSignalInport;//输入口,信号源、外部PCM、接收机
    float nBitRate;//码速率
    unsigned char nCodeType;//码型
    unsigned char  nCodeTypePos;//码型位置 1编码前、0编码后
    unsigned char nCodeRingBandwidth;//码环带宽
    bool bPhaseAmbiguity;//相位模糊
    unsigned char nDecode;//译码

    unsigned char nWordLength;//字长
    unsigned char nWordLengthSET;//字长-设置
    unsigned int nChildFrameLength;//子帧长
    unsigned int nSubFrameLength;//副帧长
    quint64 nChildSynCode;//子帧同步码,EB90,146F,9ABCB52C
    unsigned int nChildSynCodeLength;
    quint64 nSubSynCode;//副帧同步码,EB90,146F,9ABCB52C
    unsigned int nSubSynCodeLength;
    unsigned char nSubFrameType;//副帧方式 无副帧、循环副帧、反码副帧、ID副帧
    unsigned char  nIDBaseValue;//ID字基值 0开始、1开始
    unsigned char nIDCountDirection;//ID字计数方向 加计数、减计数
    unsigned int nSubframeFeatureWord;//副帧特征字
    unsigned int nSubFramePos;//副帧位置

    unsigned char nDecryptionSwitch;//解密开关 0:关 1:开
    unsigned int nStartAddress;         //起始地址
    unsigned int nCycle;                //周期
    unsigned int nFrameCounterChannelH; //帧计数高位波道
    unsigned int nFrameCounterChannelL; //帧计数低位波道

    char nEncryptedChannel[512];          //加密密钥
    char nUnencryptedChannel[64*1024 * 2];        //未加密波道


    //同步校核帧数
    unsigned char nInertialSynCnt;  //惯性同步帧数
    unsigned char nCheckCnt;        //校核帧数
    //容错位数
    unsigned char nSynAllowErr;     //同步容错,0～8:0位～8位
    unsigned char nSearchAllowErr;  //搜索容错,0～8:0位～8位





    _Demodulator()   //默认函数
    {
        nBitRate=2000000;
        nCodeType=0;
        nWordLength=8;
        nSignalInport=2;

        nSubFrameType=0;
        nSubFramePos=20;
        nChildFrameLength=256;
        nChildSynCode=0xEB90;
        nChildSynCodeLength=2;
        nSearchAllowErr=1;
        nSynAllowErr=1;
        nInertialSynCnt=3;
        nCheckCnt=1;

        strcpy(nEncryptedChannel,"");
        strcpy(nUnencryptedChannel,"");

        nSubFrameLength=64;
        nSubSynCode=0x146F;
        nSubSynCodeLength=2;

    }
}DEMODULATOR,*PDEMODULATOR;

typedef struct _Simulator   //配置信号模拟器
{
    unsigned char nLaunchSwitch;//发射开关
    float nLaunchFrequency;//发射频率
    unsigned int nModulationFrequencyOffset;//调制频偏
    unsigned char nModulatingSwitch;//调制开关
    unsigned char nModulationPolarity;//调制极性
    unsigned char  nModulationSystem;//调制体制 FM、BPSk
    unsigned int nOutputPower;//输出功率
    unsigned char nFixedRoadWave;//信号类型,0:随机码,1:台阶码,2:手动码
    float nBitRate;//码速率
    unsigned char nCodeType;//码型
    unsigned char  nCodeTypePos;//码型位置 1编码前、0编码后
    unsigned int nInitialValue;//台阶码初始值
    unsigned int nStep;//步进增量
    bool bFrameCounterChannelH;//帧计数高位波道开关
    unsigned int nFrameCounterChannelH;//帧计数高位波道
    bool bFrameCounterChannelL;//帧计数低位波道开关
    unsigned int nFrameCounterChannelL;//帧计数低位波道
    unsigned char  nCode;//编码 关闭、TPC
    unsigned char nWordLength;//字长
    unsigned char nWordLengthSET;//字长 设置
    unsigned int nChildFrameLength;//子帧长
    unsigned int nSubFrameLength;//副帧长
    quint64 nChildSynCode;//子帧同步码,EB90,146F,9ABCB52C
    unsigned int nChildSynCodeLength;
    quint64 nSubSynCode;//副帧同步码,EB90,146F,9ABCB52C
    unsigned int nSubSynCodeLength;
    unsigned char nSubFrameType;//副帧方式 无副帧、循环副帧、反码副帧、ID副帧
    unsigned char nIDBaseValue;//ID字基值 0开始、1开始
    unsigned char nIDCountDirection;//ID字计数方向 加计数、减计数
    unsigned int nSubframeFeatureWord;//副帧特征字
    unsigned int nSubFramePos;//副帧位置



    float fOutputRange;//输出幅度
    unsigned char nIDType;//ID副帧类型,0:起始1,1:起始最大,2:起始0,3:起始最大-1
    unsigned short nHandCodeValue;//手动码值
    bool bFileSend;
    char SimulateFileName[500];//模拟文件名
    bool bEnable;//模拟器使能

    _Simulator()
    {
        nBitRate=2000000;
        nCodeType=0;
        nWordLength=8;

        fOutputRange=5.0;
        nSubFrameType=0;
        nSubFramePos=20;
        nIDType=0;

        nChildFrameLength=256;
        nSubFrameLength=64;
        nChildSynCode=0xEB90;
        nChildSynCodeLength=2;
        nSubSynCode=0x146F;
        nSubSynCodeLength=2;
        nFixedRoadWave=0;
        nHandCodeValue=0x55;
        nFrameCounterChannelH=2;
        nFrameCounterChannelL=1;
        bFileSend=false;
        strcpy(SimulateFileName,"");
        bEnable=true;

    }

}SIMULATOR,*PSIMULATOR;
typedef struct _Takeoff
{
    unsigned char nTakeOffType;//起飞,0:外起飞,1:内起飞,2：选路起飞
    unsigned int nTakeOffChannel;//选路起飞波道
    unsigned char nTakeOffValue;//选路起飞值
    unsigned int nTakeOffCnt;//起飞帧数
    unsigned char nTakeOffCondition;
    _Takeoff()
    {
        nTakeOffType=0;
        nTakeOffChannel=51;
        nTakeOffValue=0xfe;
        nTakeOffCnt=5;
        nTakeOffCondition=0;
    }
}TAKEOFF,*PTAKEOFF;
typedef struct _Timer
{
    unsigned char nTimeSource;//时统,0:内DC,1:外,2:重发
    unsigned int  nYear;
    unsigned short nDay;//校时天数
    unsigned char nHour;//校时时
    unsigned char nMinute;//校时分
    unsigned char nSecond;//校时秒
    bool nChecked;      //gou :1 wei gou :0
    unsigned char nHighPrecision;
    bool bConfigTime;
    _Timer()
    {
        nYear = 2019;
        nTimeSource=0;
        nDay=234;
        nHour=21;
        nMinute=21;
        nSecond=22;
        nChecked=false;
        nHighPrecision = 0;
        bConfigTime = false;
    }
}TIMER,*PTIMER;



typedef struct _DemoSet
{
    struct _Demodulator Demodulator; //解调器相关参数
    struct _Simulator Simulator;     //模拟器相关参数
    struct _Takeoff Takeoff;         // 起飞相关参数
    struct _Timer Timer;             // 定时器相关参数
    struct _Decode Decode;           // 解码相关参数
    quint64 f0;                      // 64位无符号整型基础频率
    bool bSimpleModel;               // 布尔型简单模式标志
    _DemoSet()
    {
        bSimpleModel = true;        // 默认启用简单模式
    }
    //   struct _Decode Decode;

}DEMOSET,*PDEMOSET;                 //PDEMOSET = DEMOSET*


extern DEMOSET n_DemoSetParaOne;
extern DEMOSET n_DemoSetParaTwo;

extern int nFileHead;
extern int nFileHead2;

extern SQueue simDatQue1;
extern SQueue simDatQue2;

#define QUNMAXLEN 5242880*2//512 * 1024 * 1024



typedef struct _YaoCeData
{
    uint Len;
    uchar buf[0x10000];
    _YaoCeData()
    {
        Len = 0;
        memset(buf,0x00,0x10000);
    }
}YaoCeData;



// 在头文件中声明
class StrictIntValidator : public QValidator {
public:
    StrictIntValidator(int min, int max, QObject* parent = nullptr)
        : QValidator(parent), minVal(min), maxVal(max) {}

    State validate(QString& input, int&) const override {
        if (input.isEmpty()) return Intermediate;

        bool ok;
        uint value = input.toUInt(&ok);


        // 检查是否超出范围
        if (!ok || value > maxVal)
        {
            qDebug() << value << maxVal << ok << Invalid;
            return Invalid;
        }


    }

private:
    int minVal, maxVal;
};


enum class PositioningMethod : quint8 {
    SinglePoint      = 0,  /**< 000: 单点定位 */
    DGPS             = 1,  /**< 001: 伪距差分 */
    CarrierPhase     = 2,  /**< 010: 载波相位差分 */
    CustomBase       = 3   /**< 011-111: 标准使用方自定义 */
};
Q_DECLARE_FLAGS(PositioningMethods, PositioningMethod)


// 定位模式定义结构体，对应表4的位域布局
struct PositioningMode {
    // 位域成员定义（从低位b0到高位b15，顺序依赖编译器布局，通常低位在前）
    uint16_t gps_l1 : 1;       // b0: 1=GPS L1 参与定位, 0=GPS L1 不参与定位
    uint16_t gps_l2 : 1;       // b1: 1=GPS L2 参与定位, 0=GPS L2 不参与定位
    uint16_t gps_l5 : 1;       // b2: 1=GPS L5 参与定位, 0=GPS L5 不参与定位
    uint16_t bds_b1 : 1;       // b3: 1=BDS B1 参与定位, 0=BDS B1 不参与定位
    uint16_t bds_b2 : 1;       // b4: 1=BDS B2 参与定位, 0=BDS B2 不参与定位
    uint16_t bds_b3 : 1;       // b5: 1=BDS B3 参与定位, 0=BDS B3 不参与定位
    uint16_t glonass_g1 : 1;   // b6: 1=GLONASS G1 参与定位, 0=GLONASS G1 不参与定位
    uint16_t glonass_g2 : 1;   // b7: 1=GLONASS G2 参与定位, 0=GLONASS G2 不参与定位
    uint16_t glonass_g3 : 1;   // b8: 1=GLONASS G3 参与定位, 0=GLONASS G3 不参与定位
    uint16_t mode : 3;         // b11~b9: 定位模式（3位），见下方Mode枚举
    uint16_t reserved : 4;     // b15~b12: 保留位（4位）

    PositioningMode()
    {
        gps_l1 = 0;
        gps_l2 = 0;
        gps_l5 = 0;
        bds_b1 = 0;
        bds_b2 = 0;
        bds_b3 = 0;
        glonass_g1 = 0;
        glonass_g2 = 0;
        glonass_g3 = 0;
        mode = 0;
        reserved = 0;
    }

//    // 可选：实用函数示例，检查结构体大小和布局
//    static_assert(sizeof(PositioningMode) == sizeof(uint16_t),
//                  "PositioningMode must be exactly 16 bits wide.");
};


/**
 * @brief GNSS频点启用标志结构体
 * 通过位掩码方式实现，避免字节序问题
 */
#pragma pack(push, 1)
struct GNSSFrequencies {
    // 位域定义
    union {
        quint16 value;  /**< 16位整数值 */
        struct {
            // 低9位：频率标志位
            quint16 gps_l1     : 1;  // bit 0
            quint16 gps_l2     : 1;  // bit 1
            quint16 gps_l5     : 1;  // bit 2
            quint16 bds_b1     : 1;  // bit 3
            quint16 bds_b2     : 1;  // bit 4
            quint16 bds_b3     : 1;  // bit 5
            quint16 glonass_g1 : 1;  // bit 6
            quint16 glonass_g2 : 1;  // bit 7
            quint16 glonass_g3 : 1;  // bit 8

            // 高3位：定位方法 (bit 9-11)
            quint16 method     : 3;  // bits 9-11

            // 保留位 (bits 12-15)
            quint16 reserved   : 4;
        } bits;
    };
};
#pragma pack(pop)
Q_DECLARE_TYPEINFO(GNSSFrequencies, Q_PRIMITIVE_TYPE);

#pragma pack(push, 1)
/**
 * @brief 自定位帧固定头部分
 * 使用1字节对齐确保跨平台一致性
 */
struct SelfLocFrameHeader {
    quint8 validChannelCount;      /**< 序号1: 有效通道数n */
    quint16 reservedWord1;         /**< 序号2: 保留字 */
    quint16 reservedWord2;         /**< 序号3: 保留字 */
    GNSSFrequencies gnssFrequencies; /**< 序号4: GNSS频点启用状态和定位方法 */
    quint8 positioningStatus;     /**< 序号5: 定位状态 */
    quint8 coordinateSystem;      /**< 序号6: 坐标系类型 */
    quint16 year;                 /**< 序号7: 年 */
    quint8 month;                 /**< 序号8: 月 */
    quint8 day;                   /**< 序号9: 日 */
    quint32 secondOfDay;         /**< 序号10: 日内秒（0.1ms） */
    quint8 timeSystemId;          /**< 序号11: 时间系统标识 */
    qint32 posX;                  /**< 序号12: X方向位置分量（0.1m） */
    qint32 posY;                  /**< 序号13: Y方向位置分量（0.1m） */
    qint32 posZ;                  /**< 序号14: Z方向位置分量（0.1m） */
    qint32 velX;                  /**< 序号15: X方向速度分量（10^-3 m/s） */
    qint32 velY;                  /**< 序号16: Y方向速度分量（10^-3 m/s） */
    qint32 velZ;                  /**< 序号17: Z方向速度分量（10^-3 m/s） */
    quint16 pdop;                 /**< 序号18: PDOP（0.01） */
    qint32 clockBias;             /**< 序号19: 接收机钟差（0.1m） */
    qint32 clockDrift;            /**< 序号20: 接收机钟漂（0.1m/s²） */

    SelfLocFrameHeader()
    {
        validChannelCount = 0;
        reservedWord1 = 0x0000;
        reservedWord2 = 0x0000;
        coordinateSystem = 0;
        year = 0;
        month = 0;
        day = 0;
        secondOfDay = 0;
        timeSystemId = 0;
        posX = 0x7FFFFFFF;
        posY = 0x7FFFFFFF;
        posZ = 0x7FFFFFFF;
        velX = 0x7FFFFFFF;
        velY = 0x7FFFFFFF;
        velZ = 0x7FFFFFFF;
        pdop = 0x0000;
        clockBias = 0x7FFFFFFF;
        clockDrift = 0x7FFFFFFF;
    }

};
#pragma pack(pop)
Q_DECLARE_TYPEINFO(SelfLocFrameHeader, Q_PRIMITIVE_TYPE);



#pragma pack(push , 1)
// GNSS通用帧头结构体
struct gnss_generic_frame_header_t{
    uint8_t  frame_head[4];     // 帧头标识，固定为 {0xAA, 0x55, 0x11, 0xBB}
    uint16_t receiver_id;       // 接收机ID，用于区分多目标。0000H表示不用
    uint8_t  frame_type;        // 帧类型标识 (0:自定位帧, 1:测量元素帧, ..., 4:基准站信息帧, ...)
    uint16_t data_length;       // 后续数据体DATA的长度（字节数）
    // 注意：DATA数据体部分根据frame_type不同而不同，是可变长度的。
    // uint8_t  data[data_length]; // 数据体（在实际代码中通常用指针或柔性数组处理）
    // uint32_t crc32;            // 整帧CRC32校验码（对帧头、数据体进行校验）
    // uint8_t  frame_tail[3];    // 帧尾标识，固定为 {0x66, 0x44, 0x12}


    gnss_generic_frame_header_t()
    {
        frame_head[0] = 0xAA;
        frame_head[1] = 0x55;
        frame_head[2] = 0x11;
        frame_head[3] = 0xBB;
        receiver_id  = 0x0000;
        frame_type = 0x0;
        data_length = 0x12;

    }
};
#pragma pack(pop)





// 测量元素帧 - 数据体结构
typedef struct {
    uint8_t subframe_count; // 子帧数量 n (有效范围0~9)
    // 后面紧接 subframe_count 个 gnss_meas_subframe_t 子帧
    // 每个子帧的结构是独立的。
} gnss_measurement_frame_body_t;


// 测量元素子帧结构
typedef struct {
    uint8_t  subframe_head;      // 子帧头，固定为 0x10
    uint8_t  subframe_type;      // 子帧类型 (0xE1:GPS L1, 0xE2:GPS L2, ..., 0xF1:BDS B1, ... 详见表11)
    uint8_t  subframe_sync_code; // 子帧同步码，用于各子帧同步，随采样从0~255循环递增
    uint8_t  valid_channel_count; // 本子帧内有效通道数 m (即卫星数)
    uint32_t time1;              // 时间1 (定义同表12，如GPS为周数)
    uint64_t time2;              // 时间2 (量化单位0.1us，定义同表13，如GPS为周内秒)
    uint8_t  reserved1;          // 保留
    uint8_t  reserved2;          // 保留

    // 后面是 valid_channel_count 个通道的观测数据数组
    // 每个通道的数据结构如下：
    struct channel_data {
        uint16_t sat_id;         // 卫星号 (定义见表8，1~100:GPS, 101~200:GLONASS, 201~300:BDS)
        int8_t   freq_id;        // 频点编号 (对GLONASS为有效频率编号，其他系统保留，无意义时填0x7F)
        uint32_t c_code_pseudo_range;  // C码伪距 (量化单位0.01m，无效时填0x00000000)
        uint32_t p_code_pseudo_range;  // P码伪距 (量化单位0.01m，无效时填0x00000000)
        int64_t  carrier_phase;  // 载波相位 (量化单位0.001周，无效时填0x7FFFFFFFFFFFFFFF)
        int32_t  instant_doppler;// 瞬时载波多普勒 (量化单位0.01Hz，无效时填0x7FFFFFFF)
        uint8_t  carrier_snr;    // 载波信噪比 (量化单位0.25dBHz，无效时填0x00)
        uint32_t cont_lock_time; // 连续锁定时间 (单位ms，无效时填0x00000000)
    } channels[]; // 柔性数组，实际长度为 valid_channel_count

    // 注意：子帧尾部还有CRC校验（但标准中描述子帧结构内包含帧尾，具体实现时需仔细对齐）
} gnss_meas_subframe_t;


// 基准站信息帧 - 数据体结构
typedef struct {
    uint8_t  coord_sys_type;    // 基准站位置所属坐标系类型 (0:WGS-84, 1:PZ-90, 2:CGCS2000)
    int64_t  ref_station_x;     // 基准站坐标X方向分量 (量化单位0.001m，无效时填0x7FFFFFFFFFFFFFFF)
    int64_t  ref_station_y;     // 基准站坐标Y方向分量 (量化单位0.001m，无效时填0x7FFFFFFFFFFFFFFF)
    int64_t  ref_station_z;     // 基准站坐标Z方向分量 (量化单位0.001m，无效时填0x7FFFFFFFFFFFFFFF)
} gnss_reference_station_frame_body_t;


// 频点类型枚举，基于表9的b6~b7位定义
enum class FrequencyType : uint8_t {
    GPS_L1_GLONASS_G1_BDS_B1 = 0,  // 00: GPS L1/GLONASS G1/BDS B1
    GPS_L2_GLONASS_G2_BDS_B2 = 1,  // 01: GPS L2/GLONASS G2/BDS B2
    GPS_L5_GLONASS_G3_BDS_B3 = 2   // 10: GPS L5/GLONASS G3/BDS B3
    // 值11未定义，保留
};

// 码类型枚举，基于表9的b8位定义
enum class CodeType : uint8_t {
    CoarseCode = 0,  // 0: 粗码(C码)
    PreciseCode = 1  // 1: 精码(P码)
};

// 通道跟踪状态字结构体，基于表9定义
// 使用位域表示16位二进制整数，假设b0为最低有效位(LSB)
struct ChannelTrackingStatusWord {
    // 位字段定义
    bool codeLoopSync : 1;               // b0: 码环同步完成(1)或未完成(0)
    bool carrierLoopSync : 1;          // b1: 载波环同步完成(1)或未完成(0)
    bool bitSync : 1;                    // b2: 位同步完成(1)或未完成(0)
    bool frameSync : 1;                  // b3: 帧同步完成(1)或未完成(0)
    bool raimFault : 1;                  // b4: RAIM检测有故障(1)或无故障(0)
    bool participateInPositioning : 1;   // b5: 参与定位(1)或未参与(0)
    uint8_t frequencyType : 2;            // b6~b7: 频点类型(2位)，对应FrequencyType枚举
    CodeType codeType : 1;               // b8: 码的类型(1位)，对应CodeType枚举
    uint8_t reserved : 7;                // b9~b15: 保留位(7位)，置0或自定义

    // 默认构造函数，初始化所有字段
    ChannelTrackingStatusWord()
        : codeLoopSync(false),
          carrierLoopSync(false),
          bitSync(false),
          frameSync(false),
          raimFault(false),
          participateInPositioning(false),
          frequencyType(0),
          codeType(CodeType::CoarseCode),
          reserved(0) {}

};



// 频点信息结构
struct FreqInfo {
    uint8_t freqNo;      // 频点编号
    uint8_t snr;         // 信噪比
    uint8_t status;      // 频点状态
    uint8_t trackState;  // 跟踪状态
};

// 卫星信息结构
struct SatelliteInfo {
    uint8_t prn;             // PRN号
    uint16_t azimuth;        // 方位角（度）
    uint8_t elevation;       // 高度角（度）
    uint8_t sysStatus;       // 系统标识
    uint8_t snr;            // 信噪比
    uint8_t freqStatus;      // 频点标识
    uint8_t freqCount;       // 频点数量
    QVector<FreqInfo> freqs; // 频点信息数组
};

// SATSINFO数据结构
struct SATSINFOData {
    uint8_t satNumber;                  // 卫星总数
    uint8_t version;                    // 版本号
    uint8_t reserve1;                   // 保留字段1
    uint8_t reserve2;                   // 保留字段2
    uint8_t reserve3;                   // 保留字段3
    uint8_t frqFlag;                    // 频率标识
    QVector<SatelliteInfo> satellites;  // 卫星信息数组
    uint32_t crc;                       // CRC校验
};


// 定义OBSVM消息头的基础结构（根据表格7-49或7-50，这里只是示例）
struct ObsvmHeader
{
    // 这里需要根据实际的表7-49或7-50来定义
    // 假设包含消息ID、长度等信息
    uint16_t msgId;
    uint16_t msgLength;
    uint32_t timeStamp;
    // ... 其他字段

    // 获取头部大小
    static constexpr size_t size() {
        return sizeof(ObsvmHeader);
    }
};

// 通道跟踪状态位域结构体
// 对应表 7-55，描述从Bit 0到Bit 31的位域定义
// 使用位域紧凑存储，总大小为32位（4字节）
struct ChannelTrackingStatus {
    // 使用联合体同时支持位域访问和整数值访问
    union {
        quint32 value;  // 32位整数值

        struct {
            // 位域定义（注意：位域的位顺序取决于编译器和平台）
//            #if Q_BYTE_ORDER == Q_BIG_ENDIAN
            // 大端序布局
            unsigned int reserved0_3 : 5;       // 位0-4: 保留
            unsigned int sv_channel : 5;        // 位5-9: SV通道号
            unsigned int carrier_phase_valid : 1; // 位10: 载波相位有效标志
            unsigned int reserved : 1;            // 位11: 载波相位有效标志
            unsigned int pseudorange_valid : 1;  // 位12: 伪距有效标志
            unsigned int reserved13_16 : 3;      // 位13-15: 保留

            unsigned int satellite_system : 3;  // 位16-18: 卫星系统标识
            unsigned int reserved20 : 1;        // 位19: 保留
            unsigned int reserved21 : 1;        // 位20: 保留
            unsigned int signal_type : 5;       // 位21-25: 信号类型
            unsigned int L2C : 1;       // 位26: 信号类型
            unsigned int reserved26_31 : 5;     // 位27-31: 保留
//            #else
            // 小端序布局（x86架构常见）
            // 注意：在小端序中，位域的顺序可能会反转
            // 这里按照小端序重新排列
//            unsigned int reserved26_31 : 5;     // 位27-31: 保留
//            unsigned int L2C : 1;       // 位26: 信号类型
//            unsigned int signal_type : 5;       // 位21-25: 信号类型
//             unsigned int reserved21 : 1;        // 位20: 保留
//            unsigned int reserved20 : 1;        // 位19: 保留
//            unsigned int satellite_system : 3;  // 位16-18: 卫星系统标识
//            unsigned int reserved13_16 : 3;      // 位13-15: 保留
//            unsigned int pseudorange_valid : 1;  // 位12: 伪距有效标志
//            unsigned int reserved : 1;            // 位11: 载波相位有效标志
//            unsigned int carrier_phase_valid : 1; // 位10: 载波相位有效标志
//            unsigned int sv_channel : 5;        // 位5-9: SV通道号
//            unsigned int reserved0_3 : 5;       // 位0-4: 保留
//            #endif
        } bits;
    };
};

// 观测数据块结构体
struct ObsDataBlock
{
    // 注意：OBSVM header 是单独的结构，此处不包含
    // 但为了完整的数据解析，这里给出观测数据部分的结构体

    uint16_t systemFreq;     // GLONASS卫星频点号 (H+4, 2字节)
    uint16_t prnSlot;        // 卫星PRN号 (H+6, 2字节)
    double psr;             // 码伪距测量值，单位：m (H+8, 8字节)
    double adr;             // 载波相位，单位：度 (H+16, 8字节)
    uint16_t psrStd;        // 码伪距标准差*100 (H+24, 2字节)
    uint16_t adrStd;         // 载波相位标准差*10000 (H+26, 2字节)
    float dopp;             // 瞬时多普勒，单位：Hz (H+28, 4字节)
    uint16_t cn0;           // 载噪比*100 (H+32, 2字节)
    uint16_t reserved;       // 保留字段 (H+34, 2字节)
    float locktime;         // 连续跟踪时间，单位：s (H+36, 4字节)
    ChannelTrackingStatus ch_trstatus;   // 跟踪状态
    quint8 Satellite_type;  //卫星类型


    // 静态方法用于验证结构体大小
    static constexpr size_t size() {
        return sizeof(ObsDataBlock);
    }


};
#pragma pack(push, 1)  // 确保1字节对齐，避免结构体填充
// 完整的OBSVM消息结构
struct ObsvmMessage
{
    //uint8_t header;             // 消息头
    uint32_t obsCount;              // 观测信息个数
    QVector<ObsDataBlock> obsData;  // 观测数据块列表
    uint32_t crc32;                 // 32位CRC校验
    char endMarker;                 // 语句结束符

    // 从字节流解析消息
    bool parseFromBytes(const uint8_t* data, size_t length);

    // 序列化到字节流
    std::vector<uint8_t> serializeToBytes() const;
};
#pragma pack(pop)  // 确保1字节对齐，避免结构体填充

#pragma pack(push, 1)  // 确保1字节对齐，避免结构体填充
struct Channel1SatelliteParams {
    // 通道1卫星号
    // 无效值：0x0000
    uint16_t satelliteNumber;
    // 通道1卫星通道跟踪状态
    // 无效值：0x0000
    ChannelTrackingStatusWord CTStatusWord;
    // 通道1卫星信噪比
    // 无效值：0x00
    uint8_t signalToNoiseRatio;

    // 构造函数，初始化所有值为无效状态
    Channel1SatelliteParams()
        : satelliteNumber(0x0000)
        , signalToNoiseRatio(0x00) {}
};
#pragma pack(pop)  // 确保1字节对齐，避免结构体填充


#pragma pack(push, 1)  // 确保1字节对齐，避免结构体填充
struct FrameTail {
    uint32_t crc; // 整帧CRC校验码，4字节
    uint8_t tail1; // 帧尾1，值为0x66
    uint8_t tail2; // 帧尾2，值为0x44
    uint8_t tail3; // 帧尾3，值为0x12

    FrameTail()
    {
        crc = 0x00112233;
        tail1 = 0x66;
        tail2 = 0x44;
        tail3 = 0x12;
    }

    };
#pragma pack(pop)  // 确保1字节对齐，避免结构体填充

// 卫星频率编号特殊值定义
constexpr int8_t GLONASS_FREQUENCY_INVALID = 0x7F;  // GLONASS无效频率编号

// 无效值定义
constexpr uint32_t INVALID_CODE_PSEUDORANGE = 0x00000000;  // 无效C/P码伪距
constexpr int64_t INVALID_CARRIER_PHASE = 0x7FFFFFFFFFFFFFFF;  // 无效载波相位
constexpr int32_t INVALID_DOPPLER = 0x7FFFFFFF;  // 无效多普勒
constexpr uint8_t INVALID_SNR = 0x00;  // 无效信噪比
constexpr uint32_t INVALID_LOCK_TIME = 0x00000000;  // 无效锁定时间


#pragma pack(push , 1)
// 通道数据结构体
struct ChannelData
{
    uint16_t satelliteNumber;      // 卫星号，2字节
    int8_t frequencyNumber;        // 卫星频率编号，1字节（二进制补码）
    uint32_t Cseudorange;          // C码伪距，4字节，单位0.01m
    uint32_t Pseudorange;          // P码伪距，4字节，单位0.01m
    int32_t carrierDoppler;        // 瞬时载波多普勒，4字节，单位0.01Hz（二进制补码）
    uint8_t carrierSNR;            // 载波信噪比，1字节，单位0.25dBHz
    uint32_t Ctracking_time;       // 连续跟踪时间
};
#pragma pack(pop)

#pragma pack(push , 1)
struct ChildFrame
{
        quint8 frameHeader;           // 帧头，1字节，固定为0x10
        quint8 subframeType;          // 子帧类型，1字节
        quint8 subframeSyncCode;      // 子帧同步码，1字节
        quint8 validChannelCount;     // 有效通道数，1字节
        quint32 time1;                // 时间1，4字节
        quint64 time2;                // 时间2，8字节，单位0.1μs
        quint8 reserved1;             // 保留字节1，1字节
        quint8 reserved2;             // 保留字节2，1字节
        QVector<ChannelData> channels;
        quint32 crcChecksum;          // CRC校验字，4字节
        quint8 frameTail1;           // 帧尾1，1字节，固定为0x10
        quint8 frameTail2;           // 帧尾2，1字节，固定为0x03


        ChildFrame()
        {
            frameHeader = 0x10;
            reserved1 =  0x00;
            reserved1 =  0x00;
            crcChecksum = 0xC1C2C3C4;
            frameTail1  = 0x10;
            frameTail2  = 0x03;
        }
};
#pragma pack(pop)

#pragma pack(push , 1)
// 全帧结构体
struct SubFrame
{
    uint8_t frame_number;           // 帧数量
    QVector<ChildFrame> childframe;
};
#pragma pack(pop)

// 测量元素帧结构体
struct MeasurementFrame
{
    uint8_t subframeCount;         // 子帧数量，1字节，有效范围0~9
    std::vector<SubFrame> subframes;  // 子帧数组
};

#pragma pack(pop)  // 恢复默认对齐方式


// 基准站信息帧数据体结构
struct ReferenceStationInfoFrame
{
    // 1. 基准站位置所属坐标系类型
    uint8_t coordinateSystemType;  // 1字节，二进制编码
    // 说明：坐标系类型表示定位测速结果的所属坐标系定义同表6

    // 2. 基准站坐标X方向分量
    int64_t coordinateX;  // 8字节，二进制补码
    // 3. 基准站坐标Y方向分量
    int64_t coordinateY;  // 8字节，二进制补码
    // 4. 基准站坐标Z方向分量
    int64_t coordinateZ;  // 8字节，二进制补码

    ReferenceStationInfoFrame(){
        coordinateSystemType = 0;
        coordinateX = 0x7FFFFFFFFFFFFFFF;
        coordinateY = 0x7FFFFFFFFFFFFFFF;
        coordinateZ = 0x7FFFFFFFFFFFFFFF;
    }
};



// 枚举表示卫星导航系统
enum class SatelliteSystem {
    GPS,
    GLONASS,
    BDS
};

// 结构体用于返回计算结果
struct TimeResult {
    qint64 weekOrDays;  // 时间周（GPS/BDS为周数，GLONASS为累积日数）
    qint64 second;       // 周秒（GPS/BDS为周内秒数，GLONASS为日内秒数）
};




#endif // MSTRUT_H
