/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "flash.h"

extern const char version[12];  /* main.c 中的版本字符串 */



void setup_scr_screen_1(lv_ui *ui)
{
    //Write codes screen_1
    ui->screen_1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_1, 480, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //手动修改：左侧标题栏
    ui->screen_1_nav_cont = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_nav_cont, 0, 0);
    lv_obj_set_size(ui->screen_1_nav_cont, 120, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_nav_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->screen_1_nav_cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for screen_1_nav_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_nav_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_nav_cont, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_nav_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_nav_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_nav_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_1_nav_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_nav_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_nav_btn_1（标题1：统计）
    ui->screen_1_nav_btn_1 = lv_btn_create(ui->screen_1_nav_cont);
    ui->screen_1_nav_btn_1_label = lv_label_create(ui->screen_1_nav_btn_1);
    lv_label_set_text(ui->screen_1_nav_btn_1_label, "Statistics");
    lv_label_set_long_mode(ui->screen_1_nav_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_nav_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_nav_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_nav_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_nav_btn_1, 0, 20);
    lv_obj_set_size(ui->screen_1_nav_btn_1, 120, 50);

    //Write style for screen_1_nav_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_nav_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_nav_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_nav_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_nav_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_nav_btn_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_nav_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_nav_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_nav_btn_1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_nav_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_nav_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_nav_btn_2（标题2：版本）
    ui->screen_1_nav_btn_2 = lv_btn_create(ui->screen_1_nav_cont);
    ui->screen_1_nav_btn_2_label = lv_label_create(ui->screen_1_nav_btn_2);
    lv_label_set_text(ui->screen_1_nav_btn_2_label, "Version");
    lv_label_set_long_mode(ui->screen_1_nav_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_nav_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_nav_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_nav_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_nav_btn_2, 0, 90);
    lv_obj_set_size(ui->screen_1_nav_btn_2, 120, 50);

    //Write style for screen_1_nav_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_nav_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_nav_btn_2, lv_color_hex(0x5b514b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_nav_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_nav_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_nav_btn_2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_nav_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_nav_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_nav_btn_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_nav_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_nav_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //手动修改：右侧内容区
    ui->screen_1_content_cont = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_content_cont, 120, 0);
    lv_obj_set_size(ui->screen_1_content_cont, 360, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_content_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->screen_1_content_cont, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for screen_1_content_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_content_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_content_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_content_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_content_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_content_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_1_content_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_content_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //手动修改：Statistics 面板（默认显示）
    ui->screen_1_panel_stats = lv_obj_create(ui->screen_1_content_cont);
    lv_obj_set_pos(ui->screen_1_panel_stats, 0, 0);
    lv_obj_set_size(ui->screen_1_panel_stats, 360, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_panel_stats, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->screen_1_panel_stats, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for screen_1_panel_stats, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_panel_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_panel_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_panel_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_1_panel_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_panel_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->screen_1_label_stats_title = lv_label_create(ui->screen_1_panel_stats);
    lv_label_set_text(ui->screen_1_label_stats_title, "Statistics");
    lv_label_set_long_mode(ui->screen_1_label_stats_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_stats_title, 0, 15);
    lv_obj_set_size(ui->screen_1_label_stats_title, 360, 30);
    lv_obj_set_style_text_color(ui->screen_1_label_stats_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_stats_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_stats_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_stats_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //读取 Flash 中真实杯数（设置区基准 + 计数页事件）
    uint32_t flash_single_cups = 0;
    uint32_t flash_double_cups = 0;
    cupCounterReadFromFlash(&flash_single_cups, &flash_double_cups);
    uint32_t flash_total_cups = flash_single_cups + flash_double_cups;

    //单杯统计
    {
        char stats_buf[32];
        ui->screen_1_label_stats_single = lv_label_create(ui->screen_1_panel_stats);
        sprintf(stats_buf, "Single cups: %lu", (unsigned long)flash_single_cups);
        lv_label_set_text(ui->screen_1_label_stats_single, stats_buf);
        lv_label_set_long_mode(ui->screen_1_label_stats_single, LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(ui->screen_1_label_stats_single, 20, 70);
        lv_obj_set_size(ui->screen_1_label_stats_single, 300, 30);
        lv_obj_set_style_text_color(ui->screen_1_label_stats_single, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui->screen_1_label_stats_single, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui->screen_1_label_stats_single, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

    //双杯统计
    {
        char stats_buf[32];
        ui->screen_1_label_stats_double = lv_label_create(ui->screen_1_panel_stats);
        sprintf(stats_buf, "Double cups: %lu", (unsigned long)flash_double_cups);
        lv_label_set_text(ui->screen_1_label_stats_double, stats_buf);
        lv_label_set_long_mode(ui->screen_1_label_stats_double, LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(ui->screen_1_label_stats_double, 20, 110);
        lv_obj_set_size(ui->screen_1_label_stats_double, 300, 30);
        lv_obj_set_style_text_color(ui->screen_1_label_stats_double, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui->screen_1_label_stats_double, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui->screen_1_label_stats_double, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

    //总计（放最下面）
    {
        char stats_buf[32];
        ui->screen_1_label_stats_total = lv_label_create(ui->screen_1_panel_stats);
        sprintf(stats_buf, "Total cups: %lu", (unsigned long)flash_total_cups);
        lv_label_set_text(ui->screen_1_label_stats_total, stats_buf);
        lv_label_set_long_mode(ui->screen_1_label_stats_total, LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(ui->screen_1_label_stats_total, 20, 150);
        lv_obj_set_size(ui->screen_1_label_stats_total, 300, 30);
        lv_obj_set_style_text_color(ui->screen_1_label_stats_total, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui->screen_1_label_stats_total, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui->screen_1_label_stats_total, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

    //手动修改：Version 面板（默认隐藏）
    ui->screen_1_panel_version = lv_obj_create(ui->screen_1_content_cont);
    lv_obj_set_pos(ui->screen_1_panel_version, 0, 0);
    lv_obj_set_size(ui->screen_1_panel_version, 360, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_panel_version, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->screen_1_panel_version, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui->screen_1_panel_version, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_panel_version, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_panel_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_panel_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_panel_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_1_panel_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_panel_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->screen_1_label_version_title = lv_label_create(ui->screen_1_panel_version);
    lv_label_set_text(ui->screen_1_label_version_title, "Version");
    lv_label_set_long_mode(ui->screen_1_label_version_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_version_title, 0, 15);
    lv_obj_set_size(ui->screen_1_label_version_title, 360, 30);
    lv_obj_set_style_text_color(ui->screen_1_label_version_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_version_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_version_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_version_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->screen_1_label_version_value = lv_label_create(ui->screen_1_panel_version);
    lv_label_set_text(ui->screen_1_label_version_value, version);
    lv_label_set_long_mode(ui->screen_1_label_version_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_version_value, 20, 60);
    lv_obj_set_size(ui->screen_1_label_version_value, 200, 30);
    lv_obj_set_style_text_color(ui->screen_1_label_version_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_version_value, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_version_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_3（返回按钮：页面右上角）
    ui->screen_1_btn_3 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_3_label = lv_label_create(ui->screen_1_btn_3);
    lv_label_set_text(ui->screen_1_btn_3_label, "Back");
    lv_label_set_long_mode(ui->screen_1_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_3, 265, 228);
    lv_obj_set_size(ui->screen_1_btn_3, 70, 34);

    //Write style for screen_1_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_3, lv_color_hex(0x5b514b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_1.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

    //Init events for screen.
    events_init_screen_1(ui);
}
