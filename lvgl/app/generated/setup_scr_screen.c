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



void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 480, 272);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x8e5757), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_1, "时间\n日期");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_1, 40, 30);
    lv_obj_set_size(ui->screen_label_1, 100, 30);

    //Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
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

    //Write codes screen_btn_3
    ui->screen_btn_3 = lv_btn_create(ui->screen);
    ui->screen_btn_3_label = lv_label_create(ui->screen_btn_3);
    lv_label_set_text(ui->screen_btn_3_label, "语言切换");
    lv_label_set_long_mode(ui->screen_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_3, 340, 30);
    lv_obj_set_size(ui->screen_btn_3, 100, 29);

    //Write style for screen_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btn_3, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_3, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_btn_3, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_btn_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_btn_4
    ui->screen_btn_4 = lv_btn_create(ui->screen);
    ui->screen_btn_4_label = lv_label_create(ui->screen_btn_4);
    lv_label_set_text(ui->screen_btn_4_label, "获取杯量");
    lv_label_set_long_mode(ui->screen_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_4, 40, 217);
    lv_obj_set_size(ui->screen_btn_4, 100, 34);

    //Write style for screen_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btn_4, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_4, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_btn_4, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_btn_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_btn_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_4, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_1
    ui->screen_bar_1 = lv_bar_create(ui->screen);
    lv_obj_set_style_anim_time(ui->screen_bar_1, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_1, 0, 100);
    lv_bar_set_value(ui->screen_bar_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_bar_1, 190, 229);
    lv_obj_set_size(ui->screen_bar_1, 225, 20);

    //Write style for screen_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_1, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_img_1
    ui->screen_img_1 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_1, &_1755657687860_alpha_100x89);
    lv_img_set_pivot(ui->screen_img_1, 50,50);
    lv_img_set_angle(ui->screen_img_1, 0);
    lv_obj_set_pos(ui->screen_img_1, 190, 3);
    lv_obj_set_size(ui->screen_img_1, 100, 89);

    //Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_imgbtn_1
    ui->screen_imgbtn_1 = lv_imgbtn_create(ui->screen);
    lv_obj_add_flag(ui->screen_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_3_alpha_100x80, NULL);
    lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_2_alpha_100x80, NULL);
    lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_4_alpha_100x80, NULL);
    lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_1_alpha_100x80, NULL);
    ui->screen_imgbtn_1_label = lv_label_create(ui->screen_imgbtn_1);
    lv_label_set_text(ui->screen_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->screen_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_imgbtn_1, 90, 110);
    lv_obj_set_size(ui->screen_imgbtn_1, 100, 80);

    //Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes screen_imgbtn_2
    ui->screen_imgbtn_2 = lv_imgbtn_create(ui->screen);
    lv_obj_add_flag(ui->screen_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_3_alpha_100x80, NULL);
    lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, &_2_alpha_100x80, NULL);
    lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_4_alpha_100x80, NULL);
    lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_1_alpha_100x80, NULL);
    ui->screen_imgbtn_2_label = lv_label_create(ui->screen_imgbtn_2);
    lv_label_set_text(ui->screen_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->screen_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_imgbtn_2, 305, 110);
    lv_obj_set_size(ui->screen_imgbtn_2, 100, 80);

    //Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

    //Init events for screen.
    events_init_screen(ui);
}
