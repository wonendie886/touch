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
#include "protocol.h"

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

    //Write codes screen_1_label_steamtemp
    ui->screen_1_label_steamtemp = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_steamtemp, "Steam Boiler(°C)");
    lv_label_set_long_mode(ui->screen_1_label_steamtemp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_steamtemp, 10, 0);
    lv_obj_set_size(ui->screen_1_label_steamtemp, 100, 28);

    //Write style for screen_1_label_steamtemp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_steamtemp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_steamtemp, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_steamtemp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_steamtemp, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_steamtemp, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_steamtemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_steamtempset
    ui->screen_1_btn_steamtempset = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_steamtempset_label = lv_label_create(ui->screen_1_btn_steamtempset);
    lv_label_set_text(ui->screen_1_btn_steamtempset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_steamtempset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_steamtempset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_steamtempset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_steamtempset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_steamtempset, 250, 0);
    lv_obj_set_size(ui->screen_1_btn_steamtempset, 100, 28);

    //Write style for screen_1_btn_steamtempset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_steamtempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_steamtempset, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_steamtempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_steamtempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_steamtempset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_steamtempset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_steamtempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_steamtempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_steamtempset, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_steamtempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_steamtempset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_coffeetemp
    ui->screen_1_label_coffeetemp = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_coffeetemp, "Coffee boiler(°C)");
    lv_label_set_long_mode(ui->screen_1_label_coffeetemp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_coffeetemp, 10, 34);
    lv_obj_set_size(ui->screen_1_label_coffeetemp, 100, 28);

    //Write style for screen_1_label_coffeetemp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_coffeetemp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_coffeetemp, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_coffeetemp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_coffeetemp, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_coffeetemp, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_coffeetemp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_coffeetempset
    ui->screen_1_btn_coffeetempset = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_coffeetempset_label = lv_label_create(ui->screen_1_btn_coffeetempset);
    lv_label_set_text(ui->screen_1_btn_coffeetempset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_coffeetempset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_coffeetempset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_coffeetempset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_coffeetempset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_coffeetempset, 250, 34);
    lv_obj_set_size(ui->screen_1_btn_coffeetempset, 100, 28);

    //Write style for screen_1_btn_coffeetempset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_coffeetempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_coffeetempset, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_coffeetempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_coffeetempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_coffeetempset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_coffeetempset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_coffeetempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_coffeetempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_coffeetempset, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_coffeetempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_coffeetempset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_back
    ui->screen_1_btn_back = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_back_label = lv_label_create(ui->screen_1_btn_back);
    lv_label_set_text(ui->screen_1_btn_back_label, "Back");
    lv_label_set_long_mode(ui->screen_1_btn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_back, 430, 247);
    lv_obj_set_size(ui->screen_1_btn_back, 50, 25);

    //Write style for screen_1_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_back, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_back, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_back, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time1
    ui->screen_1_label_time1 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_time1, "Time1(s)");
    lv_label_set_long_mode(ui->screen_1_label_time1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time1, 10, 70);
    lv_obj_set_size(ui->screen_1_label_time1, 100, 28);

    //Write style for screen_1_label_time1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time1, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time2
    ui->screen_1_label_time2 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_time2, "Time3(s)");
    lv_label_set_long_mode(ui->screen_1_label_time2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time2, 10, 136);
    lv_obj_set_size(ui->screen_1_label_time2, 100, 28);

    //Write style for screen_1_label_time2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time2, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time3
    ui->screen_1_label_time3 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_time3, "Time2(s)");
    lv_label_set_long_mode(ui->screen_1_label_time3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time3, 10, 102);
    lv_obj_set_size(ui->screen_1_label_time3, 100, 28);

    //Write style for screen_1_label_time3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time3, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_1_btn_time1set
    ui->screen_1_btn_time1set = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_time1set_label = lv_label_create(ui->screen_1_btn_time1set);
    lv_label_set_text(ui->screen_1_btn_time1set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time1set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time1set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time1set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time1set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time1set, 250, 70);
    lv_obj_set_size(ui->screen_1_btn_time1set, 100, 28);

    //Write style for screen_1_btn_time1set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time1set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time1set, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time1set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time1set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time1set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time1set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time1set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time1set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time1set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time1set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time1set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_time2set
    ui->screen_1_btn_time2set = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_time2set_label = lv_label_create(ui->screen_1_btn_time2set);
    lv_label_set_text(ui->screen_1_btn_time2set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time2set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time2set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time2set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time2set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time2set, 250, 136);
    lv_obj_set_size(ui->screen_1_btn_time2set, 100, 28);

    //Write style for screen_1_btn_time2set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time2set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time2set, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time2set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time2set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time2set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time2set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time2set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time2set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time2set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time2set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time2set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_time3set
    ui->screen_1_btn_time3set = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_time3set_label = lv_label_create(ui->screen_1_btn_time3set);
    lv_label_set_text(ui->screen_1_btn_time3set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time3set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time3set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time3set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time3set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time3set, 250, 102);
    lv_obj_set_size(ui->screen_1_btn_time3set, 100, 28);

    //Write style for screen_1_btn_time3set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time3set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time3set, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time3set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time3set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time3set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time3set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time3set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time3set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time3set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time3set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time3set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_cont_set
    ui->screen_1_cont_set = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cont_set, 110, 137);
    lv_obj_set_size(ui->screen_1_cont_set, 275, 40);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_set, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_1_cont_set, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_cont_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_cont_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cont_set, lv_color_hex(0x525151), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cont_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_cancel
    ui->screen_1_btn_cancel = lv_btn_create(ui->screen_1_cont_set);
    ui->screen_1_btn_cancel_label = lv_label_create(ui->screen_1_btn_cancel);
    lv_label_set_text(ui->screen_1_btn_cancel_label, "取消");
    lv_label_set_long_mode(ui->screen_1_btn_cancel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_cancel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_cancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_cancel_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_cancel, 5, 2);
    lv_obj_set_size(ui->screen_1_btn_cancel, 50, 35);

    //Write style for screen_1_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_cancel, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_cancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_cancel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_cancel, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_certain
    ui->screen_1_btn_certain = lv_btn_create(ui->screen_1_cont_set);
    ui->screen_1_btn_certain_label = lv_label_create(ui->screen_1_btn_certain);
    lv_label_set_text(ui->screen_1_btn_certain_label, "确认");
    lv_label_set_long_mode(ui->screen_1_btn_certain_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_certain_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_certain, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_certain_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_certain, 220, 2);
    lv_obj_set_size(ui->screen_1_btn_certain, 50, 35);

    //Write style for screen_1_btn_certain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_certain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_certain, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_certain, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_certain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_certain, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_certain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_certain, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_certain, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_certain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_certain, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_spinbox_1
    ui->screen_1_spinbox_1 = lv_spinbox_create(ui->screen_1_cont_set);
    lv_obj_set_pos(ui->screen_1_spinbox_1, 107, 2);
    lv_obj_set_width(ui->screen_1_spinbox_1, 63);
    lv_obj_set_height(ui->screen_1_spinbox_1, 36);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_1, 3, 3);
    lv_spinbox_set_range(ui->screen_1_spinbox_1, 0, 135);
    lv_coord_t screen_1_spinbox_1_h = lv_obj_get_height(ui->screen_1_spinbox_1);
    ui->screen_1_spinbox_1_btn_plus = lv_btn_create(ui->screen_1_cont_set);
    lv_obj_set_size(ui->screen_1_spinbox_1_btn_plus, screen_1_spinbox_1_h, screen_1_spinbox_1_h);
    lv_obj_align_to(ui->screen_1_spinbox_1_btn_plus, ui->screen_1_spinbox_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_1_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_1_btn_plus, lv_screen_1_spinbox_1_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_1_btn_minus = lv_btn_create(ui->screen_1_cont_set);
    lv_obj_set_size(ui->screen_1_spinbox_1_btn_minus, screen_1_spinbox_1_h, screen_1_spinbox_1_h);
    lv_obj_align_to(ui->screen_1_spinbox_1_btn_minus, ui->screen_1_spinbox_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_1_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_1_btn_minus, lv_screen_1_spinbox_1_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_1, 107, 2);

    //Write style for screen_1_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_1, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_1_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_1_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_1_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_1_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_1_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_1_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_1_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_1_btn_plus, &style_screen_1_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_1_btn_minus, &style_screen_1_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    #if (LEFT_OR_COFFEE == LEFT)
    //Write codes screen_1_label_hotwater
    ui->screen_1_label_hotwater = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_hotwater, "Hotwater(s)");
    lv_label_set_long_mode(ui->screen_1_label_hotwater, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_hotwater, 10, 204);
    lv_obj_set_size(ui->screen_1_label_hotwater, 100, 28);

    //Write style for screen_1_label_hotwater, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_hotwater, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_hotwater, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_hotwater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_hotwater, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_hotwater, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_hotwaterset
    ui->screen_1_btn_hotwaterset = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_hotwaterset_label = lv_label_create(ui->screen_1_btn_hotwaterset);
    lv_label_set_text(ui->screen_1_btn_hotwaterset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_hotwaterset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_hotwaterset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_hotwaterset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_hotwaterset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_hotwaterset, 250, 204);
    lv_obj_set_size(ui->screen_1_btn_hotwaterset, 100, 28);

    //Write style for screen_1_btn_hotwaterset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_hotwaterset, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_hotwaterset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_hotwaterset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_hotwaterset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_hotwaterset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_hotwaterset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_hotwaterset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_hotwaterset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_hotwaterset, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_hotwaterset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_hotwaterset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    #endif

    //Write codes screen_1_label_brewblock
    ui->screen_1_label_brewblock = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_brewblock, "Brew Block(°C)");
    lv_label_set_long_mode(ui->screen_1_label_brewblock, LV_LABEL_LONG_WRAP);   
    lv_obj_set_pos(ui->screen_1_label_brewblock, 10, 170);
    lv_obj_set_size(ui->screen_1_label_brewblock, 100, 28);


    //Write style for screen_1_label_brewblock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_brewblock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_brewblock, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_brewblock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_brewblock, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_brewblock, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_brewblock
    ui->screen_1_btn_brewblock = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_brewblock_label = lv_label_create(ui->screen_1_btn_brewblock);
    lv_label_set_text(ui->screen_1_btn_brewblock_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_brewblock_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_brewblock_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_brewblock, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_brewblock_label, LV_PCT(100));   
    lv_obj_set_pos(ui->screen_1_btn_brewblock, 250, 170);
    lv_obj_set_size(ui->screen_1_btn_brewblock, 100, 28);

    //Write style for screen_1_btn_brewblock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_brewblock, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_brewblock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_brewblock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_brewblock, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_brewblock, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_brewblock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_brewblock, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_brewblock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_brewblock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    //The custom code of screen_1.
    char string_data[50] = {0};  
    sprintf(string_data, "%d", GrindSetData.time_1);

    char string_data1[50] = {0};  
    sprintf(string_data1, "%d", GrindSetData.time_2);

    char string_data2[50] = {0};  
    sprintf(string_data2, "%d", GrindSetData.time_3);
    
    char string_data3[50] = {0};  
    sprintf(string_data3, "%d", GrindSetData.time_4);  

    char string_data4[50] = {0};  
    sprintf(string_data4, "%d", GrindSetData.temp_steam);
    
    char string_data5[50] = {0};  
    sprintf(string_data5, "%d", GrindSetData.temp_coffee); 

    char string_data6[50] = {0};  
    sprintf(string_data6, "%d", GrindSetData.time_hotwater);

    char string_data7[50] = {0};  
    sprintf(string_data7, "%d", GrindSetData.temp_brew);

    lv_label_set_text_fmt(guider_ui.screen_1_btn_time1set_label, "%s", string_data);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_time2set_label, "%s", string_data1);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_time3set_label, "%s", string_data2);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_coffeetempset_label, "%s", string_data5);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_brewblock_label, "%s", string_data7);
    #if (LEFT_OR_COFFEE == RIGHT)
    lv_label_set_text_fmt(guider_ui.screen_1_btn_steamtempset_label, "%s", string_data4);
    #endif
    #if (LEFT_OR_COFFEE == LEFT)
    lv_label_set_text_fmt(guider_ui.screen_1_btn_hotwaterset_label, "%s", string_data6);
    lv_obj_add_flag(ui->screen_1_label_steamtemp, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_1_btn_steamtempset, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_1_btn_steamtempset_label, LV_OBJ_FLAG_HIDDEN);
    #endif
    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

    //Init events for screen.
    events_init_screen_1(ui);
}
