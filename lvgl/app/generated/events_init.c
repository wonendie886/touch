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

/**
 * 从标签提取数值并转换为Modbus寄存器格式
 * @param label 要读取的标签对象
 * @param unit_suffix 期望的单位后缀 ('s' 或 'g')
 * @return 转换后的16位整数值
 */
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
        lv_obj_clear_flag(guider_ui.screen_img_7, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_img_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_img_6, LV_OBJ_FLAG_HIDDEN);
        // 设置研磨目标为文本8
        grinding_target = 3;

        // 通过Modbus发送数据
        if (isGrindMode == 0) {
            // 模式0: 发送文本3的数值数据
            Currenttargetime = extract_value_from_label(guider_ui.screen_label_3, 's');
            if (Currenttargetime > 0) {
                printf("发送的寄存器值: %d\n", Currenttargetime);
                MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
            }
        } else {
            // 模式1: 发送文本6的数值数据
            Currenttargeweight = extract_value_from_label(guider_ui.screen_label_6, 'g');
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

        // 设置研磨目标为文本9
        grinding_target = 2;

        // 通过Modbus发送数据
        if (isGrindMode == 0) {
            // 模式0: 发送文本2的数值数据
            Currenttargetime = extract_value_from_label(guider_ui.screen_label_2, 's');
            if (Currenttargetime > 0) {
                printf("发送的寄存器值: %d\n", Currenttargetime);
                MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
            }
        } else {
            // 模式1: 发送文本5的数值数据
            Currenttargeweight = extract_value_from_label(guider_ui.screen_label_5, 'g');
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

static void screen_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Press the button to directly control the motor via Modbus protocol.
        // 发送启动标志位到下位机
        // 使用保持寄存器地址0x0006，发送值1表示启动，0表示停止

        if(start_flag == STATUS_IN_GRIND_STOP){
            start_flag = STATUS_IN_GRIND_START;
            
            
        } else {
            start_flag = STATUS_IN_GRIND_STOP;

            
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
        lv_obj_clear_flag(guider_ui.screen_spinbox_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_plus,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_spinbox_2_btn_minus,LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(guider_ui.screen_btn_8, LV_OBJ_FLAG_HIDDEN);
        if (isGrindMode == 0) {
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

        if (isGrindMode == 0) {
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

        if (isGrindMode == 0) {
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

        flash_store_read(&flash_write_data);
        //Synchronize the content of the input box with the text.
        if (Textselectionflag == 1){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_2);

            if (isGrindMode == 0) {
                lv_label_set_text_fmt(guider_ui.screen_label_1, "%ss", txt);
                strncpy(flash_write_data.label1_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 1){
                    Currenttargetime = extract_value_from_label(guider_ui.screen_label_1, 's');
                    printf("write %d\n", Currenttargetime);
                    MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                }
            } else {
                lv_label_set_text_fmt(guider_ui.screen_label_4, "%sg", txt);
                strncpy(flash_write_data.label4_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 1){
                    Currenttargeweight = extract_value_from_label(guider_ui.screen_label_4, 'g');
                    MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight/100, 100);
                }
            }
        }
        if (Textselectionflag == 2){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_2);

            if (isGrindMode == 0) {
                lv_label_set_text_fmt(guider_ui.screen_label_2, "%ss", txt);
                strncpy(flash_write_data.label2_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 3){
                    Currenttargetime = extract_value_from_label(guider_ui.screen_label_2, 's');
                    MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                }                
            } else {
                lv_label_set_text_fmt(guider_ui.screen_label_5, "%sg", txt);
                strncpy(flash_write_data.label5_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 3){
                    Currenttargeweight = extract_value_from_label(guider_ui.screen_label_5, 'g');
                    MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight/100, 100);
                }
            }
        }
        if (Textselectionflag == 3){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_2);
            //打印txt数据
            //printf("txt:%s\n", txt);
            if (isGrindMode == 0) {
                lv_label_set_text_fmt(guider_ui.screen_label_3, "%ss", txt);
                strncpy(flash_write_data.label3_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 2){
                    Currenttargetime = extract_value_from_label(guider_ui.screen_label_3, 's');
                    MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                }   
            } else {
                lv_label_set_text_fmt(guider_ui.screen_label_6, "%sg", txt);
                strncpy(flash_write_data.label6_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 2){
                    Currenttargeweight = extract_value_from_label(guider_ui.screen_label_6, 'g');
                    MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight/100, 100);
                }
                //打印flash_write_data.label6_text
                //printf("flash_write_data.label6_text:%s\n", flash_write_data.label6_text);
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

        
        if (isGrindMode == MODE_TIME) {
            // 显示标签456，隐藏标签123
            lv_obj_clear_flag(guider_ui.screen_label_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_5, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_6, LV_OBJ_FLAG_HIDDEN);
            
            lv_obj_add_flag(guider_ui.screen_label_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);

            isGrindMode = MODE_WEIGHT;
            printf("isGrindMode: %d\n", isGrindMode);

            lv_obj_add_flag(guider_ui.screen_btn_4, LV_OBJ_FLAG_HIDDEN);
        } else {
            // 显示标签123，隐藏标签456
            lv_obj_clear_flag(guider_ui.screen_label_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
            
            lv_obj_add_flag(guider_ui.screen_label_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_5, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_label_6, LV_OBJ_FLAG_HIDDEN);

            isGrindMode = MODE_TIME;
            printf("isGrindMode: %d\n", isGrindMode);

            lv_obj_clear_flag(guider_ui.screen_btn_4, LV_OBJ_FLAG_HIDDEN);
        }
        // 通过Modbus发送当前模式信息到从机
        uint16_t mode_value = isGrindMode;
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_MODE, mode_value, 100);

        break;
    }
    default:
    break;
    }    
}

static void screen_btn_10_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:{
        //Send the thickness information to the lower-level machine.
        uint16_t motordrive_value = 0;  // 驱动与否
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        break;
    }
    case LV_EVENT_LONG_PRESSED:{
        // 长按发送1
        uint16_t motordrive_value = 1;
        uint16_t direction = 0;
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_DIR, direction, 100);
        break;
    }
    case LV_EVENT_RELEASED:{
        // 松开发送0
        uint16_t motordrive_value = 0;
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        break;
    }
    default:
    break;
    }    
}

static void screen_btn_11_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:{
        //Send the thickness information to the lower-level machine.
        uint16_t motordrive_value = 0;  // 驱动与否
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        break;
    }
    case LV_EVENT_LONG_PRESSED:{
        // 长按发送1
        uint16_t motordrive_value = 1;
        uint16_t direction = 1;
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_DIR, direction, 100);
        break;
    }
    case LV_EVENT_RELEASED:{
        // 松开发送0
        uint16_t motordrive_value = 0;
        MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
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
    lv_obj_add_event_cb(ui->screen_btn_10, screen_btn_10_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_11, screen_btn_11_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}

