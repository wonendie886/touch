/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "flash.h"


#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif
static int Textselectionflag = 0;
static int mode_flag = 0;  // 0表示显示标签123，1表示显示标签456


// 封装函数：传入当前按钮，让其他全部隐藏
void show_only_one_button(lv_obj_t * active_btn)
{
    lv_obj_t * btn_list[8] = { 
                                guider_ui.screen_btn_1, guider_ui.screen_btn_2, guider_ui.screen_btn_3, 
                                guider_ui.screen_btn_4, guider_ui.screen_btn_5, guider_ui.screen_btn_6,
                                guider_ui.screen_btn_7,guider_ui.screen_btn_8
                            };

    for(int i = 0; i < 8; i++) {
        if(btn_list[i] == active_btn) {
            // 显示当前按钮
            lv_obj_clear_flag(btn_list[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            // 隐藏其他按钮
            lv_obj_add_flag(btn_list[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

static void screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Currently highlighted, the rest are initialized.
        lv_obj_clear_flag(guider_ui.screen_img_6, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_img_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_7, LV_OBJ_FLAG_HIDDEN);        
        break;
    }
    default:
        break;
    }
}

static void screen_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Currently highlighted, the rest are initialized.
        lv_obj_clear_flag(guider_ui.screen_img_7, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_img_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_6, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Currently highlighted, the rest are initialized.
        lv_obj_clear_flag(guider_ui.screen_img_5, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_img_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_6, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Press the button to directly control the motor via Modbus protocol.
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
        lv_obj_clear_flag(guider_ui.screen_spinbox_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_plus,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_minus,LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(guider_ui.screen_btn_8, LV_OBJ_FLAG_HIDDEN);
        if (mode_flag == 0) {
            lv_label_set_text(guider_ui.screen_label_1, "");
        } else {
            lv_label_set_text(guider_ui.screen_label_4, "");
        }


        show_only_one_button(guider_ui.screen_btn_8);

        Textselectionflag = 1;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Press to open the input box
        lv_obj_clear_flag(guider_ui.screen_spinbox_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_plus,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_minus,LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(guider_ui.screen_btn_8, LV_OBJ_FLAG_HIDDEN);

        if (mode_flag == 0) {
            lv_label_set_text(guider_ui.screen_label_2, "");
        } else {
            lv_label_set_text(guider_ui.screen_label_5, "");
        }

        show_only_one_button(guider_ui.screen_btn_8);

        Textselectionflag = 2;
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
        lv_obj_clear_flag(guider_ui.screen_spinbox_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_plus,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_minus,LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(guider_ui.screen_btn_8, LV_OBJ_FLAG_HIDDEN);

        if (mode_flag == 0) {
            lv_label_set_text(guider_ui.screen_label_3, "");
        } else {
            lv_label_set_text(guider_ui.screen_label_6, "");
        }

        show_only_one_button(guider_ui.screen_btn_8);

        Textselectionflag = 3;
        break;
    }
    default:
        break;
    }
}

static void screen_btn_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Save the text content and activate the storage
        lv_obj_add_flag(guider_ui.screen_spinbox_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_btn_8, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_spinbox_2_btn_plus,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_spinbox_2_btn_minus,LV_OBJ_FLAG_HIDDEN);

        //flash_store_t store;
        //flash_store_read(&store);
        //Synchronize the content of the input box with the text.
        if (Textselectionflag == 1){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_2);

            if (mode_flag == 0) {
                lv_label_set_text_fmt(guider_ui.screen_label_1, "%ss", txt);
                strncpy(flash_write_data.label1_text, txt, MAX_TEXT_LEN);
            } else {
                lv_label_set_text_fmt(guider_ui.screen_label_4, "%sg", txt);
                strncpy(flash_write_data.label4_text, txt, MAX_TEXT_LEN);
            }
        }
        if (Textselectionflag == 2){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_2);

            if (mode_flag == 0) {
                lv_label_set_text_fmt(guider_ui.screen_label_2, "%ss", txt);
                strncpy(flash_write_data.label2_text, txt, MAX_TEXT_LEN);
            } else {
                lv_label_set_text_fmt(guider_ui.screen_label_5, "%sg", txt);
                strncpy(flash_write_data.label5_text, txt, MAX_TEXT_LEN);
            }
        }
        if (Textselectionflag == 3){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_2);

            if (mode_flag == 0) {
                lv_label_set_text_fmt(guider_ui.screen_label_3, "%ss", txt);
                strncpy(flash_write_data.label3_text, txt, MAX_TEXT_LEN);
            } else {
                lv_label_set_text_fmt(guider_ui.screen_label_6, "%sg", txt);
                strncpy(flash_write_data.label6_text, txt, MAX_TEXT_LEN);
            }
        }
        // 设置标志位，触发flash写入任务
        flash_request_flag = 1;

        Textselectionflag = 0;

        lv_obj_t * btn_list[7] = { 
                                guider_ui.screen_btn_1, guider_ui.screen_btn_2, guider_ui.screen_btn_3, 
                                guider_ui.screen_btn_4, guider_ui.screen_btn_5, guider_ui.screen_btn_6,
                                guider_ui.screen_btn_7};

        for (int i = 0; i < 7; i++){
            lv_obj_clear_flag(btn_list[i], LV_OBJ_FLAG_HIDDEN);
        }      
        break;
    }
    default:
    break;
    }
}

static void screen_btn_9_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:{
        //switching mode
        mode_flag = !mode_flag;  // 切换模式
        
        if (mode_flag == 1) {
            // 显示标签456，隐藏标签123
            lv_obj_clear_flag(guider_ui.screen_label_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_5, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_6, LV_OBJ_FLAG_HIDDEN);
            
            lv_obj_add_flag(guider_ui.screen_label_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
        } else {
            // 显示标签123，隐藏标签456
            lv_obj_clear_flag(guider_ui.screen_label_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
            
            lv_obj_add_flag(guider_ui.screen_label_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_5, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_6, LV_OBJ_FLAG_HIDDEN);
        }
        break;
    }
    default:
    break;
    }    
}
void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_btn_1, screen_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_2, screen_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_3, screen_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_4, screen_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_5, screen_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_6, screen_btn_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_7, screen_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_8, screen_btn_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_9, screen_btn_9_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}

