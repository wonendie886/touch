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


static void screen_btn_coffee1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //coffee1做咖啡
        volume = 20;
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
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
        volume = 40;
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
        volume = 30;
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
        volume = 50;
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

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_btn_coffee1, screen_btn_coffee1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_coffee3, screen_btn_coffee3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_coffee2, screen_btn_coffee2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_coffee4, screen_btn_coffee4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_steam, screen_btn_steam_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_rinse, screen_btn_rinse_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_cancel, screen_btn_cancel_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
