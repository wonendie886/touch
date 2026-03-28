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


static void screen_btn_steam3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        volume = GrindSetData.weight_3;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
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
        volume = GrindSetData.weight_1;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        break;
    }
    default:
        break;
    }
}

uint8_t steamEnable = 0;
static void screen_btn_rinse_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        if(steamEnable) {
            steamEnable = 0;
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftSteam(0,volume);
            #else
                canSendRightSteam(0,volume);
            #endif
            // lv_label_set_text(guider_ui.screen_label_temp, temp_str);
            lv_label_set_text(guider_ui.screen_btn_rinse_label, "Steam");
        } else {
            volume = 30;
            GrindDataStr.data.cmd = CMDTYPE_MAKE_STEAM;
            steamEnable = 1;
            lv_label_set_text(guider_ui.screen_btn_rinse_label, "Cancel");
        }
        
        break;
    }
    default:
        break;
    }
}

static void screen_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Press to open the input box
        // show_hide_controls(&guider_ui,1);
        lv_obj_clear_flag(guider_ui.screen_cont_1, LV_OBJ_FLAG_HIDDEN);
        // show_multiple_buttons(&guider_ui,guider_ui.screen_btn_14,2);
            // 获取当前标签4的值并设置到spinbox
        const char* current_text = lv_label_get_text(guider_ui.screen_label_4);
        if (current_text != NULL && strlen(current_text) > 0) {
            lv_textarea_set_text(guider_ui.screen_spinbox_1, current_text);
            float value = atof(current_text);
            lv_spinbox_set_value(guider_ui.screen_spinbox_1, (int32_t)(value));
        } else {
            lv_label_set_text(guider_ui.screen_label_4, "");
        }
        Textselectionflag = 1;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Press to open the input box
        // show_hide_controls(&guider_ui,1);
        lv_obj_clear_flag(guider_ui.screen_cont_1, LV_OBJ_FLAG_HIDDEN);
        // show_multiple_buttons(&guider_ui,guider_ui.screen_btn_14,2);
        // 获取当前标签6的值并设置到spinbox
        const char* current_text = lv_label_get_text(guider_ui.screen_label_6);
        if (current_text != NULL && strlen(current_text) > 0) {
            lv_textarea_set_text(guider_ui.screen_spinbox_1, current_text);
            float value = atof(current_text);
            lv_spinbox_set_value(guider_ui.screen_spinbox_1, (int32_t)(value));
        } else {
            lv_label_set_text(guider_ui.screen_label_6, "");
        }
        Textselectionflag = 3;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_14_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Save the text content and activate the storage
        lv_obj_add_flag(guider_ui.screen_cont_1, LV_OBJ_FLAG_HIDDEN);

        //flash_store_read(&flash_write_data);
        //Synchronize the content of the input box with the text.
        if (Textselectionflag == 1){
            const char *txt = lv_textarea_get_text(guider_ui.screen_spinbox_1);
            char time1_str[50] = {0};
                GrindSetData.weight_1 = (uint32_t)(atof(txt));
                sprintf(time1_str, "%.1f", (float)GrindSetData.weight_1);
                lv_label_set_text_fmt(guider_ui.screen_label_4, "%s", time1_str);
                // printf("write %d\n", GrindSetData.weight_1);  
                // if(grinding_target == 1){
                //     Currenttargeweight = GrindSetData.weight_1;
                // }
        }
        if (Textselectionflag == 3){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_1);
            char time2_str[50] = {0};
            //打印txt数据
            printf("txt:%s\n", txt);

                // lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", txt);
            GrindSetData.weight_3 = (uint32_t)(atof(txt));
            sprintf(time2_str, "%.1f", (float)GrindSetData.weight_3);
            lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", time2_str);
            printf("write %d\n", GrindSetData.weight_3);
                // if(grinding_target == 3){
                //     Currenttargeweight = GrindSetData.weight_3;
                    // printf("write %d\n", Currenttargeweight);
                // }
                //打印flash_write_data.label6_text
                //printf("flash_write_data.label6_text:%s\n", flash_write_data.label6_text);
        }
        // 设置标志位，触发flash写入任务
        // flash_request_flag = 1;
        // flashDataSave();
        Textselectionflag = 0;

        // show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);
    
        break;
    }
    default:
        break;
    }
}

static void screen_btn_15_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        // Cancel text restoration, button restore.
        lv_obj_add_flag(guider_ui.screen_cont_1, LV_OBJ_FLAG_HIDDEN);

        if (Textselectionflag == 1){
            char string_data[50] = {0};
            sprintf(string_data, "%.1f", (float)GrindSetData.weight_1 );
            lv_label_set_text_fmt(guider_ui.screen_label_4, "%s", string_data);
        }
        if (Textselectionflag == 3){
            char string_data[50] = {0};
            sprintf(string_data, "%.1f", (float)GrindSetData.weight_3);
            lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", string_data);
            //打印flash_write_data.label6_text
            //printf("flash_write_data.label6_text:%s\n", flash_write_data.label6_text)
        }
        Textselectionflag = 0;

        // show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);         
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_btn_cancel, screen_btn_cancel_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam3, screen_btn_steam3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam2, screen_btn_steam2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_rinse, screen_btn_rinse_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_5, screen_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_7, screen_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_14, screen_btn_14_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_15, screen_btn_15_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
