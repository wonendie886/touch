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
#include "mbrtu_master.h"  // 添加Modbus RTU头文件
#include "modbus.h"
#include <string.h>
#include <stdlib.h>

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static int Textselectionflag = 0;
volatile int grinding_target = 0;
volatile uint16_t Currenttargetime = 0;
volatile uint16_t Currenttargeweight = 0;
volatile uint8_t start_flag = STATUS_IN_GRIND_STOP;

// 指定的图片对象数组
static lv_obj_t** target_images = NULL;
static int target_images_count = 0;


void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    // 初始化指定的图片对象数组
    static lv_obj_t* images[] = {
        guider_ui.screen_img_3,
        guider_ui.screen_img_4,
        guider_ui.screen_img_8,
        guider_ui.screen_img_9,
        guider_ui.screen_img_10,
        guider_ui.screen_img_12
    };
    
    target_images = images;
    target_images_count = sizeof(images) / sizeof(images[0]);
}

void set_image_opacity(lv_obj_t* target_img) 
{
    if (target_images == NULL) return;
    
    for (int i = 0; i < target_images_count; i++) {
        if (target_images[i] != NULL) {
            if (target_images[i] == target_img) {
                // 设置指定图片透明度为188
                lv_obj_set_style_img_opa(target_images[i], 188, LV_PART_MAIN | LV_STATE_DEFAULT);
            } else {
                // 设置其他图片透明度为255
                lv_obj_set_style_img_opa(target_images[i], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }
}

static uint16_t extract_value_from_label(lv_obj_t* label, char unit_suffix)
{
    const char *txt = lv_label_get_text(label);
    uint16_t result = 0;
    
    // 检查文本长度和单位后缀
    if (txt != NULL && strlen(txt) > 1 && txt[strlen(txt) - 1] == unit_suffix) {
        // 去掉单位后缀并转换为float
        char value_str[32];
        uint32_t len = strlen(txt) - 1;
        if (len >= sizeof(value_str)) {
            len = sizeof(value_str) - 1;
        }
        strncpy(value_str, txt, len);
        value_str[len] = '\0';
        
        // 转换为float并乘以1000转换为整数
        float value = atof(value_str);
        result = (uint16_t)(value * 1000);
        printf("提取的值: %d (原始值: %f)\n", result, value);
    }
    
    return result;
}

// 封装函数：传入当前按钮，让其他全部隐藏
void show_only_one_button(lv_obj_t * active_btn)
{
    lv_obj_t * btn_list[9] = { 
                                guider_ui.screen_btn_1, guider_ui.screen_btn_2, guider_ui.screen_btn_11, 
                                guider_ui.screen_btn_4, guider_ui.screen_btn_5, guider_ui.screen_btn_12, 
                                guider_ui.screen_btn_7, guider_ui.screen_btn_8, guider_ui.screen_btn_13, 
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
        set_image_opacity(guider_ui.screen_img_4);  
        // 设置研磨目标为文本7
        grinding_target = 1;

        // 通过Modbus发送数据
        if (isGrindMode == 0) {
            // 模式0: 发送文本1的数值数据
            Currenttargetime = extract_value_from_label(guider_ui.screen_label_1, 's');
            if (Currenttargetime > 0) {
                printf("发送的寄存器值: %d\n", Currenttargetime);
                MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
            }
        } else {
            // 模式1: 发送文本4的数值数据
            Currenttargeweight = extract_value_from_label(guider_ui.screen_label_4, 'g');
            if (Currenttargeweight > 0) {
                printf("发送的寄存器值: %d\n", Currenttargeweight);
                MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight/100, 100);
            }
        }         
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
        break;
    }
    default:
        break;
    }
}

static void screen_btn_13_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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
    lv_obj_add_event_cb(ui->screen_btn_4, screen_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_5, screen_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_7, screen_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_8, screen_btn_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_13, screen_btn_13_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //The motor runs in reverse.
        break;
    }
    default:
        break;
    }
}

static void screen_1_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //The motor is running in the forward direction.
        break;
    }
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1_btn_1, screen_1_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_2, screen_1_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
