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

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

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

static void screen_btn_steam4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        volume = 60;
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
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        volume = 45;
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
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        volume = 30;
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
        GrindDataStr.data.cmd = CMDTYPE_BEVERAGEMAKE_CHANNELB;
        volume = 1;
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
}


void events_init(lv_ui *ui)
{

}
