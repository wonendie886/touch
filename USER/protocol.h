#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "stdint.h"

/// \def the max length of one frame data
#define FRAME_MAX_LEN 200

#define FRAME_MIN_LEN 40
#define PARAM_MAX_LEN (FRAME_MAX_LEN - FRAME_MIN_LEN)

#define HEAD_OFFSET 0
#define HEAD_SIZE 2

#define LEN_OFFSET (HEAD_OFFSET+HEAD_SIZE)
#define LEN_SIZE 1

#define SYSSTATE_OFFSET (LEN_OFFSET+LEN_SIZE)
#define SYSSTATE_SIZE 1

#define SYSTEMP_OFFSET (SYSSTATE_OFFSET+SYSSTATE_SIZE)
#define SYSTEMP_SIZE 3

#define FRITEMP_OFFSET (SYSTEMP_OFFSET+SYSTEMP_SIZE)
#define FRITEMP_SIZE 4

#define ABNORMALSTATE_OFFSET (FRITEMP_OFFSET+FRITEMP_SIZE)
#define ABNORMALSTATE_SIZE 16

#define CMDTYPE_OFFSET (ABNORMALSTATE_OFFSET+ABNORMALSTATE_SIZE)
#define CMDTYPE_SIZE 1

#define CMDSTEP_OFFSET (CMDTYPE_OFFSET+CMDTYPE_SIZE)
#define CMDSTEP_SIZE 2

#define CMDNUMBER_OFFSET (CMDSTEP_OFFSET+CMDSTEP_SIZE)
#define CMDNUMBER_SIZE 1

#define CMDCHANNELA_STATE_OFFSET (CMDNUMBER_OFFSET+CMDNUMBER_SIZE)
#define CMDCHANNELA_STATE_SIZE 1

#define CMDCHANNELA_PROGRESS_OFFSET (CMDCHANNELA_STATE_OFFSET+CMDCHANNELA_STATE_SIZE)
#define CMDCHANNELA_PROGRESS_SIZE 1

#define CMDCHANNELB_STATE_OFFSET (CMDCHANNELA_PROGRESS_OFFSET+CMDCHANNELA_PROGRESS_SIZE)
#define CMDCHANNELB_STATE_SIZE 1

#define CMDCHANNELB_PROGRESS_OFFSET (CMDCHANNELB_STATE_OFFSET+CMDCHANNELB_STATE_SIZE)
#define CMDCHANNELB_PROGRESS_SIZE 1

#define CMDCHANNELC_STATE_OFFSET (CMDCHANNELB_PROGRESS_OFFSET+CMDCHANNELB_PROGRESS_SIZE)
#define CMDCHANNELC_STATE_SIZE 1

#define CMDCHANNELC_PROGRESS_OFFSET (CMDCHANNELC_STATE_OFFSET+CMDCHANNELC_STATE_SIZE)
#define CMDCHANNELC_PROGRESS_SIZE 1

#define PARAM_OFFSET (CMDCHANNELC_PROGRESS_OFFSET + CMDCHANNELC_PROGRESS_SIZE)

#define STEAM_PARAM_SIZE 4
#define MACHINE_PARAM_SIZE 22
#define POLL_PARAM_SIZE 3
#define DeepMaintenance_PARAM_SIZE 5
#define PCB_VERSION_PARAM_SIZE 30

#define FRAME_HEAD_1 0xE7
#define FRAME_HEAD_2 0x7E

#define FRAME_FOOT_1 0x7D
#define FRAME_FOOT_2 0xD7
///以为为上位机发-单品字节数
#define COFFEE_BYTE 30
#define TEA_BYTE 9
#define STEAM_BYTE 9
#define HOTWATER_BYTE 10
#define COLDWATER_BYTE 10
#define HOTMILK_BYTE 12
#define COLDMILK_BYTE 11
#define HOTFOAM_BYTE 11
#define COLDFOAM_BYTE 11
#define MILKCOVER_BYTE 11
#define HOTMILKCOVER_BYTE 11
#define DELAY_BYTE 9
///以为为下位机-单品字节数
#define COFFEE_BYTE_MCU 14
#define HOTWATER_BYTE_MCU 10
#define COLDWATER_BYTE_MCU 0
#define HOTMILK_BYTE_MCU 10
#define COLDMILK_BYTE_MCU 0
#define HOTFOAM_BYTE_MCU 0
#define COLDFOAM_BYTE_MCU 0
#define MILKCOVER_BYTE_MCU 0
#define HOTMILKCOVER_BYTE_MCU 0
#define POWDER_BYTE_MCU 0
#define SYRUP_BYTE_MCU 0
#define DELAY_BYTE_MCU 0
#define TEA_BYTE_MCU 0
#define STEAM_BYTE_MCU 10

extern const uint64_t	WARN_NONE;
extern const uint64_t	WARN_WATER_EMPTY;

extern const uint64_t   ERROR_HMICON_COM;

extern const uint8_t SYSTEMSTATE_NONE;
extern const uint8_t SYSTEMSTATE_STEAM_BOILER_FILLWATER;

//! A enum data Frame state{帧格式状态-枚举}
enum State{
	FRAME_OK = 1,        ///< data frame is ok{数据帧正常}
	FRAME_INVALID,  ///< invalid data frame,maybe head,foot and length is wrong{帧头，帧尾或者长度错误}
	FRAME_CRC_ERROR,      ///< crc is error{校验错误}
	FRAME_INVALID_CMD,    ///< invalid command{非法命令}
	FRAME_INVALID_CMD_NUMBER,   ///< invalid command number{非法命令编号}
	FRAME_INVALID_SYSTEM_STATE, ///< invalid system state{非法系统状态}
};

enum GrindMode{
    MODE_TIME = 0,
    MODE_WEIGHT,
};
enum STEPMODE{
    MODE_COARSE,
    MODE_FINE,
};

enum CmdGrindState
{
	CMD_STATE_IDLE = 0,
	CMD_STATE_REQUEST,
	CMD_STATE_EXECUTING,
	CMD_STATE_PAUSE,
	CMD_STATE_SUCCESS,
	CMD_STATE_CANCEL,
};

//! A enum data Command type{命令类型-枚举}
// enum CmdType
// {
//     CMDTYPE_NULL = 0x00,  ///< null command{空命令}
//     CMDTYPE_GRIND = 0x01,  ///< grind {磨豆}
//     CMDTYPE_CALIBRATION = 0x02,  ///< calibration{校准}
//     CMDTYPE_SET_GAP = 0x03,    ///< set gap{设置间距}
// 	CMDTYPE_FILL_WATER = 0x04, /// < fill water{加水}
// 	CMDTYPE_STEAM = 0x05,
// };

//! A enum command mode{咖啡机命令-枚举}
enum CmdType
{
    CMDTYPE_BEVERAGEMAKE = 0x01,  ///< make beverage command{制作咖啡-命令}
    CMDTYPE_RINSE_COFFEE = 0x02,  ///< rinse coffee tube system{冲洗咖啡冲煮系统管路-命令}
    CMDTYPE_RINSE_MILK = 0x03,    ///< rinse milk tube system{冲洗牛奶系统管路-命令}
    CMDTYPE_RINSE_POWDER = 0x04,  ///< rinse powder tube system{冲洗粉料系统管理-命令}

    CMDTYPE_CLEAN_BREWBLOCK = 0x05,  ///< wash coffee tube system{清洗咖啡冲煮头-命令}
    CMDTYPE_CLEAN_COFFEE = 0x06, ///< clean coffee tube system{清洗咖啡冲煮系统管路-命令}
    CMDTYPE_CLEAN_MILK = 0x07,   ///< clean milk tube system{清洗牛奶系统管路-命令}

    CMDTYPE_DESCALE = 0x08, ///< descale{除垢-命令}
    CMDTYPE_EMPTY_WATER = 0x09, ///< empty water of tube system{清空水路-命令}
    CMDTYPE_SYSTEM_FILL_WATER = 0x0A, ///< fill water{系统补水-命令}
    CMDTYPE_SYSTEM_CHECK = 0x0B, ///< check system{系统自检-命令}
    CMDTYPE_SYSTEM_CALIBRATION_FILL = 0x0C, ///< calibration fill{校准补水-命令}

    CMDTYPE_HANDSHAKE = 0x0F,     ///< handshake with coffee mcu board command{握手-命令}
    CMDTYPE_POLL = 0x10,         ///< poll the state of the coffee mcu board command{轮询-命令}
    CMDTYPE_CANCEL = 0x11,       ///< cancel current command{取消命令-命令}
    CMDTYPE_SET_PAREM = 0x12,    ///< set parameter{设置参数-命令}
    CMDTYPE_UPDATE = 0x13,       ///< update the coffee mcu software{更新程序-命令}

    CMDTYPE_CHECK_FUNCTION = 0x14,       ///< check function{功能自检-命令}
    CMDTYPE_INIT = 0x15,         ///< init the coffee mcu board command{初始化-命令}
    CMDTYPE_POWEROFF = 0x16,     ///< power off the coffee mcu board command{保留}
    CMDTYPE_ONEKEYCLEAN = 0x17,      ///
    CMDTYPE_STEAMWANDRINSE = 0x18,      ///
    CMDTYPE_MAKE_STEAM = 0x19,      ///make steam command(蒸汽制作命令,为了独立制作蒸汽)
    CMDTYPE_RINSE_FILTER = 0x1A,    ///rinse filter(滤芯冲洗命令)
    CMDTYPE_RINSE_SYRUP = 0x1B,     ///冲洗糖浆系统
    CMDTYPE_CLEAN_SYRUP = 0x1C,     ///清洗糖浆系统
    CMDTYPE_SYSTEM_CLEAN  = 0x1D,
    CMDTYPE_BEVERAGEMAKE_CHANNELB = 0x1E,
    CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB = 0x1F,
    CMDTYPE_BEVERAGEMAKE_CHANNELC = 0x20,
    CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELC = 0x21,
    CMDTYPE_CHANGE_WATER = 0x22,    ///蒸汽锅炉换水
    CMDTYPE_RINSE_BREWBLOCK = 0x23,  ///< quick wash coffee tube system{快速冲洗咖啡冲煮头-命令}
    CMDTYPE_WAKEUP = 0x24,  ///wake up machine{唤醒-命令}
    CMDTYPE_STOP_MACHINE = 0x25,    ///machine stop work{机器停止工作-命令}
    CMDTYPE_RELEASE_STEAM = 0x26,   ///release steam{释放蒸汽-命令}，用于停止蒸汽，停止加热

    CMDTYPE_SET_PCB_VERSION = 0x30,
    CMDTYPE_GET_PCB_VERSION = 0x31,
    CMDTYPE_GRIND = 0x32,
    CMDTYPE_TEMP = 0x33,
};

enum BEVERAGE_TYPE
{
    TYPE_NULL = 0,
    TYPE_COFFEE,
    TYPE_HOTWATER,
    TYPE_COLDWATER,
    TYPE_HOTMILK,
    TYPE_COLDMILK,
    TYPE_HOTFOAM,
    TYPE_COLDFOAM,
    TYPE_MILKCOVER,
    TYPE_POWDER1,
    TYPE_POWDER2,
    TYPE_POWDER3,
    TYPE_POWDER4,
    TYPE_POWDER5,
    TYPE_SYRUP1,
    TYPE_SYRUP2,
    TYPE_SYRUP3,
    TYPE_SYRUP4,
    TYPE_SYRUP5,
    TYPE_DELAY,
    TYPE_TEA1,
    TYPE_TEA2,
    TYPE_TEA3,
    TYPE_TEA4,
    TYPE_TEA5,
    TYPE_HOTMILKCOVER,
	TYPE_STEAM,
};

struct GrindData
{
	uint8_t mode;
	uint16_t target;
	uint8_t cmd;
	uint8_t cmd_state;
	uint8_t cmd_number;
};

struct GrindRealData
{
	struct GrindData data;
	uint16_t time; //uint: ms
	uint16_t weight; //uint: 0.1g
};

enum CmdState{
    CMDSTATE_IDLE = 0,
    EXECUTING = 1,
    STAGE_SUCCESS = 2,
    ALL_SUCCESS = 3,
    FAIL = 4,
};

struct Frame{
	uint16_t head;
	uint8_t len;
	uint8_t warn;
    uint8_t mode;
	uint16_t target;
	uint8_t cmd;
	uint8_t cmd_state;
    uint8_t cmd_number;
    volatile uint8_t cmd_channelA_state;
    volatile uint8_t cmd_channelA_progress;
	uint8_t crc;
	uint16_t foot;
};

struct Protocol{
	struct Frame frame;
	uint8_t frameState;
};

void getProtocol(const uint8_t *buf,struct Protocol *ret);
int setGrindCmdType(uint8_t *buf,struct GrindData *pData);
int setCalibrationCmdType(uint8_t *buf,struct GrindData *pData);
int setGapCmdType(uint8_t *buf,struct GrindData *pData);
int setFillwater(uint8_t *buf,struct GrindData *pData);
int setdosteam(uint8_t *buf,struct GrindData *pData);
int setcancel(uint8_t *buf,struct GrindData *pData);
int settemp(uint8_t *buf,struct GrindData *pData);
int setdescale(uint8_t *buf,struct GrindData *pData);
int setPoll(uint8_t *buf,struct GrindData *pData);
int setchangewater(uint8_t *buf,struct GrindData *pData);
int setemptywater(uint8_t *buf,struct GrindData *pData);

#endif
