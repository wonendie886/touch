/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "protocol.h"
#include <string.h>
#include <stdlib.h>
#include "flash.h"
#include "main.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

extern struct GrindRealData GrindDataStr;
extern bool screen_flag;
uint8_t descale_setting = 0;
uint16_t volume;
uint16_t currentstep = 1;
uint8_t waiting_ack = 0;
TimeDataStruct TimeDataStr = {30, 45, 60};  // 默认值

static uint8_t active_time_setting = 0; 
static uint8_t matain_setting = 0; 
static void screen_btn_cancel_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        GrindDataStr.data.cmd = CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_steam4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        GrindDataStr.data.cmd = CMDTYPE_MAKE_STEAM;
        volume = TimeDataStr.time3;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_steam3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        GrindDataStr.data.cmd = CMDTYPE_MAKE_STEAM;
        volume = TimeDataStr.time2;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_steam2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        GrindDataStr.data.cmd = CMDTYPE_MAKE_STEAM;
        volume = TimeDataStr.time1;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_rinse_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        GrindDataStr.data.cmd = CMDTYPE_MAKE_STEAM;
        volume = 1;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        screen_flag = false;
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_btn_cancel, screen_btn_cancel_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam4, screen_btn_steam4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam3, screen_btn_steam3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam2, screen_btn_steam2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_rinse, screen_btn_rinse_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_menu, screen_btn_menu_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_btn_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        screen_flag = true;        
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //锅炉温度
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        const char* current_text = lv_label_get_text(guider_ui.screen_1_label_set);
        lv_textarea_set_text(guider_ui.screen_1_spinbox_set, current_text);
        float value = atof(current_text);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_set, value); 

        active_time_setting = 4;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_settime1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //时间1
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_set, TimeDataStr.time1); 
        active_time_setting = 1;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_settime2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //时间2
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_set, TimeDataStr.time2); 
        active_time_setting = 2;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_settime3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //时间3
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_set, TimeDataStr.time3); 
        active_time_setting = 3;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_certain_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //确定修改，更新flash
        const char *txt = lv_textarea_get_text(guider_ui.screen_1_spinbox_set);
        if(active_time_setting == 4){
            lv_label_set_text_fmt(guider_ui.screen_1_label_set, "%s", txt);  
            GrindDataStr.data.target = atoi(txt);
            GrindDataStr.data.cmd = CMDTYPE_TEMP;
        } else if (active_time_setting == 1){
            lv_label_set_text_fmt(guider_ui.screen_btn_steam2_label, "%ss", txt); 
            lv_label_set_text_fmt(guider_ui.screen_1_btn_settime1_label, "%s", txt); 
            TimeDataStr.time1 = atoi(txt);
        } else if (active_time_setting == 2){
            lv_label_set_text_fmt(guider_ui.screen_btn_steam3_label, "%ss", txt); 
            lv_label_set_text_fmt(guider_ui.screen_1_btn_settime2_label, "%s", txt); 
            TimeDataStr.time2 = atoi(txt);
        } else if (active_time_setting == 3){
            lv_label_set_text_fmt(guider_ui.screen_btn_steam4_label, "%ss", txt); 
            lv_label_set_text_fmt(guider_ui.screen_1_btn_settime3_label, "%s", txt); 
            TimeDataStr.time3 = atoi(txt);
        } 
        saveCustomDataToFlash();
        lv_obj_add_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN); 
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_cancel_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //取消修改，数值不变
        lv_obj_add_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);  
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_descale_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //除垢
        lv_label_set_text(guider_ui.screen_1_label_hint, "步骤1:清空蓄水盘,并给清洗容器添加2包除垢粉+2L水,点击确定进入除垢;");
        lv_obj_add_flag(guider_ui.screen_1_btn_maintenancecancellation, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_1_cont_matain, LV_OBJ_FLAG_HIDDEN);
        matain_setting = 1;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_waterempty_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //清空水路
        lv_label_set_text(guider_ui.screen_1_label_hint, "清空蓄水盘,点击确定进入清空水路;");
        lv_obj_add_flag(guider_ui.screen_1_btn_maintenancecancellation, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_1_cont_matain, LV_OBJ_FLAG_HIDDEN);
        matain_setting = 2;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_waterchange_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //锅炉换水
        lv_label_set_text(guider_ui.screen_1_label_hint, "清空蓄水盘,点击确定进入锅炉换水;");
        lv_obj_add_flag(guider_ui.screen_1_btn_maintenancecancellation, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_1_cont_matain, LV_OBJ_FLAG_HIDDEN);
        matain_setting = 3;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_maintenancecancellation_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //维护取消，隐藏容器
        lv_obj_add_flag(guider_ui.screen_1_cont_matain, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_maintenancebegins_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //维护确认，根据触发按钮开始维护操作。
        if(matain_setting == 1){
            currentstep = 1;
            GrindDataStr.data.cmd = CMDTYPE_DESCALE;
            matain_setting = 0;
        } else if (matain_setting == 2) {
            GrindDataStr.data.cmd = CMDTYPE_EMPTY_WATER;
            matain_setting = 0;
        } else if (matain_setting == 3) {
            GrindDataStr.data.cmd = CMDTYPE_CHANGE_WATER;
            matain_setting = 0;
        }

        if (descale_setting == 1){
            currentstep = 2;
            GrindDataStr.data.cmd = CMDTYPE_DESCALE;
            waiting_ack = 1;
            descale_setting = 0;
        } else if (descale_setting == 2){
            currentstep = 3;
            GrindDataStr.data.cmd = CMDTYPE_DESCALE;
            descale_setting = 0;
        }
        lv_obj_add_flag(guider_ui.screen_1_btn_maintenancebegins, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(guider_ui.screen_1_label_hint, "正在维护中...");
        break;
    }
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1_btn_back, screen_1_btn_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_set, screen_1_btn_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_settime1, screen_1_btn_settime1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_settime2, screen_1_btn_settime2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_settime3, screen_1_btn_settime3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_certain, screen_1_btn_certain_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_cancel, screen_1_btn_cancel_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_descale, screen_1_btn_descale_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_waterempty, screen_1_btn_waterempty_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_waterchange, screen_1_btn_waterchange_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_maintenancecancellation, screen_1_btn_maintenancecancellation_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_maintenancebegins, screen_1_btn_maintenancebegins_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{
    // if(emptysuccess){
        
    // }
}
