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

    //Write codes screen_1_btn_1
    ui->screen_1_btn_1 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_1_label = lv_label_create(ui->screen_1_btn_1);
    lv_label_set_text(ui->screen_1_btn_1_label, "Fine");
    lv_label_set_long_mode(ui->screen_1_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_1, 287, 50);
    lv_obj_set_size(ui->screen_1_btn_1, 60, 60);

    //Write style for screen_1_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_1, 124, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_1, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_1_btn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_1_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_1_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_1_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_2
    ui->screen_1_btn_2 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_2_label = lv_label_create(ui->screen_1_btn_2);
    lv_label_set_text(ui->screen_1_btn_2_label, "Coarse");
    lv_label_set_long_mode(ui->screen_1_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_2, 139, 50);
    lv_obj_set_size(ui->screen_1_btn_2, 60, 60);

    //Write style for screen_1_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_2, 129, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_2, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_1_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_1_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_1_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_1_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_1_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_2, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_calibration1
    ui->screen_1_btn_calibration1 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_calibration1_label = lv_label_create(ui->screen_1_btn_calibration1);
    lv_label_set_text(ui->screen_1_btn_calibration1_label, "OK");
    lv_label_set_long_mode(ui->screen_1_btn_calibration1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_calibration1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_calibration1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_calibration1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_calibration1, 287, 125);
    lv_obj_set_size(ui->screen_1_btn_calibration1, 50, 50);

    //Write style for screen_1_btn_calibration1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_calibration1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_calibration1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_calibration1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_calibration1, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_calibration1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_1_btn_calibration1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_1_btn_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_1_btn_calibration1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_1_btn_calibration1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_1_btn_calibration1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_calibration1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_calibration1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_calibration1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_calibration1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_calibration2
    ui->screen_1_btn_calibration2 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_calibration2_label = lv_label_create(ui->screen_1_btn_calibration2);
    lv_label_set_text(ui->screen_1_btn_calibration2_label, "OK");
    lv_label_set_long_mode(ui->screen_1_btn_calibration2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_calibration2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_calibration2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_calibration2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_calibration2, 287, 185);
    lv_obj_set_size(ui->screen_1_btn_calibration2, 50, 50);

    //Write style for screen_1_btn_calibration2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_calibration2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_calibration2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_calibration2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_calibration2, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_calibration2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_1_btn_calibration2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_1_btn_calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_1_btn_calibration2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_1_btn_calibration2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_1_btn_calibration2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_calibration2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_calibration2, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_calibration2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_calibration2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_3
    ui->screen_1_btn_3 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_3_label = lv_label_create(ui->screen_1_btn_3);
    lv_label_set_text(ui->screen_1_btn_3_label, "BACK");
    lv_label_set_long_mode(ui->screen_1_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_3, 379, 220);
    lv_obj_set_size(ui->screen_1_btn_3, 100, 50);

    //Write style for screen_1_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_3, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_thickness
    ui->screen_1_label_thickness = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_thickness, "300");
    lv_label_set_long_mode(ui->screen_1_label_thickness, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_thickness, 220, 50);
    lv_obj_set_size(ui->screen_1_label_thickness, 45, 19);

    //Write style for screen_1_label_thickness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_thickness, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_thickness, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_thickness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_thickness, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_thickness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_um
    ui->screen_1_label_um = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_um, "um");
    lv_label_set_long_mode(ui->screen_1_label_um, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_um, 235, 70);
    lv_obj_set_size(ui->screen_1_label_um, 45, 19);

    //Write style for screen_1_label_um, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_um, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_um, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_um, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_um, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_um, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_thicknessset
    ui->screen_1_btn_thicknessset = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_thicknessset_label = lv_label_create(ui->screen_1_btn_thicknessset);
    lv_label_set_text(ui->screen_1_btn_thicknessset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_thicknessset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_thicknessset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_thicknessset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_thicknessset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_thicknessset, 204, 50);
    lv_obj_set_size(ui->screen_1_btn_thicknessset, 80, 19);

    //Write style for screen_1_btn_thicknessset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_thicknessset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_thicknessset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_thicknessset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_thicknessset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_thicknessset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_thicknessset, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_thicknessset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_thicknessset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_cont_1
    ui->screen_1_cont_1 = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cont_1, 91, 124);
    lv_obj_set_size(ui->screen_1_cont_1, 300, 59);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_1_cont_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cont_1, lv_color_hex(0x94877f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_cont_1, lv_color_hex(0x94877f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_spinbox_1
    ui->screen_1_spinbox_1 = lv_spinbox_create(ui->screen_1_cont_1);
    lv_obj_set_pos(ui->screen_1_spinbox_1, 113, 9);
    lv_obj_set_width(ui->screen_1_spinbox_1, 70);
    lv_obj_set_height(ui->screen_1_spinbox_1, 40);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_1, 4, 4);
    lv_spinbox_set_range(ui->screen_1_spinbox_1, 0, 2000);
    lv_coord_t screen_1_spinbox_1_h = lv_obj_get_height(ui->screen_1_spinbox_1);
    ui->screen_1_spinbox_1_btn_plus = lv_btn_create(ui->screen_1_cont_1);
    lv_obj_set_size(ui->screen_1_spinbox_1_btn_plus, screen_1_spinbox_1_h, screen_1_spinbox_1_h);
    lv_obj_align_to(ui->screen_1_spinbox_1_btn_plus, ui->screen_1_spinbox_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_1_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_1_btn_plus, lv_screen_1_spinbox_1_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_1_btn_minus = lv_btn_create(ui->screen_1_cont_1);
    lv_obj_set_size(ui->screen_1_spinbox_1_btn_minus, screen_1_spinbox_1_h, screen_1_spinbox_1_h);
    lv_obj_align_to(ui->screen_1_spinbox_1_btn_minus, ui->screen_1_spinbox_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_1_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_1_btn_minus, lv_screen_1_spinbox_1_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_1, 113, 9);

    //Write style for screen_1_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_1, lv_color_hex(0x94877f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_1, lv_color_hex(0x94877f), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_1_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_1_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_1_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_1_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_1_extra_btns_main_default, lv_color_hex(0x94877f));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_1_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_1_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_1_btn_plus, &style_screen_1_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_1_btn_minus, &style_screen_1_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_confirm
    ui->screen_1_btn_confirm = lv_btn_create(ui->screen_1_cont_1);
    ui->screen_1_btn_confirm_label = lv_label_create(ui->screen_1_btn_confirm);
    lv_label_set_text(ui->screen_1_btn_confirm_label, "Confirm");
    lv_label_set_long_mode(ui->screen_1_btn_confirm_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_confirm_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_confirm, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_confirm_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_confirm, 234, 3);
    lv_obj_set_size(ui->screen_1_btn_confirm, 57, 49);

    //Write style for screen_1_btn_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_confirm, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_confirm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_confirm, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
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
    lv_obj_set_pos(ui->screen_1_btn_concel, 1, 1);
    lv_obj_set_size(ui->screen_1_btn_concel, 61, 54);

    //Write style for screen_1_btn_concel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_concel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_concel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_concel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_concel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_concel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_concel, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_concel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_concel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_hint1
    ui->screen_1_label_hint1 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_hint1, "Insert the basket, wait for 5 seconds, and then click OK");
    lv_label_set_long_mode(ui->screen_1_label_hint1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_hint1, 130, 130);
    lv_obj_set_size(ui->screen_1_label_hint1, 130, 40);

    //Write style for screen_1_label_hint1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_hint1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_hint1, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_hint1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_hint1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_hint1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_hint2
    ui->screen_1_label_hint2 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_hint2, "Place 20 grams of weights, wait for 5 seconds, and then click OK");
    lv_label_set_long_mode(ui->screen_1_label_hint2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_hint2, 130, 190);
    lv_obj_set_size(ui->screen_1_label_hint2, 130, 50);

    //Write style for screen_1_label_hint2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_hint2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_hint2, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_hint2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_hint2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_hint2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_Grindingspeed
    ui->screen_1_btn_Grindingspeed = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_Grindingspeed_label = lv_label_create(ui->screen_1_btn_Grindingspeed);
    lv_label_set_text(ui->screen_1_btn_Grindingspeed_label, "0");
    lv_label_set_long_mode(ui->screen_1_btn_Grindingspeed_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_Grindingspeed_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_Grindingspeed, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_Grindingspeed_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_Grindingspeed, 40, 30);
    lv_obj_set_size(ui->screen_1_btn_Grindingspeed, 50, 20);

    //Write style for screen_1_btn_Grindingspeed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_Grindingspeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_Grindingspeed, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_Grindingspeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_Grindingspeed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_Grindingspeed, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_Grindingspeed, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_Grindingspeed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_Grindingspeed, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_1.
    char string_um[50] = {0};
    sprintf(string_um, "%d", GrindSetData.grind_thickness);   
    lv_label_set_text_fmt(guider_ui.screen_1_label_thickness, "%s", string_um);
    char string_g[50] = {0};
    sprintf(string_g, "%d", GrindSetData.grind_speed);   
    lv_label_set_text_fmt(guider_ui.screen_1_btn_Grindingspeed_label, "%s", string_g); 

    lv_obj_move_foreground(ui->screen_1_cont_1);
    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

    //Init events for screen.
    events_init_screen_1(ui);
}
