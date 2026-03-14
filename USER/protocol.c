#include "protocol.h"
#include <stdio.h>

static int setCrc(void);

const uint64_t	WARN_NONE                         =    0x0000000000000000; ///< {无故障}
const uint64_t	WARN_WATER_EMPTY                 =    0x0000000000000001; ///< {缺水}


const uint64_t  ERROR_NONE                         =    0x0000000000000000; ///< {无故障}
const uint64_t	ERROR_HMICON_COM                   =    0x0000000000000001; ///< {串口通信故障}

const uint8_t SYSTEMSTATE_NONE = 0x00;
const uint8_t SYSTEMSTATE_STEAM_BOILER_FILLWATER = 0x01;

void getProtocol(const uint8_t *buf,struct Protocol *ret)
{
    //the head and foot is 0xe7 ? is the length valid?
    if (buf[HEAD_OFFSET] != FRAME_HEAD_1 || buf[HEAD_OFFSET+1] != FRAME_HEAD_2 || buf[LEN_OFFSET] != FRAME_MIN_LEN
        || buf[buf[LEN_OFFSET] - 2] != FRAME_FOOT_1 || buf[buf[LEN_OFFSET] - 1] != FRAME_FOOT_2) {
        ret->frameState = FRAME_INVALID;
    } else {
        ret->frame.head = FRAME_HEAD_1;
        ret->frame.foot = FRAME_FOOT_2;
        ret->frame.len = buf[LEN_OFFSET];

        uint8_t i = 0;
        uint32_t sum = 0;

        //skip the head,foot and crc
        for (i = HEAD_SIZE; i < ret->frame.len - 3; i++)
            sum += buf[i];

        //crc offset is 2 from behind, check the CRC sum
        if ((sum & 0xFF) == buf[ret->frame.len - 3]) {
            ret->frameState = FRAME_OK;
            ret->frame.crc = (sum & 0xFF);
        } else {
            ret->frameState = FRAME_CRC_ERROR;
            return;
        }

        // ret->frame.warn = buf[ABNORMALSTATE_OFFSET];
        // ret->frame.mode = buf[MODE_OFFSET];
        // ret->frame.target = buf[TARGET_OFFSET]  | buf[TARGET_OFFSET + 1] << 8;

        ret->frame.cmd = buf[CMDTYPE_OFFSET];
        // ret->frame.cmd_state = buf[CMDSTATE_OFFSET];
        ret->frame.cmd_number = buf[CMDNUMBER_OFFSET];
    }
}

static uint8_t m_buf[FRAME_MAX_LEN];
// int setGrindCmdType(uint8_t *buf,struct GrindData *pData)
// {
//     //set m_buf content
//     m_buf[HEAD_OFFSET] = FRAME_HEAD_1;
//     m_buf[HEAD_OFFSET+1] = FRAME_HEAD_2;
//     m_buf[LEN_OFFSET] =  FRAME_LEN;
//     m_buf[ABNORMALSTATE_OFFSET] = 0;

//     m_buf[MODE_OFFSET] = pData->mode;
//     m_buf[TARGET_OFFSET] = pData->target & 0x00FF;
//     m_buf[TARGET_OFFSET+1] = (pData->target >> 8) & 0x00FF;

//     m_buf[CMDTYPE_OFFSET] = CMDTYPE_GRIND;
//     m_buf[CMDSTATE_OFFSET] = pData->cmd_state;
//     m_buf[CMDNUMBER_OFFSET] = pData->cmd_number;

//     m_buf[m_buf[LEN_OFFSET] - 2] = FRAME_FOOT_1;
//     m_buf[m_buf[LEN_OFFSET] - 1] = FRAME_FOOT_2;

//     //set Crc content
//     setCrc();

//     uint8_t len = m_buf[LEN_OFFSET];
//     for (int i = 0; i < len; i++) {
//         buf[i] = m_buf[i];
//     }

//     return len;
// }

int setFillwater(uint8_t *buf,struct GrindData *pData)
{
    //set m_buf content
    m_buf[HEAD_OFFSET] = FRAME_HEAD_1;
    m_buf[HEAD_OFFSET+1] = FRAME_HEAD_2;
    m_buf[LEN_OFFSET] =  FRAME_MIN_LEN;
    m_buf[ABNORMALSTATE_OFFSET] = 0;

    m_buf[CMDTYPE_OFFSET] = CMDTYPE_SYSTEM_FILL_WATER;

    m_buf[m_buf[LEN_OFFSET] - 2] = FRAME_FOOT_1;
    m_buf[m_buf[LEN_OFFSET] - 1] = FRAME_FOOT_2;

    //set Crc content
    setCrc();

    uint8_t len = m_buf[LEN_OFFSET];
    for (int i = 0; i < len; i++) {
        buf[i] = m_buf[i];
    }
    return len;
}
extern uint16_t volume;
int setdosteam(uint8_t *buf,struct GrindData *pData)
{
    //set m_buf content
    m_buf[HEAD_OFFSET] = FRAME_HEAD_1;
    m_buf[HEAD_OFFSET+1] = FRAME_HEAD_2;
    m_buf[LEN_OFFSET] =  FRAME_MIN_LEN +STEAM_BYTE + 2;
    m_buf[ABNORMALSTATE_OFFSET] = 0;

    // m_buf[MODE_OFFSET] = 0;
    // m_buf[TARGET_OFFSET] = pData->target & 0x00FF;
    // m_buf[TARGET_OFFSET+1] = (pData->target >> 8) & 0x00FF;

    m_buf[CMDTYPE_OFFSET] = CMDTYPE_BEVERAGEMAKE_CHANNELB;
    // m_buf[CMDNUMBER_OFFSET] = pData->cmd_number;

    m_buf[m_buf[LEN_OFFSET] - 2] = FRAME_FOOT_1;
    m_buf[m_buf[LEN_OFFSET] - 1] = FRAME_FOOT_2;
    m_buf[PARAM_OFFSET + 0] = 1;
    m_buf[PARAM_OFFSET + 1] = 1;
    m_buf[PARAM_OFFSET + 2] = TYPE_STEAM;
    m_buf[PARAM_OFFSET + 2 + 1] = 0;
    m_buf[PARAM_OFFSET + 2 + 2] = volume & 0x00FF;
    m_buf[PARAM_OFFSET + 2 + 3] = volume & 0xFF00;
    m_buf[PARAM_OFFSET + 2 + 4] = 0;
    m_buf[PARAM_OFFSET + 2 + 5] = 0;
    m_buf[PARAM_OFFSET + 2 + 6] = 0;
    m_buf[PARAM_OFFSET + 2 + 7] = 0;
    m_buf[PARAM_OFFSET + 2 + 8] = 0;
    //set Crc content
     setCrc();

    uint8_t len = m_buf[LEN_OFFSET];
    for (int i = 0; i < len; i++) {
        buf[i] = m_buf[i];
    }

    return len;
}

int setcancel(uint8_t *buf,struct GrindData *pData)
{
    //set m_buf content
    m_buf[HEAD_OFFSET] = FRAME_HEAD_1;
    m_buf[HEAD_OFFSET+1] = FRAME_HEAD_2;
    m_buf[LEN_OFFSET] =  FRAME_MIN_LEN +1;
    m_buf[ABNORMALSTATE_OFFSET] = 0;

    // m_buf[MODE_OFFSET] = 0;
    // m_buf[TARGET_OFFSET] = pData->target & 0x00FF;
    // m_buf[TARGET_OFFSET+1] = (pData->target >> 8) & 0x00FF;

    m_buf[CMDTYPE_OFFSET] = CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB;
    // m_buf[CMDNUMBER_OFFSET] = pData->cmd_number;

    m_buf[m_buf[LEN_OFFSET] - 2] = FRAME_FOOT_1;
    m_buf[m_buf[LEN_OFFSET] - 1] = FRAME_FOOT_2;
    //set Crc content
     setCrc();

    uint8_t len = m_buf[LEN_OFFSET];
    for (int i = 0; i < len; i++) {
        buf[i] = m_buf[i];
    }

    return len;
}
// int setCalibrationCmdType(uint8_t *buf,struct GrindData *pData)
// {
//     //set m_buf content
//     m_buf[HEAD_OFFSET] = FRAME_HEAD_1;
//     m_buf[HEAD_OFFSET+1] = FRAME_HEAD_2;
//     m_buf[LEN_OFFSET] =  FRAME_LEN;
//     m_buf[ABNORMALSTATE_OFFSET] = 0;

//     m_buf[MODE_OFFSET] = 0;
//     m_buf[TARGET_OFFSET] = pData->target & 0x00FF;
//     m_buf[TARGET_OFFSET+1] = (pData->target >> 8) & 0x00FF;

//     m_buf[CMDTYPE_OFFSET] = CMDTYPE_CALIBRATION;
//     m_buf[CMDSTATE_OFFSET] = 0;
//     m_buf[CMDNUMBER_OFFSET] = pData->cmd_number;

//     m_buf[m_buf[LEN_OFFSET] - 2] = FRAME_FOOT_1;
//     m_buf[m_buf[LEN_OFFSET] - 1] = FRAME_FOOT_2;

//     //set Crc content
//     setCrc();

//     uint8_t len = m_buf[LEN_OFFSET];
//     for (int i = 0; i < len; i++) {
//         buf[i] = m_buf[i];
//     }

//     return len;
// }

// int setGapCmdType(uint8_t *buf,struct GrindData *pData)
// {
//     //set m_buf content
//     m_buf[HEAD_OFFSET] = FRAME_HEAD_1;
//     m_buf[HEAD_OFFSET+1] = FRAME_HEAD_2;
//     m_buf[LEN_OFFSET] =  FRAME_LEN;
//     m_buf[ABNORMALSTATE_OFFSET] = 0;

//     m_buf[MODE_OFFSET] = pData->mode;
//     m_buf[TARGET_OFFSET] = pData->target & 0x00FF;
//     m_buf[TARGET_OFFSET+1] = (pData->target >> 8) & 0x00FF;

//     m_buf[CMDTYPE_OFFSET] = CMDTYPE_SET_GAP;
//     m_buf[CMDSTATE_OFFSET] = 0;
//     m_buf[CMDNUMBER_OFFSET] = pData->cmd_number;

//     m_buf[m_buf[LEN_OFFSET] - 2] = FRAME_FOOT_1;
//     m_buf[m_buf[LEN_OFFSET] - 1] = FRAME_FOOT_2;

//     //set Crc content
//     setCrc();

//     uint8_t len = m_buf[LEN_OFFSET];
//     for (int i = 0; i < len; i++) {
//         buf[i] = m_buf[i];
//     }

//     return len;
// }

static int setCrc(void)
{
    //the head and foot is 0xe7 ? is the length valid?
    if (m_buf[HEAD_OFFSET] != FRAME_HEAD_1 || m_buf[HEAD_OFFSET+1] != FRAME_HEAD_2 || m_buf[LEN_OFFSET] < FRAME_MIN_LEN
        || m_buf[m_buf[LEN_OFFSET] - 2] != FRAME_FOOT_1 || m_buf[m_buf[LEN_OFFSET] - 1] != FRAME_FOOT_2) {
        return -1;
    } else {
        uint8_t i = 0;
        uint32_t sum = 0;
        //skip the head,foot and crc
        for (i = HEAD_SIZE; i < m_buf[LEN_OFFSET] - 3; i++)
            sum += m_buf[i];

        //crc offset is 2 from behind
        m_buf[m_buf[LEN_OFFSET] - 3] = sum & 0xFF;

    }

    return m_buf[LEN_OFFSET];
}
static int setCmdNumber(uint8_t number)
{
    //set m_buf content
    m_buf[CMDNUMBER_OFFSET] = number;

    //set Crc content
    setCrc();

    return m_buf[LEN_OFFSET];
}



