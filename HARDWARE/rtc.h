#ifndef __RTC_H__
#define __RTC_H__
#include "sys.h"

// ISL1208 I2C地址
#define ISL1208_I2C_ADDR        0x6F  // 7位地址，左移后为0xDE

// ISL1208寄存器地址
#define ISL1208_REG_SC          0x00  // 秒
#define ISL1208_REG_MN          0x01  // 分
#define ISL1208_REG_HR          0x02  // 时
#define ISL1208_REG_DT          0x03  // 日
#define ISL1208_REG_MO          0x04  // 月
#define ISL1208_REG_YR          0x05  // 年
#define ISL1208_REG_DW          0x06  // 星期
#define ISL1208_REG_SR          0x07  // 状态寄存器
#define ISL1208_REG_INT         0x08  // 中断寄存器
#define ISL1208_REG_ATR         0x0A  // 模拟微调寄存器
#define ISL1208_REG_DTR         0x0B  // 数字微调寄存器
#define ISL1208_REG_USER_RAM1   0x13  // 用户RAM开始地址
#define ISL1208_REG_USER_RAM2   0x14
// ... 最多到0x1F

// 状态寄存器位定义
#define ISL1208_SR_RTCF          (1 << 0)  
#define ISL1208_SR_BAT          (1 << 1)  // 电池状态位
#define ISL1208_SR_WRTC         (1 << 4)  // 使能RTC写操作

// 时间寄存器掩码
#define ISL1208_SECONDS_MASK    0x7F
#define ISL1208_MINUTES_MASK    0x7F
#define ISL1208_HOUR_12_MASK    0x1F
#define ISL1208_HOUR_24_MASK    0x3F
#define ISL1208_DATE_MASK       0x3F
#define ISL1208_MONTH_MASK      0x1F
#define ISL1208_YEAR_MASK       0xFF
#define ISL1208_DAY_MASK        0x07

// 控制寄存器位
#define ISL1208_HR_MIL          (1 << 7)  // 24小时制
#define ISL1208_HR_PM           (1 << 5)  // PM指示(12小时制)

// RTC时间结构体
typedef struct {
    uint8_t seconds;    // 0-59
    uint8_t minutes;    // 0-59
    uint8_t hours;      // 0-23 (24小时制)
    uint8_t day;        // 1-7 (星期几)
    uint8_t date;       // 1-31
    uint8_t month;      // 1-12
    uint8_t year;       // 0-99 (2000-2099)
    uint8_t format_12h; // 1:12小时制, 0:24小时制
} ISL1208_Time_t;

// RTC日期结构体
typedef struct {
    uint8_t day;
    uint8_t month;
    uint16_t year;      // 完整年份
} ISL1208_Date_t;

// 闹钟结构体
typedef struct {
    uint8_t seconds;    // 闹钟秒
    uint8_t minutes;    // 闹钟分
    uint8_t hours;      // 闹钟时
    uint8_t date;       // 闹钟日
    uint8_t month;      // 闹钟月
    uint8_t weekday;    // 闹钟星期
    uint8_t enabled;    // 闹钟使能
} ISL1208_Alarm_t;

HAL_StatusTypeDef ISL1208_Init(void);
HAL_StatusTypeDef ISL1208_SetTime(ISL1208_Time_t *time);
HAL_StatusTypeDef ISL1208_GetTime(ISL1208_Time_t *time);
int ISL1208_test(void);

#endif