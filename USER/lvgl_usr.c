#include "lvgl_usr.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"

// 在实现文件中定义
void update_time_display(ISL1208_Time_t *time) {
    char time_str[20];
    char date_str[20];
    sprintf(time_str, "%02d:%02d", time->hours, time->minutes);
    sprintf(date_str, "%02d-%02d-%02d", time->year, time->month, time->date);
    lv_label_set_text(guider_ui.screen_label_time, time_str);
    lv_label_set_text(guider_ui.screen_label_date, date_str);
}