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

void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 480, 272);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0xd6cdcd), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_1
    ui->screen_img_1 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_1, &_brew_alpha_8x8);
    lv_img_set_pivot(ui->screen_img_1, 50,50);
    lv_img_set_angle(ui->screen_img_1, 0);
    lv_obj_set_pos(ui->screen_img_1, 16, 11);
    lv_obj_set_size(ui->screen_img_1, 8, 8);

    //Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_1, "");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_1, 27, 11);
    lv_obj_set_size(ui->screen_label_1, 27, 9);

    //Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_2
    ui->screen_label_2 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_2, "°C");
    lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_2, 57, 11);
    lv_obj_set_size(ui->screen_label_2, 17, 9);

    //Write style for screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_2, lv_color_hex(0x868686), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_2, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_2
    ui->screen_img_2 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_2, &_logo_alpha_47x19);
    lv_img_set_pivot(ui->screen_img_2, 50,50);
    lv_img_set_angle(ui->screen_img_2, 0);
    lv_obj_set_pos(ui->screen_img_2, 217, 9);
    lv_obj_set_size(ui->screen_img_2, 47, 19);

    //Write style for screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_3
    ui->screen_img_3 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_3, &_steamblock_alpha_14x13);
    lv_img_set_pivot(ui->screen_img_3, 50,50);
    lv_img_set_angle(ui->screen_img_3, 0);
    lv_obj_set_pos(ui->screen_img_3, 362, 11);
    lv_obj_set_size(ui->screen_img_3, 14, 13);

    //Write style for screen_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_3, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_3
    ui->screen_label_3 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_3, "");
    lv_label_set_long_mode(ui->screen_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_3, 381, 11);
    lv_obj_set_size(ui->screen_label_3, 27, 9);

    //Write style for screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_3, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_4
    ui->screen_img_4 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_4, &_coffeebock_alpha_14x13);
    lv_img_set_pivot(ui->screen_img_4, 50,50);
    lv_img_set_angle(ui->screen_img_4, 0);
    lv_obj_set_pos(ui->screen_img_4, 412, 11);
    lv_obj_set_size(ui->screen_img_4, 14, 13);

    //Write style for screen_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_4, 140, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_4
    ui->screen_label_4 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_4, "");
    lv_label_set_long_mode(ui->screen_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_4, 428, 11);
    lv_obj_set_size(ui->screen_label_4, 27, 9);

    //Write style for screen_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_4, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_5
    ui->screen_img_5 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_5, &_caidan_alpha_8x7);
    lv_img_set_pivot(ui->screen_img_5, 50,50);
    lv_img_set_angle(ui->screen_img_5, 0);
    lv_obj_set_pos(ui->screen_img_5, 460, 12);
    lv_obj_set_size(ui->screen_img_5, 8, 7);

    //Write style for screen_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_10
    ui->screen_img_10 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_10, &_btnnew_alpha_104x100);
    lv_img_set_pivot(ui->screen_img_10, 50,50);
    lv_img_set_angle(ui->screen_img_10, 0);
    lv_obj_set_pos(ui->screen_img_10, 8, 51);
    lv_obj_set_size(ui->screen_img_10, 104, 100);

    //Write style for screen_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_9
    ui->screen_img_9 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_9, &_1coffee_alpha_52x52);
    lv_img_set_pivot(ui->screen_img_9, 50,50);
    lv_img_set_angle(ui->screen_img_9, 0);
    lv_obj_set_pos(ui->screen_img_9, 33, 63);
    lv_obj_set_size(ui->screen_img_9, 52, 52);

    //Write style for screen_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_9
    ui->screen_label_9 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_9, "1  CAP");
    lv_label_set_long_mode(ui->screen_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_9, 32, 121);
    lv_obj_set_size(ui->screen_label_9, 55, 17);

    //Write style for screen_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_9, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_9, lv_color_hex(0xd79442), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_9, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_9, lv_color_hex(0xfcfbfa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_11
    ui->screen_img_11 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_11, &_btnnew_alpha_104x100);
    lv_img_set_pivot(ui->screen_img_11, 50,50);
    lv_img_set_angle(ui->screen_img_11, 0);
    lv_obj_set_pos(ui->screen_img_11, 8, 160);
    lv_obj_set_size(ui->screen_img_11, 104, 100);

    //Write style for screen_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_12
    ui->screen_img_12 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_12, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_12, &_3coffee_alpha_52x52);
    lv_img_set_pivot(ui->screen_img_12, 50,50);
    lv_img_set_angle(ui->screen_img_12, 0);
    lv_obj_set_pos(ui->screen_img_12, 33, 173);
    lv_obj_set_size(ui->screen_img_12, 52, 52);

    //Write style for screen_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_10
    ui->screen_label_10 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_10, "3  CAP");
    lv_label_set_long_mode(ui->screen_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_10, 32, 230);
    lv_obj_set_size(ui->screen_label_10, 55, 17);

    //Write style for screen_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_10, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_10, lv_color_hex(0xd79442), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_10, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_10, lv_color_hex(0xfcfbfa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_label_16
    ui->screen_label_16 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_16, "0.0 bar");
    lv_label_set_long_mode(ui->screen_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_16, 220, 159);
    lv_obj_set_size(ui->screen_label_16, 41, 17);

    //Write style for screen_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_16, lv_color_hex(0xd79442), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_16, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_18
    ui->screen_label_18 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_18, "00:00");
    lv_label_set_long_mode(ui->screen_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_18, 195, 115);
    lv_obj_set_size(ui->screen_label_18, 91, 42);

    //Write style for screen_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_18, lv_color_hex(0x3f291d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_18, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_18, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_img_15
    ui->screen_img_15 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_15, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_15, &_btnnew_alpha_104x100);
    lv_img_set_pivot(ui->screen_img_15, 50,50);
    lv_img_set_angle(ui->screen_img_15, 0);
    lv_obj_set_pos(ui->screen_img_15, 368, 51);
    lv_obj_set_size(ui->screen_img_15, 104, 100);

    //Write style for screen_img_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_16
    ui->screen_img_16 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_16, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_16, &_2coffee_alpha_52x52);
    lv_img_set_pivot(ui->screen_img_16, 50,50);
    lv_img_set_angle(ui->screen_img_16, 0);
    lv_obj_set_pos(ui->screen_img_16, 395, 62);
    lv_obj_set_size(ui->screen_img_16, 52, 52);

    //Write style for screen_img_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_19
    ui->screen_label_19 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_19, "2  CAP");
    lv_label_set_long_mode(ui->screen_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_19, 392, 121);
    lv_obj_set_size(ui->screen_label_19, 55, 17);

    //Write style for screen_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_19, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_19, lv_color_hex(0xd79442), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_19, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_19, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_19, lv_color_hex(0xfcfbfa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_19, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_17
    ui->screen_img_17 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_17, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_17, &_btnnew_alpha_104x100);
    lv_img_set_pivot(ui->screen_img_17, 50,50);
    lv_img_set_angle(ui->screen_img_17, 0);
    lv_obj_set_pos(ui->screen_img_17, 368, 160);
    lv_obj_set_size(ui->screen_img_17, 104, 100);

    //Write style for screen_img_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_18
    ui->screen_img_18 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_18, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_18, &_4coffee_alpha_52x52);
    lv_img_set_pivot(ui->screen_img_18, 50,50);
    lv_img_set_angle(ui->screen_img_18, 0);
    lv_obj_set_pos(ui->screen_img_18, 394, 173);
    lv_obj_set_size(ui->screen_img_18, 52, 52);

    //Write style for screen_img_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_20
    ui->screen_label_20 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_20, "4  CAP");
    lv_label_set_long_mode(ui->screen_label_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_20, 393, 230);
    lv_obj_set_size(ui->screen_label_20, 55, 17);

    //Write style for screen_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_20, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_20, lv_color_hex(0xd79442), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_20, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_20, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_20, lv_color_hex(0xfcfbfa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_20, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_22
    ui->screen_img_22 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_22, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_22, &_6_alpha_38x38);
    lv_img_set_pivot(ui->screen_img_22, 50,50);
    lv_img_set_angle(ui->screen_img_22, 0);
    lv_obj_set_pos(ui->screen_img_22, 293, 221);
    lv_obj_set_size(ui->screen_img_22, 38, 38);
    lv_obj_add_flag(ui->screen_img_22,LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_img_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_cont_1
    ui->screen_cont_1 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_1, 103, 41);
    lv_obj_set_size(ui->screen_cont_1, 272, 154);
    lv_obj_set_scrollbar_mode(ui->screen_cont_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_cont_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_1, lv_color_hex(0x222222), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_23
    ui->screen_img_23 = lv_img_create(ui->screen_cont_1);
    lv_obj_add_flag(ui->screen_img_23, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_23, &_juxing_alpha_65x38);
    lv_img_set_pivot(ui->screen_img_23, 50,50);
    lv_img_set_angle(ui->screen_img_23, 0);
    lv_obj_set_pos(ui->screen_img_23, 0, 15);
    lv_obj_set_size(ui->screen_img_23, 65, 38);

    //Write style for screen_img_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_24
    ui->screen_img_24 = lv_img_create(ui->screen_cont_1);
    lv_obj_add_flag(ui->screen_img_24, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_24, &_juxing_alpha_65x38);
    lv_img_set_pivot(ui->screen_img_24, 50,50);
    lv_img_set_angle(ui->screen_img_24, 0);
    lv_obj_set_pos(ui->screen_img_24, 0, 64);
    lv_obj_set_size(ui->screen_img_24, 65, 38);

    //Write style for screen_img_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_24, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_25
    ui->screen_img_25 = lv_img_create(ui->screen_cont_1);
    lv_obj_add_flag(ui->screen_img_25, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_25, &_juxing_alpha_65x38);
    lv_img_set_pivot(ui->screen_img_25, 50,50);
    lv_img_set_angle(ui->screen_img_25, 0);
    lv_obj_set_pos(ui->screen_img_25, 0, 113);
    lv_obj_set_size(ui->screen_img_25, 65, 38);

    //Write style for screen_img_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_25, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_21
    ui->screen_label_21 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_21, "50");
    lv_label_set_long_mode(ui->screen_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_21, 24, 20);
    lv_obj_set_size(ui->screen_label_21, 15, 17);

    //Write style for screen_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_21, lv_color_hex(0x2bc39c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_21, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_22
    ui->screen_label_22 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_22, "flow x10/ml");
    lv_label_set_long_mode(ui->screen_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_22, 3, 37);
    lv_obj_set_size(ui->screen_label_22, 57, 11);

    //Write style for screen_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_22, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_22, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_23
    ui->screen_label_23 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_23, "7");
    lv_label_set_long_mode(ui->screen_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_23, 28, 69);
    lv_obj_set_size(ui->screen_label_23, 7, 17);

    //Write style for screen_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_23, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_23, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_23, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_24
    ui->screen_label_24 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_24, "time/s");
    lv_label_set_long_mode(ui->screen_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_24, 16, 86);
    lv_obj_set_size(ui->screen_label_24, 32, 11);

    //Write style for screen_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_24, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_24, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_24, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_25
    ui->screen_label_25 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_25, "32");
    lv_label_set_long_mode(ui->screen_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_25, 23, 118);
    lv_obj_set_size(ui->screen_label_25, 16, 17);

    //Write style for screen_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_25, lv_color_hex(0xff6bb1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_25, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_25, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_26
    ui->screen_label_26 = lv_label_create(ui->screen_cont_1);
    lv_label_set_text(ui->screen_label_26, "flow ml/s");
    lv_label_set_long_mode(ui->screen_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_26, 9, 135);
    lv_obj_set_size(ui->screen_label_26, 46, 11);

    //Write style for screen_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_26, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_26, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_26, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_chart_1
    ui->screen_chart_1 = lv_chart_create(ui->screen_cont_1);
    lv_chart_set_type(ui->screen_chart_1, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->screen_chart_1, 6, 2);
    lv_chart_set_point_count(ui->screen_chart_1, 5);
    lv_chart_set_range(ui->screen_chart_1, LV_CHART_AXIS_PRIMARY_Y, 0, 10);
    lv_chart_set_axis_tick(ui->screen_chart_1, LV_CHART_AXIS_PRIMARY_Y, 1, 1, 6, 1, true, 40);
    lv_chart_set_range(ui->screen_chart_1, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
    lv_chart_set_axis_tick(ui->screen_chart_1, LV_CHART_AXIS_PRIMARY_X, 1, 1, 5, 1, true, 40);
    lv_chart_set_zoom_x(ui->screen_chart_1, 256);
    lv_chart_set_zoom_y(ui->screen_chart_1, 256);
    ui->screen_chart_1_0 = lv_chart_add_series(ui->screen_chart_1, lv_color_hex(0xff6bb1), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->screen_chart_1, ui->screen_chart_1_0, 1);
    lv_chart_set_next_value(ui->screen_chart_1, ui->screen_chart_1_0, 2);
    lv_chart_set_next_value(ui->screen_chart_1, ui->screen_chart_1_0, 4);
    lv_chart_set_next_value(ui->screen_chart_1, ui->screen_chart_1_0, 6);
    lv_chart_set_next_value(ui->screen_chart_1, ui->screen_chart_1_0, 1);
#endif
    lv_obj_set_pos(ui->screen_chart_1, 78, 15);
    lv_obj_set_size(ui->screen_chart_1, 186, 125);
    lv_obj_set_scrollbar_mode(ui->screen_chart_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_chart_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->screen_chart_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_chart_1, lv_color_hex(0xe8e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_chart_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_chart_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_chart_1, lv_color_hex(0x151212), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_chart_1, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_chart_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->screen_chart_1, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_chart_1, lv_color_hex(0xe8e8e8), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_chart_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write codes screen_btn_coffee1
    ui->screen_btn_coffee1 = lv_btn_create(ui->screen);
    ui->screen_btn_coffee1_label = lv_label_create(ui->screen_btn_coffee1);
    lv_label_set_text(ui->screen_btn_coffee1_label, "");
    lv_label_set_long_mode(ui->screen_btn_coffee1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_coffee1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_coffee1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_coffee1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_coffee1, 8, 51);
    lv_obj_set_size(ui->screen_btn_coffee1, 104, 100);

    //Write style for screen_btn_coffee1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_coffee1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_coffee1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_coffee1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_coffee1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_coffee1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_coffee1, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_coffee1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_coffee1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_coffee3
    ui->screen_btn_coffee3 = lv_btn_create(ui->screen);
    ui->screen_btn_coffee3_label = lv_label_create(ui->screen_btn_coffee3);
    lv_label_set_text(ui->screen_btn_coffee3_label, "");
    lv_label_set_long_mode(ui->screen_btn_coffee3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_coffee3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_coffee3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_coffee3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_coffee3, 8, 160);
    lv_obj_set_size(ui->screen_btn_coffee3, 104, 100);

    //Write style for screen_btn_coffee3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_coffee3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_coffee3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_coffee3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_coffee3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_coffee3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_coffee3, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_coffee3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_coffee3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_coffee2
    ui->screen_btn_coffee2 = lv_btn_create(ui->screen);
    ui->screen_btn_coffee2_label = lv_label_create(ui->screen_btn_coffee2);
    lv_label_set_text(ui->screen_btn_coffee2_label, "");
    lv_label_set_long_mode(ui->screen_btn_coffee2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_coffee2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_coffee2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_coffee2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_coffee2, 368, 51);
    lv_obj_set_size(ui->screen_btn_coffee2, 104, 100);

    //Write style for screen_btn_coffee2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_coffee2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_coffee2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_coffee2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_coffee2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_coffee2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_coffee2, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_coffee2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_coffee2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_coffee4
    ui->screen_btn_coffee4 = lv_btn_create(ui->screen);
    ui->screen_btn_coffee4_label = lv_label_create(ui->screen_btn_coffee4);
    lv_label_set_text(ui->screen_btn_coffee4_label, "");
    lv_label_set_long_mode(ui->screen_btn_coffee4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_coffee4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_coffee4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_coffee4_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_coffee4, 368, 160);
    lv_obj_set_size(ui->screen_btn_coffee4, 104, 100);

    //Write style for screen_btn_coffee4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_coffee4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_coffee4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_coffee4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_coffee4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_coffee4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_coffee4, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_coffee4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_coffee4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_cancel
    ui->screen_btn_cancel = lv_btn_create(ui->screen);
    ui->screen_btn_cancel_label = lv_label_create(ui->screen_btn_cancel);
    lv_label_set_text(ui->screen_btn_cancel_label, "");
    lv_label_set_long_mode(ui->screen_btn_cancel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_cancel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_cancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_cancel_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_cancel, 293, 221);
    lv_obj_set_size(ui->screen_btn_cancel, 38, 38);
    lv_obj_add_flag(ui->screen_btn_cancel,LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_cancel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_cancel, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_menu
    ui->screen_btn_menu = lv_btn_create(ui->screen);
    ui->screen_btn_menu_label = lv_label_create(ui->screen_btn_menu);
    lv_label_set_text(ui->screen_btn_menu_label, "");
    lv_label_set_long_mode(ui->screen_btn_menu_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_menu_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_menu, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_menu_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_menu, 457, 9);
    lv_obj_set_size(ui->screen_btn_menu, 15, 15);

    //Write style for screen_btn_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_menu, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_menu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_menu, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_menu, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    #if (LEFT_OR_COFFEE == RIGHT)

    #endif

    //Write codes screen_btnm_choosemode
    ui->screen_btnm_choosemode = lv_btnmatrix_create(ui->screen);
    static const char *screen_btnm_choosemode_text_map[] = {"咖啡萃取", "茶饮萃取", "",};
    lv_btnmatrix_set_map(ui->screen_btnm_choosemode, screen_btnm_choosemode_text_map);
    lv_obj_set_pos(ui->screen_btnm_choosemode, 156, 48);
    lv_obj_set_size(ui->screen_btnm_choosemode, 170, 25);
    // lv_obj_add_flag(ui->screen_btnm_choosemode, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_btnm_choosemode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_btnm_choosemode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_btnm_choosemode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_btnm_choosemode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_btnm_choosemode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_btnm_choosemode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->screen_btnm_choosemode, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->screen_btnm_choosemode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btnm_choosemode, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_btnm_choosemode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btnm_choosemode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btnm_choosemode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_btnm_choosemode, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_btnm_choosemode, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_btnm_choosemode, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_btnm_choosemode, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_btnm_choosemode, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btnm_choosemode, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btnm_choosemode, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btnm_choosemode, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btnm_choosemode, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_btnm_choosemode, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btnm_choosemode, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btnm_choosemode, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btnm_choosemode, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
    /* 高亮态（被选中） */
    lv_obj_set_style_bg_color(ui->screen_btnm_choosemode,lv_color_hex(0x2195f6),LV_PART_ITEMS | LV_STATE_CHECKED);// 高亮蓝
    lv_obj_set_style_text_color(ui->screen_btnm_choosemode,lv_color_hex(0xFFFFFF),LV_PART_ITEMS | LV_STATE_CHECKED);
    /* 未选中态（灰） */
    lv_obj_set_style_bg_color(ui->screen_btnm_choosemode,lv_color_hex(0xC9C9C9),LV_PART_ITEMS | LV_STATE_DEFAULT);// 灰色
    lv_obj_set_style_text_color(ui->screen_btnm_choosemode,lv_color_hex(0x333333),LV_PART_ITEMS | LV_STATE_DEFAULT);// 深灰字

    //Write codes screen_img_tea1
    ui->screen_img_tea1 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_tea1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_tea1, &_1tea_alpha_25x45);
    lv_img_set_pivot(ui->screen_img_tea1, 50,50);
    lv_img_set_angle(ui->screen_img_tea1, 0);
    lv_obj_set_pos(ui->screen_img_tea1, 48, 71);
    lv_obj_set_size(ui->screen_img_tea1, 25, 45);

    //Write style for screen_img_tea1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_tea1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_tea1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_tea1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_tea1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_tea2
    ui->screen_img_tea2 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_tea2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_tea2, &_2tea_alpha_25x47);
    lv_img_set_pivot(ui->screen_img_tea2, 50,50);
    lv_img_set_angle(ui->screen_img_tea2, 0);
    lv_obj_set_pos(ui->screen_img_tea2, 408, 69);
    lv_obj_set_size(ui->screen_img_tea2, 25, 47);

    //Write style for screen_img_tea2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_tea2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_tea2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_tea2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_tea2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_tea3
    ui->screen_img_tea3 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_tea3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_tea3, &_3tea_alpha_25x47);
    lv_img_set_pivot(ui->screen_img_tea3, 50,50);
    lv_img_set_angle(ui->screen_img_tea3, 0);
    lv_obj_set_pos(ui->screen_img_tea3, 48, 178);
    lv_obj_set_size(ui->screen_img_tea3, 25, 47);

    //Write style for screen_img_tea3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_tea3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_tea3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_tea3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_tea3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_tea4
    ui->screen_img_tea4 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_tea4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_tea4, &_4tea_alpha_24x44);
    lv_img_set_pivot(ui->screen_img_tea4, 50,50);
    lv_img_set_angle(ui->screen_img_tea4, 0);
    lv_obj_set_pos(ui->screen_img_tea4, 408, 181);
    lv_obj_set_size(ui->screen_img_tea4, 24, 44);

    //Write style for screen_img_tea4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_tea4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_tea4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_tea4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_tea4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_cont_M
    ui->screen_cont_M = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_M, 121, 207);
    lv_obj_set_size(ui->screen_cont_M, 238, 53);
    lv_obj_set_scrollbar_mode(ui->screen_cont_M, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_M, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_M, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_M, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_M, lv_color_hex(0xefebe6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_M, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_M, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_20
    ui->screen_img_20 = lv_img_create(ui->screen_cont_M);
    lv_obj_add_flag(ui->screen_img_20, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_20, &_steam_alpha_27x32);
    lv_img_set_pivot(ui->screen_img_20, 50,50);
    lv_img_set_angle(ui->screen_img_20, 0);
    lv_obj_set_pos(ui->screen_img_20, 20, 11);
    lv_obj_set_size(ui->screen_img_20, 27, 32);

    //Write style for screen_img_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_20, true, LV_PART_MAIN|LV_STATE_DEFAULT);
#if (LEFT_OR_COFFEE == LEFT)
    //Write codes screen_img_hotwater
    ui->screen_img_hotwater = lv_img_create(ui->screen_cont_M);
    lv_obj_add_flag(ui->screen_img_hotwater, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_hotwater, &_hotwater24_alpha_30x37);
    lv_img_set_pivot(ui->screen_img_hotwater, 50,50);
    lv_img_set_angle(ui->screen_img_hotwater, 0);
    lv_obj_set_pos(ui->screen_img_hotwater, 188, 8);
    lv_obj_set_size(ui->screen_img_hotwater, 30, 37);

    //Write style for screen_img_hotwater, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_hotwater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_hotwater, true, LV_PART_MAIN|LV_STATE_DEFAULT);
#endif
    //Write codes screen_img_stop
    ui->screen_img_stop = lv_img_create(ui->screen_cont_M);
    lv_obj_add_flag(ui->screen_img_stop, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_stop, &_stop_alpha_32x32);
    lv_img_set_pivot(ui->screen_img_stop, 50,50);
    lv_img_set_angle(ui->screen_img_stop, 0);
    lv_obj_set_pos(ui->screen_img_stop, 105, 11);
    lv_obj_set_size(ui->screen_img_stop, 32, 32);
    lv_obj_add_flag(ui->screen_img_stop, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_img_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_stop, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_21
    ui->screen_img_21 = lv_img_create(ui->screen_cont_M);
    lv_obj_add_flag(ui->screen_img_21, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_21, &_start_alpha_32x32);
    lv_img_set_pivot(ui->screen_img_21, 50,50);
    lv_img_set_angle(ui->screen_img_21, 0);
    lv_obj_set_pos(ui->screen_img_21, 105, 11);
    lv_obj_set_size(ui->screen_img_21, 32, 32);

    //Write style for screen_img_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);
#if (LEFT_OR_COFFEE == LEFT)
    //Write codes screen_btn_hotwater
    ui->screen_btn_hotwater = lv_btn_create(ui->screen_cont_M);
    ui->screen_btn_hotwater_label = lv_label_create(ui->screen_btn_hotwater);
    lv_label_set_text(ui->screen_btn_hotwater_label, "");
    lv_label_set_long_mode(ui->screen_btn_hotwater_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_hotwater_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_hotwater, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_hotwater_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_hotwater, 174, 2);
    lv_obj_set_size(ui->screen_btn_hotwater, 60, 47);

    //Write style for screen_btn_hotwater, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_hotwater, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_hotwater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_hotwater, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_hotwater, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_hotwater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_hotwater, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
#endif
    //Write codes screen_btn_rinse
    ui->screen_btn_rinse = lv_btn_create(ui->screen_cont_M);
    ui->screen_btn_rinse_label = lv_label_create(ui->screen_btn_rinse);
    lv_label_set_text(ui->screen_btn_rinse_label, "");
    lv_label_set_long_mode(ui->screen_btn_rinse_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_rinse_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_rinse, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_rinse_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_rinse, 64, 2);
    lv_obj_set_size(ui->screen_btn_rinse, 109, 45);

    //Write style for screen_btn_rinse, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_rinse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_rinse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_rinse, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_rinse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_rinse, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_rinse, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_rinse, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_rinse, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_steam
    ui->screen_btn_steam = lv_btn_create(ui->screen_cont_M);
    ui->screen_btn_steam_label = lv_label_create(ui->screen_btn_steam);
    lv_label_set_text(ui->screen_btn_steam_label, "");
    lv_label_set_long_mode(ui->screen_btn_steam_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_steam_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_steam, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_steam_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_steam, 4, 2);
    lv_obj_set_size(ui->screen_btn_steam, 60, 47);

    //Write style for screen_btn_steam, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_steam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_steam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_steam, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_steam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_steam, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_steam, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_steam, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_steam, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

   //Write codes screen_btn_teaset1
    ui->screen_btn_teaset1 = lv_btn_create(ui->screen);
    ui->screen_btn_teaset1_label = lv_label_create(ui->screen_btn_teaset1);
    lv_label_set_text(ui->screen_btn_teaset1_label, "");
    lv_label_set_long_mode(ui->screen_btn_teaset1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_teaset1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_teaset1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_teaset1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_teaset1, 32, 121);
    lv_obj_set_size(ui->screen_btn_teaset1, 55, 17);

    //Write style for screen_btn_teaset1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_teaset1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_teaset1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_teaset1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_teaset1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_teaset1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_teaset1, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_teaset1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_teaset1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_teaset3
    ui->screen_btn_teaset3 = lv_btn_create(ui->screen);
    ui->screen_btn_teaset3_label = lv_label_create(ui->screen_btn_teaset3);
    lv_label_set_text(ui->screen_btn_teaset3_label, "");
    lv_label_set_long_mode(ui->screen_btn_teaset3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_teaset3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_teaset3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_teaset3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_teaset3, 32, 230);
    lv_obj_set_size(ui->screen_btn_teaset3, 55, 17);

    //Write style for screen_btn_teaset3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_teaset3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_teaset3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_teaset3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_teaset3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_teaset3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_teaset3, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_teaset3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_teaset3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_teaset2
    ui->screen_btn_teaset2 = lv_btn_create(ui->screen);
    ui->screen_btn_teaset2_label = lv_label_create(ui->screen_btn_teaset2);
    lv_label_set_text(ui->screen_btn_teaset2_label, "");
    lv_label_set_long_mode(ui->screen_btn_teaset2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_teaset2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_teaset2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_teaset2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_teaset2, 392, 121);
    lv_obj_set_size(ui->screen_btn_teaset2, 55, 17);

    //Write style for screen_btn_teaset2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_teaset2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_teaset2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_teaset2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_teaset2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_teaset2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_teaset2, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_teaset2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_teaset2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_teaset4
    ui->screen_btn_teaset4 = lv_btn_create(ui->screen);
    ui->screen_btn_teaset4_label = lv_label_create(ui->screen_btn_teaset4);
    lv_label_set_text(ui->screen_btn_teaset4_label, "");
    lv_label_set_long_mode(ui->screen_btn_teaset4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_teaset4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_teaset4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_teaset4_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_teaset4, 393, 230);
    lv_obj_set_size(ui->screen_btn_teaset4, 55, 17);

    //Write style for screen_btn_teaset4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_teaset4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_teaset4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_teaset4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_teaset4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_teaset4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_teaset4, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_teaset4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_teaset4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    //Write codes screen_arc_1
    ui->screen_arc_1 = lv_arc_create(ui->screen);
    lv_arc_set_mode(ui->screen_arc_1, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->screen_arc_1, 0, 100);
    lv_arc_set_bg_angles(ui->screen_arc_1, 135, 45);
    lv_arc_set_value(ui->screen_arc_1, 0);
    lv_arc_set_rotation(ui->screen_arc_1, 0);
    lv_obj_set_pos(ui->screen_arc_1, 180, 76);
    lv_obj_set_size(ui->screen_arc_1, 120, 120);

    //Write style for screen_arc_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->screen_arc_1, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_arc_1, 149, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_arc_1, lv_color_hex(0x513c28), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_arc_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_arc_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->screen_arc_1, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_arc_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_arc_1, lv_color_hex(0xd79442), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_arc_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_arc_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_arc_1, lv_color_hex(0xd79442), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_arc_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_arc_1, 5, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui->screen_arc_1, LV_OBJ_FLAG_CLICKABLE);

   //Write codes screen_cont_teaset
    ui->screen_cont_teaset = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_teaset, 121, 27);
    lv_obj_set_size(ui->screen_cont_teaset, 234, 231);
    lv_obj_set_scrollbar_mode(ui->screen_cont_teaset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_cont_teaset, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_cont_teaset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_cont_teaset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_teaset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_teaset, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_cont_teaset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_teaset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_teaset, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_teaset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_teaset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_teaset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_teaset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_teaset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_teaset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_teaset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_startime
    ui->screen_label_startime = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_startime, "运行时间");
    lv_label_set_long_mode(ui->screen_label_startime, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_startime, 69, 5);
    lv_obj_set_size(ui->screen_label_startime, 50, 20);

    //Write style for screen_label_startime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_startime, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_startime, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_startime, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_startime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_startime, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_startime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_suspendtime
    ui->screen_label_suspendtime = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_suspendtime, "暂停时间");
    lv_label_set_long_mode(ui->screen_label_suspendtime, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_suspendtime, 160, 5);
    lv_obj_set_size(ui->screen_label_suspendtime, 50, 20);

    //Write style for screen_label_suspendtime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_suspendtime, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_suspendtime, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_suspendtime, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_suspendtime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_suspendtime, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_suspendtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_one
    ui->screen_label_one = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_one, "1");
    lv_label_set_long_mode(ui->screen_label_one, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_one, 4, 25);
    lv_obj_set_size(ui->screen_label_one, 48, 30);

    //Write style for screen_label_one, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_one, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_one, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_one, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_one, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_one, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_one, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_two
    ui->screen_label_two = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_two, "2");
    lv_label_set_long_mode(ui->screen_label_two, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_two, 4, 60);
    lv_obj_set_size(ui->screen_label_two, 48, 30);

    //Write style for screen_label_two, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_two, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_two, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_two, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_two, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_two, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_two, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_three
    ui->screen_label_three = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_three, "3");
    lv_label_set_long_mode(ui->screen_label_three, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_three, 4, 95);
    lv_obj_set_size(ui->screen_label_three, 48, 30);

    //Write style for screen_label_three, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_three, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_three, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_three, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_three, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_three, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_three, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_four
    ui->screen_label_four = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_four, "4");
    lv_label_set_long_mode(ui->screen_label_four, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_four, 4, 130);
    lv_obj_set_size(ui->screen_label_four, 48, 30);

    //Write style for screen_label_four, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_four, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_four, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_four, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_four, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_four, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_four, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_five
    ui->screen_label_five = lv_label_create(ui->screen_cont_teaset);
    lv_label_set_text(ui->screen_label_five, "5");
    lv_label_set_long_mode(ui->screen_label_five, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_five, 4, 165);
    lv_obj_set_size(ui->screen_label_five, 48, 30);

    //Write style for screen_label_five, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_five, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_five, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_five, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_five, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_five, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_five, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ta_1stepoff
    ui->screen_ta_1stepoff = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_1stepoff, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_1stepoff, "");
    lv_textarea_set_password_bullet(ui->screen_ta_1stepoff, "*");
    lv_textarea_set_password_mode(ui->screen_ta_1stepoff, false);
    lv_textarea_set_one_line(ui->screen_ta_1stepoff, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_1stepoff, "");
    lv_textarea_set_max_length(ui->screen_ta_1stepoff, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_1stepoff, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_1stepoff, 160, 25);
    lv_obj_set_size(ui->screen_ta_1stepoff, 50, 30);

    //Write style for screen_ta_1stepoff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_1stepoff, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_1stepoff, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_1stepoff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_1stepoff, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_1stepoff, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_1stepoff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_1stepoff, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_1stepoff, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_1stepoff, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_1stepoff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_1stepoff, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_1stepoff, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_1stepoff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_1stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_1stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_1stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_1stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_1stepoff, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_1stepoff, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_1stepoff, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_1stepoff, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_1stepoff, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_1stepon
    ui->screen_ta_1stepon = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_1stepon, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_1stepon, "");
    lv_textarea_set_password_bullet(ui->screen_ta_1stepon, "*");
    lv_textarea_set_password_mode(ui->screen_ta_1stepon, false);
    lv_textarea_set_one_line(ui->screen_ta_1stepon, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_1stepon, "");
    lv_textarea_set_max_length(ui->screen_ta_1stepon, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_1stepon, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_1stepon, 69, 25);
    lv_obj_set_size(ui->screen_ta_1stepon, 50, 30);

    //Write style for screen_ta_1stepon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_1stepon, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_1stepon, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_1stepon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_1stepon, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_1stepon, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_1stepon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_1stepon, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_1stepon, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_1stepon, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_1stepon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_1stepon, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_1stepon, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_1stepon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_1stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_1stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_1stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_1stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_1stepon, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_1stepon, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_1stepon, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_1stepon, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_1stepon, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_2stepon
    ui->screen_ta_2stepon = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_2stepon, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_2stepon, "");
    lv_textarea_set_password_bullet(ui->screen_ta_2stepon, "*");
    lv_textarea_set_password_mode(ui->screen_ta_2stepon, false);
    lv_textarea_set_one_line(ui->screen_ta_2stepon, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_2stepon, "");
    lv_textarea_set_max_length(ui->screen_ta_2stepon, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_2stepon, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_2stepon, 69, 60);
    lv_obj_set_size(ui->screen_ta_2stepon, 50, 30);

    //Write style for screen_ta_2stepon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_2stepon, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_2stepon, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_2stepon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_2stepon, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_2stepon, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_2stepon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_2stepon, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_2stepon, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_2stepon, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_2stepon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_2stepon, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_2stepon, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_2stepon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_2stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_2stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_2stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_2stepon, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_2stepon, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_2stepon, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_2stepon, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_2stepon, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_2stepon, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_2stepoff
    ui->screen_ta_2stepoff = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_2stepoff, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_2stepoff, "");
    lv_textarea_set_password_bullet(ui->screen_ta_2stepoff, "*");
    lv_textarea_set_password_mode(ui->screen_ta_2stepoff, false);
    lv_textarea_set_one_line(ui->screen_ta_2stepoff, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_2stepoff, "");
    lv_textarea_set_max_length(ui->screen_ta_2stepoff, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_2stepoff, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_2stepoff, 160, 60);
    lv_obj_set_size(ui->screen_ta_2stepoff, 50, 30);

    //Write style for screen_ta_2stepoff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_2stepoff, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_2stepoff, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_2stepoff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_2stepoff, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_2stepoff, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_2stepoff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_2stepoff, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_2stepoff, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_2stepoff, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_2stepoff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_2stepoff, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_2stepoff, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_2stepoff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_2stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_2stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_2stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_2stepoff, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_2stepoff, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_2stepoff, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_2stepoff, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_2stepoff, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_2stepoff, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_3
    ui->screen_ta_3 = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_3, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_3, "");
    lv_textarea_set_password_bullet(ui->screen_ta_3, "*");
    lv_textarea_set_password_mode(ui->screen_ta_3, false);
    lv_textarea_set_one_line(ui->screen_ta_3, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_3, "");
    lv_textarea_set_max_length(ui->screen_ta_3, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_3, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_3, 69, 95);
    lv_obj_set_size(ui->screen_ta_3, 50, 30);

    //Write style for screen_ta_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_3, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_3, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_3, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_3, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_3, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_3, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_3, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_4
    ui->screen_ta_4 = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_4, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_4, "");
    lv_textarea_set_password_bullet(ui->screen_ta_4, "*");
    lv_textarea_set_password_mode(ui->screen_ta_4, false);
    lv_textarea_set_one_line(ui->screen_ta_4, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_4, "");
    lv_textarea_set_max_length(ui->screen_ta_4, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_4, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_4, 69, 130);
    lv_obj_set_size(ui->screen_ta_4, 50, 30);

    //Write style for screen_ta_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_4, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_4, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_4, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_4, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_4, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_4, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_4, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_5
    ui->screen_ta_5 = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_5, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_5, "");
    lv_textarea_set_password_bullet(ui->screen_ta_5, "*");
    lv_textarea_set_password_mode(ui->screen_ta_5, false);
    lv_textarea_set_one_line(ui->screen_ta_5, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_5, "");
    lv_textarea_set_max_length(ui->screen_ta_5, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_5, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_5, 69, 165);
    lv_obj_set_size(ui->screen_ta_5, 50, 30);

    //Write style for screen_ta_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_5, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_5, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_5, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_5, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_5, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_5, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_5, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_6
    ui->screen_ta_6 = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_6, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_6, "");
    lv_textarea_set_password_bullet(ui->screen_ta_6, "*");
    lv_textarea_set_password_mode(ui->screen_ta_6, false);
    lv_textarea_set_one_line(ui->screen_ta_6, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_6, "");
    lv_textarea_set_max_length(ui->screen_ta_6, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_6, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_6, 160, 95);
    lv_obj_set_size(ui->screen_ta_6, 50, 30);

    //Write style for screen_ta_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_6, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_6, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_6, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_6, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_6, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_6, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_6, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_7
    ui->screen_ta_7 = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_7, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_7, "");
    lv_textarea_set_password_bullet(ui->screen_ta_7, "*");
    lv_textarea_set_password_mode(ui->screen_ta_7, false);
    lv_textarea_set_one_line(ui->screen_ta_7, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_7, "");
    lv_textarea_set_max_length(ui->screen_ta_7, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_7, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_7, 160, 130);
    lv_obj_set_size(ui->screen_ta_7, 50, 30);

    //Write style for screen_ta_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_7, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_7, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_7, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_7, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_7, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_7, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_7, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_ta_8
    ui->screen_ta_8 = lv_textarea_create(ui->screen_cont_teaset);
    lv_textarea_set_text(ui->screen_ta_8, "");
    lv_textarea_set_placeholder_text(ui->screen_ta_8, "");
    lv_textarea_set_password_bullet(ui->screen_ta_8, "*");
    lv_textarea_set_password_mode(ui->screen_ta_8, false);
    lv_textarea_set_one_line(ui->screen_ta_8, false);
    lv_textarea_set_accepted_chars(ui->screen_ta_8, "");
    lv_textarea_set_max_length(ui->screen_ta_8, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_ta_8, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_ta_8, 160, 165);
    lv_obj_set_size(ui->screen_ta_8, 50, 30);

    //Write style for screen_ta_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ta_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ta_8, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ta_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ta_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ta_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ta_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ta_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_ta_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_ta_8, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_ta_8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ta_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ta_8, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ta_8, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ta_8, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ta_8, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ta_8, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_btn_save
    ui->screen_btn_save = lv_btn_create(ui->screen_cont_teaset);
    ui->screen_btn_save_label = lv_label_create(ui->screen_btn_save);
    lv_label_set_text(ui->screen_btn_save_label, "保存");
    lv_label_set_long_mode(ui->screen_btn_save_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_save_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_save, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_save_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_save, 144, 199);
    lv_obj_set_size(ui->screen_btn_save, 65, 23);

    //Write style for screen_btn_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btn_save, lv_color_hex(0xb1b6ba), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btn_save, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_save, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_save, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_save, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_save, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_teacancel
    ui->screen_btn_teacancel = lv_btn_create(ui->screen_cont_teaset);
    ui->screen_btn_teacancel_label = lv_label_create(ui->screen_btn_teacancel);
    lv_label_set_text(ui->screen_btn_teacancel_label, "取消");
    lv_label_set_long_mode(ui->screen_btn_teacancel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_teacancel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_teacancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_teacancel_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_teacancel, 25, 199);
    lv_obj_set_size(ui->screen_btn_teacancel, 65, 23);

    //Write style for screen_btn_teacancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_teacancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btn_teacancel, lv_color_hex(0xb1b6ba), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btn_teacancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_teacancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_teacancel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_teacancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_teacancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_teacancel, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_teacancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_teacancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

 
    //The custom code of screen.
    lv_btnmatrix_set_btn_ctrl_all(ui->screen_btnm_choosemode, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_one_checked(ui->screen_btnm_choosemode, true);
    lv_btnmatrix_set_btn_ctrl(ui->screen_btnm_choosemode, 0, LV_BTNMATRIX_CTRL_CHECKED); /* 默认A高亮 */

    char string_data[50] = {0};  
    sprintf(string_data, "%d", GrindSetData.time_1);

    char string_data1[50] = {0};  
    sprintf(string_data1, "%d", GrindSetData.time_2);

    char string_data2[50] = {0};  
    sprintf(string_data2, "%d", GrindSetData.time_3);

    char string_data3[50] = {0};  
    sprintf(string_data3, "%d", GrindSetData.time_4);

    lv_label_set_text_fmt(guider_ui.screen_label_9, "%ss", string_data);
    lv_label_set_text_fmt(guider_ui.screen_label_19, "%ss", string_data1);
    lv_label_set_text_fmt(guider_ui.screen_label_10, "%ss", string_data2);
    lv_label_set_text_fmt(guider_ui.screen_label_20, "%ss", string_data3);

    lv_obj_add_flag(ui->screen_img_tea1,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_img_tea2,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_img_tea3,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_img_tea4,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_btn_teaset1,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_btn_teaset2,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_btn_teaset3,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_btn_teaset4,LV_OBJ_FLAG_HIDDEN);
    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

    //Init events for screen.
    events_init_screen(ui);
}
