#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "stdint.h"

/// \def the max length of one frame data
#define FRAME_MAX_LEN 20

#define FRAME_LEN 13

#define HEAD_OFFSET 0
#define HEAD_SIZE 2

#define LEN_OFFSET (HEAD_OFFSET+HEAD_SIZE)
#define LEN_SIZE 1

#define ABNORMALSTATE_OFFSET (LEN_OFFSET+LEN_SIZE)
#define ABNORMALSTATE_SIZE 1

#define MODE_OFFSET (ABNORMALSTATE_OFFSET+ABNORMALSTATE_SIZE)
#define MODE_SIZE 1

#define TARGET_OFFSET (MODE_OFFSET+MODE_SIZE)
#define TARGET_SIZE 2

#define CMDTYPE_OFFSET (TARGET_OFFSET+TARGET_SIZE)
#define CMDTYPE_SIZE 1

#define CMDSTATE_OFFSET (CMDTYPE_OFFSET+CMDTYPE_SIZE)
#define CMDSTATE_SIZE 1

#define CMDNUMBER_OFFSET (CMDSTATE_OFFSET+CMDSTATE_SIZE)
#define CMDNUMBER_SIZE 1

#define FOOT_OFFSET (CMDNUMBER_OFFSET+CMDNUMBER_SIZE)
#define FOOT_SIZE 2


#define FRAME_HEAD_1 0xE7
#define FRAME_HEAD_2 0x7E

#define FRAME_FOOT_1 0x7D
#define FRAME_FOOT_2 0xD7

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
};

//! A enum data Command type{命令类型-枚举}
enum CmdType
{
    CMDTYPE_NULL = 0x00,  ///< null command{空命令}
    CMDTYPE_GRIND = 0x01,  ///< grind {磨豆}
    CMDTYPE_CALIBRATION = 0x02,  ///< calibration{校准}
    CMDTYPE_SET_GAP = 0x03,    ///< set gap{设置间距}
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


struct Frame{
	uint16_t head;
	uint8_t len;
	uint8_t warn;
    uint8_t mode;
	uint16_t target;
	uint8_t cmd;
	uint8_t cmd_state;
    uint8_t cmd_number;
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

#endif
