/*
* Copyright 2026 NXP
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
#include "protocol.h"
extern struct GrindRealData GrindDataStr;


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

    //Write codes screen_1_btn_back
    ui->screen_1_btn_back = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_back_label = lv_label_create(ui->screen_1_btn_back);
    lv_label_set_text(ui->screen_1_btn_back_label, "返回");
    lv_label_set_long_mode(ui->screen_1_btn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_back, 400, 220);
    lv_obj_set_size(ui->screen_1_btn_back, 80, 50);

    //Write style for screen_1_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_back, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_menu
    ui->screen_1_menu = lv_tabview_create(ui->screen_1, LV_DIR_LEFT, 100);
    lv_obj_set_pos(ui->screen_1_menu, 0, 0);
    lv_obj_set_size(ui->screen_1_menu, 400, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_menu, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_menu, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_menu, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_menu, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_menu, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_menu, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_menu, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_menu_extra_btnm_main_default
    static lv_style_t style_screen_1_menu_extra_btnm_main_default;
    ui_init_style(&style_screen_1_menu_extra_btnm_main_default);

    lv_style_set_border_width(&style_screen_1_menu_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_screen_1_menu_extra_btnm_main_default, 0);
    lv_style_set_bg_opa(&style_screen_1_menu_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_menu_extra_btnm_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_1_menu_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_1_menu), &style_screen_1_menu_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_menu_extra_btnm_items_default
    static lv_style_t style_screen_1_menu_extra_btnm_items_default;
    ui_init_style(&style_screen_1_menu_extra_btnm_items_default);

    lv_style_set_text_color(&style_screen_1_menu_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_screen_1_menu_extra_btnm_items_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_menu_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_1_menu), &style_screen_1_menu_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_1_menu_extra_btnm_items_checked
    static lv_style_t style_screen_1_menu_extra_btnm_items_checked;
    ui_init_style(&style_screen_1_menu_extra_btnm_items_checked);

    lv_style_set_text_color(&style_screen_1_menu_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_text_font(&style_screen_1_menu_extra_btnm_items_checked, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_menu_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_screen_1_menu_extra_btnm_items_checked, 4);
    lv_style_set_border_opa(&style_screen_1_menu_extra_btnm_items_checked, 255);
    lv_style_set_border_color(&style_screen_1_menu_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_border_side(&style_screen_1_menu_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_screen_1_menu_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_screen_1_menu_extra_btnm_items_checked, 60);
    lv_style_set_bg_color(&style_screen_1_menu_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_1_menu_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_1_menu), &style_screen_1_menu_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes set
    ui->screen_1_menu_tab_1 = lv_tabview_add_tab(ui->screen_1_menu,"set");
    lv_obj_t * screen_1_menu_tab_1_label = lv_label_create(ui->screen_1_menu_tab_1);
    lv_label_set_text(screen_1_menu_tab_1_label, "");

    //Write codes screen_1_label_boilertemp
    ui->screen_1_label_boilertemp = lv_label_create(ui->screen_1_menu_tab_1);
    lv_label_set_text(ui->screen_1_label_boilertemp, "蒸汽锅炉温度");
    lv_label_set_long_mode(ui->screen_1_label_boilertemp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_boilertemp, 0, 20);
    lv_obj_set_size(ui->screen_1_label_boilertemp, 100, 32);

    //Write style for screen_1_label_boilertemp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_boilertemp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_boilertemp, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_boilertemp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_boilertemp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_boilertemp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_label_boilertemp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_label_boilertemp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_boilertemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_set
    ui->screen_1_label_set = lv_label_create(ui->screen_1_menu_tab_1);
    lv_label_set_text(ui->screen_1_label_set, "");
    lv_label_set_long_mode(ui->screen_1_label_set, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_set, 130, 14);
    lv_obj_set_size(ui->screen_1_label_set, 100, 32);

    //Write style for screen_1_label_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_label_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_label_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_label_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_set, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_set
    ui->screen_1_btn_set = lv_btn_create(ui->screen_1_menu_tab_1);
    ui->screen_1_btn_set_label = lv_label_create(ui->screen_1_btn_set);
    lv_label_set_text(ui->screen_1_btn_set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_set, 130, 14);
    lv_obj_set_size(ui->screen_1_btn_set, 100, 32);

    //Write style for screen_1_btn_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_set, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_settime1
    ui->screen_1_btn_settime1 = lv_btn_create(ui->screen_1_menu_tab_1);
    ui->screen_1_btn_settime1_label = lv_label_create(ui->screen_1_btn_settime1);
    lv_label_set_text(ui->screen_1_btn_settime1_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_settime1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_settime1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_settime1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_settime1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_settime1, 130, 65);
    lv_obj_set_size(ui->screen_1_btn_settime1, 100, 32);

    //Write style for screen_1_btn_settime1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_settime1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_settime1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_settime1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_settime1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_settime1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_settime1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_settime1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_settime1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_settime1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_settime1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_settime1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_settime2
    ui->screen_1_btn_settime2 = lv_btn_create(ui->screen_1_menu_tab_1);
    ui->screen_1_btn_settime2_label = lv_label_create(ui->screen_1_btn_settime2);
    lv_label_set_text(ui->screen_1_btn_settime2_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_settime2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_settime2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_settime2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_settime2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_settime2, 130, 120);
    lv_obj_set_size(ui->screen_1_btn_settime2, 100, 32);

    //Write style for screen_1_btn_settime2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_settime2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_settime2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_settime2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_settime2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_settime2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_settime2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_settime2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_settime2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_settime2, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_settime2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_settime2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_settime3
    ui->screen_1_btn_settime3 = lv_btn_create(ui->screen_1_menu_tab_1);
    ui->screen_1_btn_settime3_label = lv_label_create(ui->screen_1_btn_settime3);
    lv_label_set_text(ui->screen_1_btn_settime3_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_settime3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_settime3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_settime3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_settime3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_settime3, 130, 179);
    lv_obj_set_size(ui->screen_1_btn_settime3, 100, 32);

    //Write style for screen_1_btn_settime3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_settime3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_settime3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_settime3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_settime3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_settime3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_settime3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_settime3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_settime3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_settime3, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_settime3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_settime3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time1
    ui->screen_1_label_time1 = lv_label_create(ui->screen_1_menu_tab_1);
    lv_label_set_text(ui->screen_1_label_time1, "时间1");
    lv_label_set_long_mode(ui->screen_1_label_time1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time1, 1, 75);
    lv_obj_set_size(ui->screen_1_label_time1, 100, 32);

    //Write style for screen_1_label_time1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time2
    ui->screen_1_label_time2 = lv_label_create(ui->screen_1_menu_tab_1);
    lv_label_set_text(ui->screen_1_label_time2, "时间2");
    lv_label_set_long_mode(ui->screen_1_label_time2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time2, 3, 127);
    lv_obj_set_size(ui->screen_1_label_time2, 100, 32);

    //Write style for screen_1_label_time2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time3
    ui->screen_1_label_time3 = lv_label_create(ui->screen_1_menu_tab_1);
    lv_label_set_text(ui->screen_1_label_time3, "时间3");
    lv_label_set_long_mode(ui->screen_1_label_time3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time3, 3, 184);
    lv_obj_set_size(ui->screen_1_label_time3, 100, 32);

    //Write style for screen_1_label_time3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time3, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_cont_set
    ui->screen_1_cont_set = lv_obj_create(ui->screen_1_menu_tab_1);
    lv_obj_set_pos(ui->screen_1_cont_set, -13, 78);
    lv_obj_set_size(ui->screen_1_cont_set, 276, 50);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_set, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_cont_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_cont_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_cont_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_cont_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_cont_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_cont_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cont_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cont_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_spinbox_set
    ui->screen_1_spinbox_set = lv_spinbox_create(ui->screen_1_cont_set);
    lv_obj_set_pos(ui->screen_1_spinbox_set, 105, 4);
    lv_obj_set_width(ui->screen_1_spinbox_set, 62);
    lv_obj_set_height(ui->screen_1_spinbox_set, 37);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_set, 3, 3);
    lv_spinbox_set_range(ui->screen_1_spinbox_set, 0, 130);
    lv_coord_t screen_1_spinbox_set_h = lv_obj_get_height(ui->screen_1_spinbox_set);
    ui->screen_1_spinbox_set_btn_plus = lv_btn_create(ui->screen_1_cont_set);
    lv_obj_set_size(ui->screen_1_spinbox_set_btn_plus, screen_1_spinbox_set_h, screen_1_spinbox_set_h);
    lv_obj_align_to(ui->screen_1_spinbox_set_btn_plus, ui->screen_1_spinbox_set, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_set_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_set_btn_plus, lv_screen_1_spinbox_set_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_set_btn_minus = lv_btn_create(ui->screen_1_cont_set);
    lv_obj_set_size(ui->screen_1_spinbox_set_btn_minus, screen_1_spinbox_set_h, screen_1_spinbox_set_h);
    lv_obj_align_to(ui->screen_1_spinbox_set_btn_minus, ui->screen_1_spinbox_set, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_set_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_set_btn_minus, lv_screen_1_spinbox_set_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_set, 105, 4);

    //Write style for screen_1_spinbox_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_set, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_set, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_set, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_set, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_set, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_set, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_set, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_set, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_set, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_set, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_set, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_set, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_set, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_set_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_set_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_set_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_set_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_set_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_set_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_set_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_set_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_set_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_set_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_set_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_set_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_set_btn_plus, &style_screen_1_spinbox_set_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_set_btn_minus, &style_screen_1_spinbox_set_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_certain
    ui->screen_1_btn_certain = lv_btn_create(ui->screen_1_cont_set);
    ui->screen_1_btn_certain_label = lv_label_create(ui->screen_1_btn_certain);
    lv_label_set_text(ui->screen_1_btn_certain_label, "确定");
    lv_label_set_long_mode(ui->screen_1_btn_certain_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_certain_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_certain, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_certain_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_certain, 210, 6);
    lv_obj_set_size(ui->screen_1_btn_certain, 62, 35);

    //Write style for screen_1_btn_certain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_certain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_certain, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_certain, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_certain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_certain, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_certain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_certain, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_certain, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_certain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_certain, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_cancel
    ui->screen_1_btn_cancel = lv_btn_create(ui->screen_1_cont_set);
    ui->screen_1_btn_cancel_label = lv_label_create(ui->screen_1_btn_cancel);
    lv_label_set_text(ui->screen_1_btn_cancel_label, "取消");
    lv_label_set_long_mode(ui->screen_1_btn_cancel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_cancel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_cancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_cancel_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_cancel, 0, 5);
    lv_obj_set_size(ui->screen_1_btn_cancel, 61, 37);

    //Write style for screen_1_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_cancel, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_cancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_cancel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_cancel, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_1.
    char string_data[50] = {0};  
    sprintf(string_data, "%d", TimeDataStr.time1);

    char string_data1[50] = {0};  
    sprintf(string_data1, "%d", TimeDataStr.time2);

    char string_data2[50] = {0};  
    sprintf(string_data2, "%d", TimeDataStr.time3);
    
    char string_data3[50] = {0};  
    sprintf(string_data3, "%d", GrindDataStr.data.target);  

    lv_label_set_text_fmt(guider_ui.screen_1_btn_settime1_label, "0%s", string_data);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_settime2_label, "0%s", string_data1);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_settime3_label, "0%s", string_data2);
    lv_label_set_text_fmt(guider_ui.screen_1_label_set, "%s", string_data3);

    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

    //Init events for screen.
    events_init_screen_1(ui);
}
