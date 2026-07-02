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
#include "can.h"
#include "flash.h"
#include <string.h>
#include <stdlib.h>
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif
static int Textselectionflag = 0;
extern struct GrindRealData GrindDataStr;
volatile uint16_t volume;
bool current_mode = MODE_COFFEE;
static uint8_t active_time_setting = 0; 
uint8_t teasetflag = 0;

static void SaveTeaParam(uint8_t index);
static void ShowTeaParam(uint8_t index);

static void screen_btn_coffee1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //coffee1做咖啡
        if(current_mode == MODE_COFFEE){
            volume = GrindSetData.time_1;
            GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        } else if (current_mode == MODE_TEA){
            GrindDataStr.data.cmd = CMDTYPE_MAKE_TEA;
        }

        break;
    }
    default:
        break;
    }
}

static void screen_btn_coffee3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //coffee3
        volume = GrindSetData.time_3;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_coffee2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //coffee2
        volume = GrindSetData.time_2;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_coffee4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //coffee4
        volume = GrindSetData.time_4;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        break;
    }
    default:
        break;
    }
}
uint8_t steamEnable = 0;
static void screen_btn_steam_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //steam
        if(steamEnable) {
            steamEnable = 0;
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftSteam(0,volume);
            #else
                canSendRightSteam(0,volume);
            #endif
            lv_obj_set_style_bg_opa(guider_ui.screen_btn_steam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
            // lv_label_set_text(guider_ui.screen_label_temp, temp_str);
            // lv_label_set_text(guider_ui.screen_btn_rinse_label, "Steam");
        } else {
            volume = 30;
            GrindDataStr.data.cmd = CMDTYPE_MAKE_STEAM;
            steamEnable = 1;
            lv_obj_set_style_bg_opa(guider_ui.screen_btn_steam, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
            // lv_label_set_text(guider_ui.screen_btn_rinse_label, "Cancel");
        }
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
        //rinse
        volume = 2;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_cancel_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //coffee cancel
        GrindDataStr.data.cmd = CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB;
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
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_hotwater_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //做热水can下发
        volume = GrindSetData.time_hotwater;
        printf("volume %d\n",volume);
        GrindDataStr.data.cmd = CMDTYPE_HOTWATER;
        break;
    }
    default:
        break;
    }
}


static void screen_btn_teaset1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒设置界面，从内存读取1数据并设置文本
        teasetflag = 0;
        ShowTeaParam(teasetflag);
        lv_obj_clear_flag(guider_ui.screen_cont_teaset, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_teaset3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒设置界面，从内存读取3数据并设置文本
        teasetflag = 2;
        ShowTeaParam(teasetflag);
        lv_obj_clear_flag(guider_ui.screen_cont_teaset, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_teaset2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒设置界面，从内存读取2数据并设置文本
        teasetflag = 1;
        ShowTeaParam(teasetflag);
        lv_obj_clear_flag(guider_ui.screen_cont_teaset, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_teaset4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒设置界面，从内存读取4数据并设置文本
        teasetflag = 3;
        ShowTeaParam(teasetflag);
        lv_obj_clear_flag(guider_ui.screen_cont_teaset, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}


static void screen_btn_save_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //隐藏容器，flash保存一次数据
        SaveTeaParam(teasetflag);
        flashDataSave();
        lv_obj_add_flag(guider_ui.screen_cont_teaset,LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_teacancel_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //取消修改，不做修改，隐藏容器
        lv_obj_add_flag(guider_ui.screen_cont_teaset, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btnm_choosemode_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    uint32_t btn_id = lv_btnmatrix_get_selected_btn(obj);   // 0 or 1

    if(btn_id == 0) {
        /* Coffee Extraction */
        // 1. 切换数据
        current_mode = MODE_COFFEE;

        // 2. 切换图片
        lv_obj_add_flag(guider_ui.screen_img_tea1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_tea2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_tea3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_tea4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_btn_teaset1,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_btn_teaset2,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_btn_teaset3,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_btn_teaset4,LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(guider_ui.screen_img_9, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_img_12, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_img_16, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_img_18, LV_OBJ_FLAG_HIDDEN);
    }
    else if(btn_id == 1) {
        /* Tea Beverage Extraction */
        current_mode = MODE_TEA;
        lv_obj_clear_flag(guider_ui.screen_img_tea1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_img_tea2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_img_tea3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_img_tea4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_btn_teaset1,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_btn_teaset2,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_btn_teaset3,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_btn_teaset4,LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_img_9, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_12, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_16, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_18, LV_OBJ_FLAG_HIDDEN);
    }
}
void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_btn_coffee1, screen_btn_coffee1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_coffee3, screen_btn_coffee3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_coffee2, screen_btn_coffee2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_coffee4, screen_btn_coffee4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam, screen_btn_steam_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_rinse, screen_btn_rinse_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_cancel, screen_btn_cancel_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_menu, screen_btn_menu_event_handler, LV_EVENT_ALL, ui);
    #if (LEFT_OR_COFFEE == RIGHT)
    lv_obj_add_event_cb(ui->screen_btn_hotwater, screen_btn_hotwater_event_handler, LV_EVENT_ALL, ui);
    #endif
    lv_obj_add_event_cb(ui->screen_btnm_choosemode,screen_btnm_choosemode_event_cb,LV_EVENT_VALUE_CHANGED,NULL);
    lv_obj_add_event_cb(ui->screen_btn_teaset1, screen_btn_teaset1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_teaset3, screen_btn_teaset3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_teaset2, screen_btn_teaset2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_teaset4, screen_btn_teaset4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_save, screen_btn_save_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_teacancel, screen_btn_teacancel_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_btn_steamtempset_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //获取旧设置值到微调器上，唤醒容器
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.temp_steam);

        active_time_setting = 5;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_coffeetempset_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒容器，获取设置温度值并显示在微调器上
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.temp_coffee);

        active_time_setting = 6;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_time1set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //time1的值获取到给微调器
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.time_1);

        active_time_setting = 1;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_time2set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //time2的值给微调器
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.time_2);

        active_time_setting = 2;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_time3set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //time3的值给微调器
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.time_3);

        active_time_setting = 3;
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_time4set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //time4的值给微调器
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.time_4);

        active_time_setting = 4;
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
        //取消修改，不做修改，隐藏容器
        lv_obj_add_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);  
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
        //确认修改，新值下发，隐藏容器
        int32_t spinbox_value = lv_spinbox_get_value(guider_ui.screen_1_spinbox_1);

        char str_value[16];
        sprintf(str_value, "%ld", (long)spinbox_value); 
        // const char *txt = lv_textarea_get_text(guider_ui.screen_1_spinbox_1);
        if(active_time_setting == 1){
            lv_label_set_text_fmt(guider_ui.screen_label_9, "%ss", str_value);  
            lv_label_set_text_fmt(guider_ui.screen_1_btn_time1set_label, "%s", str_value);
            GrindSetData.time_1 = spinbox_value;
        } else if (active_time_setting == 2){
            lv_label_set_text_fmt(guider_ui.screen_label_19, "%ss", str_value);  
            lv_label_set_text_fmt(guider_ui.screen_1_btn_time2set_label, "%s", str_value);
            GrindSetData.time_2 = spinbox_value;            
        } else if (active_time_setting == 3){
            lv_label_set_text_fmt(guider_ui.screen_label_10, "%ss", str_value);  
            lv_label_set_text_fmt(guider_ui.screen_1_btn_time3set_label, "%s", str_value);
            GrindSetData.time_3 = spinbox_value;               
        } else if (active_time_setting == 4){
            lv_label_set_text_fmt(guider_ui.screen_label_20, "%ss", str_value);  
            lv_label_set_text_fmt(guider_ui.screen_1_btn_time4set_label, "%s", str_value);
            GrindSetData.time_4 = spinbox_value;               
        } else if (active_time_setting == 5){ 
            lv_label_set_text_fmt(guider_ui.screen_1_btn_steamtempset_label, "%s", str_value);
            GrindSetData.temp_steam = spinbox_value;      
            volume = GrindSetData.temp_steam;
            GrindDataStr.data.cmd = CMDTYPE_SET_STEAMBLOCK;
        } else if (active_time_setting == 6){
            lv_label_set_text_fmt(guider_ui.screen_1_btn_coffeetempset_label, "%s", str_value);
            GrindSetData.temp_coffee = spinbox_value;
            volume = GrindSetData.temp_coffee;
            GrindDataStr.data.cmd = CMDTYPE_SET_COFFEEBLOCK;
        } 
        #if (LEFT_OR_COFFEE == RIGHT)
        else if (active_time_setting == 7){
            lv_label_set_text_fmt(guider_ui.screen_1_btn_hotwaterset_label, "%s", str_value);
            GrindSetData.time_hotwater = spinbox_value;
        }
        #endif
        else if (active_time_setting == 8){
            lv_label_set_text_fmt(guider_ui.screen_1_btn_brewblock_label, "%s", str_value);
            GrindSetData.temp_brew = spinbox_value;
            volume = GrindSetData.temp_brew;
            GrindDataStr.data.cmd = CMDTYPE_SET_BREWBLOCK;
        }
        flashDataSave();
        lv_obj_add_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN); 
        break;
    }
    default:
        break;
    }
}
static void screen_1_btn_hotwaterset_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒容器，获取热水秒数值
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.time_hotwater);

        active_time_setting = 7;        
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_brewblock_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //唤醒容器，获取冲煮头温度值
        lv_obj_clear_flag(guider_ui.screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_value(guider_ui.screen_1_spinbox_1, GrindSetData.temp_brew);

        active_time_setting = 8;   
        break;
    }
    default:
        break;
    }
}
void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1_btn_steamtempset, screen_1_btn_steamtempset_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_coffeetempset, screen_1_btn_coffeetempset_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_back, screen_1_btn_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_time1set, screen_1_btn_time1set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_time2set, screen_1_btn_time2set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_time3set, screen_1_btn_time3set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_time4set, screen_1_btn_time4set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_cancel, screen_1_btn_cancel_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_certain, screen_1_btn_certain_event_handler, LV_EVENT_ALL, ui);
    #if (LEFT_OR_COFFEE == RIGHT)
    lv_obj_add_event_cb(ui->screen_1_btn_hotwaterset, screen_1_btn_hotwaterset_event_handler, LV_EVENT_ALL, ui);
    #endif
    lv_obj_add_event_cb(ui->screen_1_btn_brewblock, screen_1_btn_brewblock_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}


static void SaveTeaParam(uint8_t index)
{
    lv_obj_t *ta[10] =
    {
        guider_ui.screen_ta_1stepon,
        guider_ui.screen_ta_1stepoff,
        guider_ui.screen_ta_2stepon,
        guider_ui.screen_ta_2stepoff,
        guider_ui.screen_ta_3,
        guider_ui.screen_ta_6,
        guider_ui.screen_ta_4,
        guider_ui.screen_ta_7,
        guider_ui.screen_ta_5,
        guider_ui.screen_ta_8,
    };

    for(int i = 0; i < 10; i++)
    {
        const char *txt = lv_textarea_get_text(ta[i]);

        GrindSetData.extract_time[index][i] = (uint8_t)atoi(txt);
    }
}

static void ShowTeaParam(uint8_t index)
{
    lv_obj_t *ta[10] =
    {
        guider_ui.screen_ta_1stepon,
        guider_ui.screen_ta_1stepoff,
        guider_ui.screen_ta_2stepon,
        guider_ui.screen_ta_2stepoff,
        guider_ui.screen_ta_3,
        guider_ui.screen_ta_6,
        guider_ui.screen_ta_4,
        guider_ui.screen_ta_7,
        guider_ui.screen_ta_5,
        guider_ui.screen_ta_8,
    };

    char buf[4];

    for(int i = 0; i < 10; i++)
    {
        sprintf(buf, "%d", GrindSetData.extract_time[index][i]);
        lv_textarea_set_text(ta[i], buf);
    }
}