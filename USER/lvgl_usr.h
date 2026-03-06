#ifndef __LVGL_USR_H
#define __LVGL_USR_H

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "rtc.h"

void update_time_display(ISL1208_Time_t *time);

#endif /* __LVGL_USR_H */
