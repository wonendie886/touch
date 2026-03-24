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
#include "flash.h"


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
    lv_label_set_text(ui->screen_1_btn_back_label, "BACK");
    lv_label_set_long_mode(ui->screen_1_btn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_back, 420, 220);
    lv_obj_set_size(ui->screen_1_btn_back, 60, 52);

    //Write style for screen_1_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_back, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_back, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_back, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_tabview_1
    ui->screen_1_tabview_1 = lv_tabview_create(ui->screen_1, LV_DIR_LEFT, 90);
    lv_obj_set_pos(ui->screen_1_tabview_1, 0, 0);
    lv_obj_set_size(ui->screen_1_tabview_1, 417, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_tabview_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_tabview_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_tabview_1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_tabview_1_extra_btnm_main_default
    static lv_style_t style_screen_1_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_screen_1_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_screen_1_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_tabview_1_extra_btnm_main_default, lv_color_hex(0x202020));
    lv_style_set_bg_grad_dir(&style_screen_1_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_screen_1_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_1_tabview_1), &style_screen_1_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_tabview_1_extra_btnm_items_default
    static lv_style_t style_screen_1_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_screen_1_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_screen_1_tabview_1_extra_btnm_items_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_tabview_1_extra_btnm_items_default, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_screen_1_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_1_tabview_1), &style_screen_1_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_1_tabview_1_extra_btnm_items_checked
    static lv_style_t style_screen_1_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_screen_1_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_screen_1_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_tabview_1_extra_btnm_items_checked, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_screen_1_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_screen_1_tabview_1_extra_btnm_items_checked, 4);
    lv_style_set_border_opa(&style_screen_1_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_color(&style_screen_1_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_border_side(&style_screen_1_tabview_1_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_screen_1_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_screen_1_tabview_1_extra_btnm_items_checked, 60);
    lv_style_set_bg_color(&style_screen_1_tabview_1_extra_btnm_items_checked, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_screen_1_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_1_tabview_1), &style_screen_1_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes calibration
    ui->screen_1_tabview_1_tab_1 = lv_tabview_add_tab(ui->screen_1_tabview_1,"calibration");

    lv_obj_t * screen_1_tabview_1_tab_1_label = lv_label_create(ui->screen_1_tabview_1_tab_1);
    lv_label_set_text(screen_1_tabview_1_tab_1_label, "");

    //Write codes screen_1_label_calibration2
    ui->screen_1_label_calibration2 = lv_label_create(ui->screen_1_tabview_1_tab_1);
    lv_label_set_text(ui->screen_1_label_calibration2, "Place 20 grams of weights, wait for 5 seconds, and then click OK");
    lv_label_set_long_mode(ui->screen_1_label_calibration2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_calibration2, 17, 142);
    lv_obj_set_size(ui->screen_1_label_calibration2, 168, 48);

    //Write style for screen_1_label_calibration2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_calibration2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_calibration2, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_calibration2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_label_calibration2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_label_calibration2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_calibration1
    ui->screen_1_label_calibration1 = lv_label_create(ui->screen_1_tabview_1_tab_1);
    lv_label_set_text(ui->screen_1_label_calibration1, "Insert the basket, wait for 5 seconds, and then click OK");
    lv_label_set_long_mode(ui->screen_1_label_calibration1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_calibration1, 17, 36);
    lv_obj_set_size(ui->screen_1_label_calibration1, 168, 50);

    //Write style for screen_1_label_calibration1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_calibration1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_calibration1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_calibration1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_label_calibration1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_label_calibration1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_calibration1
    ui->screen_1_btn_calibration1 = lv_btn_create(ui->screen_1_tabview_1_tab_1);
    ui->screen_1_btn_calibration1_label = lv_label_create(ui->screen_1_btn_calibration1);
    lv_label_set_text(ui->screen_1_btn_calibration1_label, "ok");
    lv_label_set_long_mode(ui->screen_1_btn_calibration1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_calibration1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_calibration1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_calibration1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_calibration1, 220, 39);
    lv_obj_set_size(ui->screen_1_btn_calibration1, 50, 50);

    //Write style for screen_1_btn_calibration1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_calibration1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_calibration1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_calibration1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_calibration1, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_calibration1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_calibration1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_calibration1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    // //Write codes screen_1_label_calibrationtime
    // ui->screen_1_label_calibrationtime = lv_label_create(ui->screen_1_tabview_1_tab_1);
    // lv_label_set_text(ui->screen_1_label_calibrationtime, "0");
    // lv_label_set_long_mode(ui->screen_1_label_calibrationtime, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // lv_obj_set_pos(ui->screen_1_label_calibrationtime, 43, 80);
    // lv_obj_set_size(ui->screen_1_label_calibrationtime, 214, 93);

    // //Write style for screen_1_label_calibrationtime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    // lv_obj_set_style_border_width(ui->screen_1_label_calibrationtime, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(ui->screen_1_label_calibrationtime, 253, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(ui->screen_1_label_calibrationtime, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_border_side(ui->screen_1_label_calibrationtime, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(ui->screen_1_label_calibrationtime, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui->screen_1_label_calibrationtime, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(ui->screen_1_label_calibrationtime, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_letter_space(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_line_space(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_align(ui->screen_1_label_calibrationtime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(ui->screen_1_label_calibrationtime, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_grad_dir(ui->screen_1_label_calibrationtime, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_top(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_right(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_bottom(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_left(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_shadow_width(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_1_btn__calibration2
    ui->screen_1_btn__calibration2 = lv_btn_create(ui->screen_1_tabview_1_tab_1);
    ui->screen_1_btn__calibration2_label = lv_label_create(ui->screen_1_btn__calibration2);
    lv_label_set_text(ui->screen_1_btn__calibration2_label, "ok");
    lv_label_set_long_mode(ui->screen_1_btn__calibration2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn__calibration2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn__calibration2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn__calibration2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn__calibration2, 222, 137);
    lv_obj_set_size(ui->screen_1_btn__calibration2, 50, 50);

    //Write style for screen_1_btn__calibration2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn__calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn__calibration2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn__calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn__calibration2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn__calibration2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn__calibration2, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn__calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn__calibration2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn__calibration2, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn__calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn__calibration2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_calibrationtime
    ui->screen_1_label_calibrationtime = lv_label_create(ui->screen_1_tabview_1_tab_1);
    lv_label_set_text(ui->screen_1_label_calibrationtime, "Label");
    lv_label_set_long_mode(ui->screen_1_label_calibrationtime, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_pos(ui->screen_1_label_calibrationtime, 43, 80);
    lv_obj_set_size(ui->screen_1_label_calibrationtime, 214, 93);

    //Write style for screen_1_label_calibrationtime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_calibrationtime, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_label_calibrationtime, 253, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_label_calibrationtime, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_label_calibrationtime, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_calibrationtime, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_calibrationtime, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_calibrationtime, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_calibrationtime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_calibrationtime, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_label_calibrationtime, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_label_calibrationtime, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_calibrationtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_flag(ui->screen_1_label_calibrationtime, LV_OBJ_FLAG_HIDDEN);
    
    //Write codes 调粗细
    ui->screen_1_tabview_1_tab_2 = lv_tabview_add_tab(ui->screen_1_tabview_1,"grindingdegree");
    lv_obj_t * screen_1_tabview_1_tab_2_label = lv_label_create(ui->screen_1_tabview_1_tab_2);
    lv_label_set_text(screen_1_tabview_1_tab_2_label, "");

    //Write codes screen_1_btn_grindsize
    ui->screen_1_btn_grindsize = lv_btn_create(ui->screen_1_tabview_1_tab_2);
    ui->screen_1_btn_grindsize_label = lv_label_create(ui->screen_1_btn_grindsize);
    lv_label_set_text(ui->screen_1_btn_grindsize_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_grindsize_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_grindsize_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_grindsize, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_grindsize_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_grindsize, 129, 122);
    lv_obj_set_size(ui->screen_1_btn_grindsize, 35, 19);

    //Write style for screen_1_btn_grindsize, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_grindsize, 198, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_grindsize, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_grindsize, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_grindsize, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_grindsize, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_grindsize, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_grindsize, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_grindsize, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_grindsize, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_grindsize, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_cont_1
    ui->screen_1_cont_1 = lv_obj_create(ui->screen_1_tabview_1_tab_2);
    lv_obj_set_pos(ui->screen_1_cont_1, 2, 107);
    lv_obj_set_size(ui->screen_1_cont_1, 300, 59);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_flag(ui->screen_1_cont_1, LV_OBJ_FLAG_HIDDEN);

    //Write codes screen_1_spinbox_grindsize
    ui->screen_1_spinbox_grindsize = lv_spinbox_create(ui->screen_1_cont_1);
    lv_obj_set_pos(ui->screen_1_spinbox_grindsize, 112, 8);
    lv_obj_set_width(ui->screen_1_spinbox_grindsize, 70);
    lv_obj_set_height(ui->screen_1_spinbox_grindsize, 40);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_grindsize, 4, 4);
    lv_spinbox_set_range(ui->screen_1_spinbox_grindsize, 50, 2000);
    lv_coord_t screen_1_spinbox_grindsize_h = lv_obj_get_height(ui->screen_1_spinbox_grindsize);
    ui->screen_1_spinbox_grindsize_btn_plus = lv_btn_create(ui->screen_1_cont_1);
    lv_obj_set_size(ui->screen_1_spinbox_grindsize_btn_plus, screen_1_spinbox_grindsize_h, screen_1_spinbox_grindsize_h);
    lv_obj_align_to(ui->screen_1_spinbox_grindsize_btn_plus, ui->screen_1_spinbox_grindsize, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_grindsize_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_grindsize_btn_plus, lv_screen_1_spinbox_grindsize_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_grindsize_btn_minus = lv_btn_create(ui->screen_1_cont_1);
    lv_obj_set_size(ui->screen_1_spinbox_grindsize_btn_minus, screen_1_spinbox_grindsize_h, screen_1_spinbox_grindsize_h);
    lv_obj_align_to(ui->screen_1_spinbox_grindsize_btn_minus, ui->screen_1_spinbox_grindsize, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_grindsize_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_grindsize_btn_minus, lv_screen_1_spinbox_grindsize_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_grindsize, 112, 8);

    //Write style for screen_1_spinbox_grindsize, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_grindsize, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_grindsize, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_grindsize, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_grindsize, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_grindsize, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_grindsize, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_grindsize, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_grindsize, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_grindsize, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_grindsize, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_grindsize, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_grindsize, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_grindsize, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_grindsize, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_grindsize, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_grindsize, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_grindsize, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_grindsize, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_grindsize, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_grindsize, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_grindsize, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_grindsize, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_grindsize, lv_color_hex(0x000000), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_grindsize, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_grindsize_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_grindsize_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_grindsize_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_grindsize_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_grindsize_extra_btns_main_default, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_grindsize_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_grindsize_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_grindsize_extra_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_grindsize_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_grindsize_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_grindsize_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_grindsize_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_grindsize_btn_plus, &style_screen_1_spinbox_grindsize_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_grindsize_btn_minus, &style_screen_1_spinbox_grindsize_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_confirm
    ui->screen_1_btn_confirm = lv_btn_create(ui->screen_1_cont_1);
    ui->screen_1_btn_confirm_label = lv_label_create(ui->screen_1_btn_confirm);
    lv_label_set_text(ui->screen_1_btn_confirm_label, "Confirm");
    lv_label_set_long_mode(ui->screen_1_btn_confirm_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_confirm_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_confirm, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_confirm_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_confirm, 229, 3);
    lv_obj_set_size(ui->screen_1_btn_confirm, 62, 49);

    //Write style for screen_1_btn_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_confirm, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_confirm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_confirm, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_confirm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_confirm, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_concel
    ui->screen_1_btn_concel = lv_btn_create(ui->screen_1_cont_1);
    ui->screen_1_btn_concel_label = lv_label_create(ui->screen_1_btn_concel);
    lv_label_set_text(ui->screen_1_btn_concel_label, "Concel");
    lv_label_set_long_mode(ui->screen_1_btn_concel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_concel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_concel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_concel_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_concel, 2, 2);
    lv_obj_set_size(ui->screen_1_btn_concel, 61, 54);

    //Write style for screen_1_btn_concel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_concel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_concel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_concel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_concel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_concel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_concel, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_concel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_concel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_um
    ui->screen_1_label_um = lv_label_create(ui->screen_1_tabview_1_tab_2);
    lv_label_set_text(ui->screen_1_label_um, "um");
    lv_label_set_long_mode(ui->screen_1_label_um, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_um, 172, 124);
    lv_obj_set_size(ui->screen_1_label_um, 45, 19);

    //Write style for screen_1_label_um, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_um, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_um, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_um, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_um, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_thickness
    ui->screen_1_label_thickness = lv_label_create(ui->screen_1_tabview_1_tab_2);
    lv_label_set_text(ui->screen_1_label_thickness, "300");
    lv_label_set_long_mode(ui->screen_1_label_thickness, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_thickness, 111, 125);
    lv_obj_set_size(ui->screen_1_label_thickness, 45, 19);

    //Write style for screen_1_label_thickness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_thickness, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_thickness, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_thickness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_thickness, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_coarser
    ui->screen_1_btn_coarser = lv_btn_create(ui->screen_1_tabview_1_tab_2);
    ui->screen_1_btn_coarser_label = lv_label_create(ui->screen_1_btn_coarser);
    lv_label_set_text(ui->screen_1_btn_coarser_label, "Coarse");
    lv_label_set_long_mode(ui->screen_1_btn_coarser_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_coarser_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_coarser, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_coarser_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_coarser, 40, 106);
    lv_obj_set_size(ui->screen_1_btn_coarser, 60, 60);

    //Write style for screen_1_btn_coarser, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_coarser, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_coarser, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_coarser, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_coarser, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_coarser, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_coarser, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_coarser, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_coarser, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_coarser, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_coarser, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_coarser, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_1_btn_thinner
    ui->screen_1_btn_thinner = lv_btn_create(ui->screen_1_tabview_1_tab_2);
    ui->screen_1_btn_thinner_label = lv_label_create(ui->screen_1_btn_thinner);
    lv_label_set_text(ui->screen_1_btn_thinner_label, "Fine");
    lv_label_set_long_mode(ui->screen_1_btn_thinner_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_thinner_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_thinner, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_thinner_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_thinner, 214, 106);
    lv_obj_set_size(ui->screen_1_btn_thinner, 60, 60);

    //Write style for screen_1_btn_thinner, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_thinner, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_thinner, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_thinner, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_thinner, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_thinner, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_thinner, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_thinner, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_thinner, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_thinner, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_thinner, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_thinner, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



    ui->screen_1_tabview_1_tab_3 = lv_tabview_add_tab(ui->screen_1_tabview_1,"");
    lv_obj_t * screen_1_tabview_1_tab_3_label = lv_label_create(ui->screen_1_tabview_1_tab_3);
    lv_label_set_text(screen_1_tabview_1_tab_3_label, "");

    //The custom code of screen_1.
    char string_um[50] = {0};
    sprintf(string_um, "%d", GrindSetData.grind_thickness);
    
    lv_label_set_text_fmt(guider_ui.screen_1_label_thickness, "%s", string_um);

    lv_obj_move_foreground(ui->screen_1_cont_1);

    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

    //Init events for screen.
    events_init_screen_1(ui);
}
