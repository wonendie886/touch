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
static lv_obj_t* target_images[6];   // 直接开一个数组
static int target_images_count = 0;


void images_init(lv_ui *ui)
{
    /* Add your codes here */
    target_images[0] = guider_ui.screen_img_3;
    target_images[1] = guider_ui.screen_img_4;
    target_images[2] = guider_ui.screen_img_8;
    target_images[3] = guider_ui.screen_img_9;
    target_images[4] = guider_ui.screen_img_10;
    target_images[5] = guider_ui.screen_img_12;

    target_images_count = 6;
}
void set_image_opacity(lv_obj_t* target_img) 
{
    if (target_images == NULL) return;
    
    for (int i = 0; i < target_images_count; i++) {
        if (target_images[i] != NULL) {
            if (target_images[i] == target_img) {
                // 设置指定图片透明度为188
                lv_obj_set_style_img_opa(target_images[i], 100, LV_PART_MAIN | LV_STATE_DEFAULT);
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

/*
 * 显示或隐藏指定的控件集合
 * show: 1表示显示，0表示隐藏
 */
void show_hide_controls(lv_ui *ui, int show)
{
    lv_obj_t *controls[] = {
        ui->screen_spinbox_1,  // 微调器1
        ui->screen_btn_14,     // 按钮14
        ui->screen_btn_15 ,     // 按钮15
        ui->screen_spinbox_1_btn_plus, //微调器按钮
        ui->screen_spinbox_1_btn_minus, //微调器按钮
        ui->screen_cont_1,
    };
    
    int num_controls = sizeof(controls) / sizeof(controls[0]);
    
    for (int i = 0; i < num_controls; i++) {
        if (show) {
            lv_obj_clear_flag(controls[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(controls[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}
/*
 * 显示指定数量的按钮，其他按钮隐藏
 * ui: 界面对象
 * target_btn: 要显示的起始按钮
 * count: 要显示的按钮数量
 */
void show_multiple_buttons(lv_ui *ui, lv_obj_t *target_btn, int count)
{
    lv_obj_t *all_buttons[] = {
        ui->screen_btn_1,
        ui->screen_btn_2,
        ui->screen_btn_4,
        ui->screen_btn_5,
        ui->screen_btn_7,
        ui->screen_btn_11,
        ui->screen_btn_12,
        ui->screen_btn_13,
        ui->screen_btn_14,
        ui->screen_btn_15
    };
    
    int num_buttons = sizeof(all_buttons) / sizeof(all_buttons[0]);
    
    // 找到目标按钮的索引
    int target_index = -1;
    for (int i = 0; i < num_buttons; i++) {
        if (all_buttons[i] == target_btn) {
            target_index = i;
            break;
        }
    }
    
    // 如果未找到目标按钮，则默认从第一个按钮开始
    if (target_index == -1) {
        target_index = 0;
    }
    
    // 确保count不超过数组边界
    if (target_index + count > num_buttons) {
        count = num_buttons - target_index;
    }
    
    // 隐藏所有按钮
    for (int i = 0; i < num_buttons; i++) {
        lv_obj_add_flag(all_buttons[i], LV_OBJ_FLAG_HIDDEN);
    }
    
    // 显示指定数量的按钮
    for (int i = target_index; i < target_index + count; i++) {
        lv_obj_clear_flag(all_buttons[i], LV_OBJ_FLAG_HIDDEN);
    }
}

static void screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Currently highlighted, the rest are initialized.
        lv_obj_set_style_img_opa(guider_ui.screen_img_4,255,LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_3,100,LV_PART_MAIN | LV_STATE_DEFAULT);

        grinding_target = 1;
        // 通过Modbus发送数据
        if (isGrindMode == 0) {
            // 模式0: 发送文本1的数值数据
            Currenttargetime = GrindSetData.time_1;
            printf("Currenttime == %d\n",Currenttargetime);
            if (Currenttargetime > 0) {
                printf("发送的寄存器值: %d\n", Currenttargetime);
                int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                if(ret != 0){
                    printf("ret == %d\n",ret);
                }
            }
        } else {
            // 模式1: 发送文本4的数值数据
            Currenttargeweight = GrindSetData.weight_1;
            if (Currenttargeweight > 0) {
                printf("发送的寄存器值: %d\n", Currenttargeweight);
                int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight, 100);
                if (ret != 0){
                    printf("ret == %d\n",ret);
                }
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
        lv_obj_set_style_img_opa(guider_ui.screen_img_3,255,LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_4,100,LV_PART_MAIN | LV_STATE_DEFAULT);

        // 设置研磨目标为文本8
        grinding_target = 3;

        // 通过Modbus发送数据
        if (isGrindMode == 0) {
            // 模式0: 发送文本3的数值数据
            Currenttargetime = GrindSetData.time_3;
            if (Currenttargetime > 0) {
                printf("发送的寄存器值: %d\n", Currenttargetime);
                int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                if(ret != 0){
                    printf("ret == %d\n",ret);
                }
            }
        } else {
            // 模式1: 发送文本6的数值数据
            Currenttargeweight = GrindSetData.weight_3;
            if (Currenttargeweight > 0) {
                printf("发送的寄存器值: %d\n", Currenttargeweight);
                int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight, 100);
                if(ret != 0){
                    printf("ret == %d\n",ret);
                }
            }
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
        show_hide_controls(&guider_ui,1);

        show_multiple_buttons(&guider_ui,guider_ui.screen_btn_14,2);
        if (isGrindMode == 0) {
            // 获取当前标签1的值并设置到spinbox
            const char* current_text = lv_label_get_text(guider_ui.screen_label_1);
            printf("current_text = %s\n",current_text);
            if (current_text != NULL && strlen(current_text) > 0) {
                lv_textarea_set_text(guider_ui.screen_spinbox_1, current_text);
                float value = atof(current_text);
                printf("value == %f\n",value);
                lv_spinbox_set_value(guider_ui.screen_spinbox_1, (int32_t)(value * 10));
            } 
            else {
                lv_label_set_text(guider_ui.screen_label_1, "");
            }
        } else {
            // 获取当前标签4的值并设置到spinbox
            const char* current_text = lv_label_get_text(guider_ui.screen_label_4);
            if (current_text != NULL && strlen(current_text) > 0) {
                lv_textarea_set_text(guider_ui.screen_spinbox_1, current_text);
                float value = atof(current_text);
                lv_spinbox_set_value(guider_ui.screen_spinbox_1, (int32_t)(value * 10));
            } else {
                lv_label_set_text(guider_ui.screen_label_4, "");
            }
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
        show_hide_controls(&guider_ui,1);

        show_multiple_buttons(&guider_ui,guider_ui.screen_btn_14,2);

       if (isGrindMode == 0) {
            // 获取当前标签3的值并设置到spinbox
            const char* current_text = lv_label_get_text(guider_ui.screen_label_3);
            if (current_text != NULL && strlen(current_text) > 0) {
                lv_textarea_set_text(guider_ui.screen_spinbox_1, current_text);
                float value = atof(current_text);
                lv_spinbox_set_value(guider_ui.screen_spinbox_1, (int32_t)(value * 10)); 
            } else {
                lv_label_set_text(guider_ui.screen_label_3, "");
            }
        } else {
            // 获取当前标签6的值并设置到spinbox
            const char* current_text = lv_label_get_text(guider_ui.screen_label_6);
            if (current_text != NULL && strlen(current_text) > 0) {
                lv_textarea_set_text(guider_ui.screen_spinbox_1, current_text);
                float value = atof(current_text);
                lv_spinbox_set_value(guider_ui.screen_spinbox_1, (int32_t)(value * 10));
            } else {
                lv_label_set_text(guider_ui.screen_label_6, "");
            }
        }
        Textselectionflag = 3;
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

static void screen_btn_11_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_img_opa(guider_ui.screen_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_3, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
        uint16_t initialization_data[2] = {0};
        initialization_data[0] = GrindSetData.time_1;
        initialization_data[1] = GrindSetData.weight_1;
        int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_GRIND_TIME, 2, initialization_data, 200); 
        if(ret != 0){
            printf("ret == %d\n",ret);
        }  
        //Weighing mode
        lv_obj_set_style_img_opa(guider_ui.screen_img_9,255,LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_10,100,LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_8,100,LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_clear_flag(guider_ui.screen_label_4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_label_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_label_9, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_label_10, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_label_1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_11, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_12, LV_OBJ_FLAG_HIDDEN);



        isGrindMode = MODE_WEIGHT;
        uint16_t mode = 1;
        GrindSetData.grind_mode = MODE_WEIGHT;
        flashDataSave();
        printf("isGrindMode: %d\n", isGrindMode);

        lv_obj_add_flag(guider_ui.screen_btn_4, LV_OBJ_FLAG_HIDDEN);
        int retdata = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_MODE, mode, 100);
        if(retdata != 0){
            printf("retdata == %d\n",retdata);
        }
        break;
    }
    default:
        break;
    }
}
static void screen_btn_12_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        //Timing mode
        lv_obj_set_style_img_opa(guider_ui.screen_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_3, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
        
        uint16_t initialization_data[2] = {0};
        initialization_data[0] = GrindSetData.time_1;
        initialization_data[1] = GrindSetData.weight_1;
        int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_GRIND_TIME, 2, initialization_data, 200);    
        if(ret != 0){
            printf("ret == %d\n",ret);
        }

        lv_obj_set_style_img_opa(guider_ui.screen_img_10,255,LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_9,100,LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(guider_ui.screen_img_8,255,LV_PART_MAIN | LV_STATE_DEFAULT);

            // 显示标签123，隐藏标签456
        lv_obj_clear_flag(guider_ui.screen_label_1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_label_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_label_11, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_label_12, LV_OBJ_FLAG_HIDDEN);
        
        lv_obj_add_flag(guider_ui.screen_label_4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_9, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_label_10, LV_OBJ_FLAG_HIDDEN);


        isGrindMode = MODE_TIME;
        uint16_t mode = 0;
        GrindSetData.grind_mode = MODE_TIME;
        flashDataSave();
        printf("isGrindMode: %d\n", isGrindMode);

        lv_obj_clear_flag(guider_ui.screen_btn_4, LV_OBJ_FLAG_HIDDEN);
        int retdata = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_MODE, mode, 100);
        if (retdata != 0)
        {
            printf("retdata == %d\n",retdata);
        }
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
        lv_obj_set_style_img_opa(guider_ui.screen_img_12,255,LV_PART_MAIN | LV_STATE_DEFAULT);
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
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
        show_hide_controls(&guider_ui,0);

        //flash_store_read(&flash_write_data);
        //Synchronize the content of the input box with the text.
        if (Textselectionflag == 1){
            const char *txt = lv_textarea_get_text(guider_ui.screen_spinbox_1);
            char time1_str[50] = {0};
            if (isGrindMode == 0) {
                GrindSetData.time_1 = (uint32_t)(atof(txt) * 1000);
                sprintf(time1_str, "%.1f", (float)GrindSetData.time_1 / 1000.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_1, "%s", time1_str);
                // printf("write %d\n", GrindSetData.time_1);
                // strncpy(flash_write_data.label1_text, txt, MAX_TEXT_LEN);
                if(grinding_target == 1){
                    Currenttargetime = GrindSetData.time_1;
                    // printf("write %d\n", Currenttargetime);
                    int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                    if(ret != 0){
                        printf("ret == %d\n",ret);
                    }
                }
            } else { 
                GrindSetData.weight_1 = (uint32_t)(atof(txt) * 10);
                sprintf(time1_str, "%.1f", (float)GrindSetData.weight_1 / 10.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_4, "%s", time1_str);
                // printf("write %d\n", GrindSetData.weight_1);  
                if(grinding_target == 1){
                    Currenttargeweight = GrindSetData.weight_1;

                    // printf("write %d\n", Currenttargeweight);
                    int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight/100, 100);
                    if(ret != 0){
                        printf("ret == %d\n",ret);
                    }
                }
            }
        }
        if (Textselectionflag == 3){
            const char * txt = lv_textarea_get_text(guider_ui.screen_spinbox_1);
            char time2_str[50] = {0};
            //打印txt数据
            //printf("txt:%s\n", txt);
            if (isGrindMode == 0) {
                GrindSetData.time_3 = (uint32_t)(atof(txt) * 1000);
                sprintf(time2_str, "%.1f", (float)GrindSetData.time_3 / 1000.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_3, "%s", time2_str);
                // printf("write %d\n", GrindSetData.time_3);
                if(grinding_target == 3){
                    Currenttargetime = GrindSetData.time_3;
                    // printf("write %d\n", Currenttargetime);
                    int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, Currenttargetime, 100);
                    if(ret!= 0){
                        printf("ret == %d\n",ret);
                    }
                }   
            } else {
                // lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", txt);
                GrindSetData.weight_3 = (uint32_t)(atof(txt) * 10);
                sprintf(time2_str, "%.1f", (float)GrindSetData.weight_3 / 10.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", time2_str);
                // printf("write %d\n", GrindSetData.weight_3);
                if(grinding_target == 3){
                    Currenttargeweight = GrindSetData.weight_3;
                    // printf("write %d\n", Currenttargeweight);
                    int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight/100, 100);
                    if(ret != 0){
                        printf("ret == %d\n",ret);
                    }
                }
                //打印flash_write_data.label6_text
                //printf("flash_write_data.label6_text:%s\n", flash_write_data.label6_text);
            }
        }
        // 设置标志位，触发flash写入任务
        // flash_request_flag = 1;
        flashDataSave();
        Textselectionflag = 0;

        show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);
    
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
        show_hide_controls(&guider_ui,0);

        if (Textselectionflag == 1){
            if (isGrindMode == 0) {
                char string_data[50] = {0};  // 初始化为全0
                sprintf(string_data, "%.1f", (float)GrindSetData.time_1 / 1000.0f); 
                lv_label_set_text_fmt(guider_ui.screen_label_1, "%s", string_data);
            } else {
                char string_data[50] = {0};
                sprintf(string_data, "%.1f", (float)GrindSetData.weight_1 / 10.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_4, "%s", string_data);
 
            }
        }
        if (Textselectionflag == 3){
            if (isGrindMode == 0) {
                char string_data[50] = {0};
                sprintf(string_data, "%.1f", (float)GrindSetData.time_3 / 1000.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_3, "%s", string_data);
 
            } else {
                char string_data[50] = {0};
                sprintf(string_data, "%.1f", (float)GrindSetData.weight_3 / 10.0f);
                lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", string_data);
                //打印flash_write_data.label6_text
                //printf("flash_write_data.label6_text:%s\n", flash_write_data.label6_text);
            }
        }
        Textselectionflag = 0;

        show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);         
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
    lv_obj_add_event_cb(ui->screen_btn_5, screen_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_7, screen_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_4, screen_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_11, screen_btn_11_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_12, screen_btn_12_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_13, screen_btn_13_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_14, screen_btn_14_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_15, screen_btn_15_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:{
        //Send the thickness information to the lower-level machine.
        uint16_t motordrive_value = 0;  // 驱动与否
        int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        if(ret != 0)
        {
            printf("MBRTUMasterWriteSingleRegister error: %d\n", ret);
        }
        break;
    }
    case LV_EVENT_LONG_PRESSED:{
        // 长按发送1
        uint16_t motordrive_value[2] = {1,0};
        int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_STEP_ENABLE,2, motordrive_value, 100);
        if(ret != 0){
            printf("ret == %d\n",ret);
        }  
        break;
    }
    case LV_EVENT_RELEASED:{
        // 松开发送0
        uint16_t motordrive_value = 0;
        int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        if (ret != 0)
        {
            printf("MBRTUMasterWriteSingleRegister error: %d\n", ret);
        }
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
    case LV_EVENT_CLICKED:{
        //Send the thickness information to the lower-level machine.
        uint16_t motordrive_value = 0;  // 驱动与否
        int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        if(ret != 0){
            printf("MBRTUMasterWriteSingleRegister error: %d\n", ret);
        }
        break;
    }
    case LV_EVENT_LONG_PRESSED:{
        // 长按发送1
        uint16_t motordrive_value[2] = {1,1};
        int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_STEP_ENABLE,2, motordrive_value, 100);
        if(ret != 0){
            printf("ret == %d\n",ret);
        }
        break;
    }
    case LV_EVENT_RELEASED:{
        // 松开发送0
        uint16_t motordrive_value = 0;
        int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_STEP_ENABLE, motordrive_value, 100);
        if (ret != 0)
        {
            printf("MBRTUMasterWriteSingleRegister error: %d\n", ret);
        }
        break;
    }
    default:
        break;
    }
}
static void screen_1_btn_3_event_handler (lv_event_t *e)
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

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1_btn_1, screen_1_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_2, screen_1_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_btn_3, screen_1_btn_3_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
