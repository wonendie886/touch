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

    //Write codes screen_1_menu_1
    ui->screen_1_menu_1 = lv_menu_create(ui->screen_1);

    //Create sidebar page for menu screen_1_menu_1
    ui->screen_1_menu_1_sidebar_page = lv_menu_page_create(ui->screen_1_menu_1, "菜单");
    lv_menu_set_sidebar_page(ui->screen_1_menu_1, ui->screen_1_menu_1_sidebar_page);
    lv_obj_set_scrollbar_mode(ui->screen_1_menu_1_sidebar_page, LV_SCROLLBAR_MODE_OFF);

    //Create subpage for screen_1_menu_1
    ui->screen_1_menu_1_subpage_1 = lv_menu_page_create(ui->screen_1_menu_1, NULL);
    ui->screen_1_menu_1_cont_1 = lv_menu_cont_create(ui->screen_1_menu_1_sidebar_page);
    ui->screen_1_menu_1_label_1 = lv_label_create(ui->screen_1_menu_1_cont_1);
    lv_label_set_text(ui->screen_1_menu_1_label_1, "设置");
    lv_obj_set_size(ui->screen_1_menu_1_label_1, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->screen_1_menu_1_subpage_1, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->screen_1_menu_1, ui->screen_1_menu_1_cont_1, ui->screen_1_menu_1_subpage_1);

    //Create subpage for screen_1_menu_1
    ui->screen_1_menu_1_subpage_2 = lv_menu_page_create(ui->screen_1_menu_1, NULL);
    ui->screen_1_menu_1_cont_2 = lv_menu_cont_create(ui->screen_1_menu_1_sidebar_page);
    ui->screen_1_menu_1_label_2 = lv_label_create(ui->screen_1_menu_1_cont_2);
    lv_label_set_text(ui->screen_1_menu_1_label_2, "维护");
    lv_obj_set_size(ui->screen_1_menu_1_label_2, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->screen_1_menu_1_subpage_2, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->screen_1_menu_1, ui->screen_1_menu_1_cont_2, ui->screen_1_menu_1_subpage_2);

    //Create subpage for screen_1_menu_1
    ui->screen_1_menu_1_subpage_3 = lv_menu_page_create(ui->screen_1_menu_1, NULL);
    ui->screen_1_menu_1_cont_3 = lv_menu_cont_create(ui->screen_1_menu_1_sidebar_page);
    ui->screen_1_menu_1_label_3 = lv_label_create(ui->screen_1_menu_1_cont_3);
    lv_label_set_text(ui->screen_1_menu_1_label_3, "密码");
    lv_obj_set_size(ui->screen_1_menu_1_label_3, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->screen_1_menu_1_subpage_3, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->screen_1_menu_1, ui->screen_1_menu_1_cont_3, ui->screen_1_menu_1_subpage_3);
    lv_event_send(ui->screen_1_menu_1_cont_1, LV_EVENT_CLICKED, NULL);
    lv_obj_set_pos(ui->screen_1_menu_1, 0, 0);
    lv_obj_set_size(ui->screen_1_menu_1, 480, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_menu_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_menu_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_1_menu_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_menu_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_menu_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_menu_1_extra_sidebar_page_main_default
    static lv_style_t style_screen_1_menu_1_extra_sidebar_page_main_default;
    ui_init_style(&style_screen_1_menu_1_extra_sidebar_page_main_default);

    lv_style_set_bg_opa(&style_screen_1_menu_1_extra_sidebar_page_main_default, 72);
    lv_style_set_bg_color(&style_screen_1_menu_1_extra_sidebar_page_main_default, lv_color_hex(0xdaf2f8));
    lv_style_set_bg_grad_dir(&style_screen_1_menu_1_extra_sidebar_page_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_screen_1_menu_1_extra_sidebar_page_main_default, 0);
    lv_obj_add_style(ui->screen_1_menu_1_sidebar_page, &style_screen_1_menu_1_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_menu_1_extra_option_btns_main_default
    static lv_style_t style_screen_1_menu_1_extra_option_btns_main_default;
    ui_init_style(&style_screen_1_menu_1_extra_option_btns_main_default);

    lv_style_set_text_color(&style_screen_1_menu_1_extra_option_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_menu_1_extra_option_btns_main_default, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_screen_1_menu_1_extra_option_btns_main_default, 255);
    lv_style_set_text_align(&style_screen_1_menu_1_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_screen_1_menu_1_extra_option_btns_main_default, 10);
    lv_style_set_pad_bottom(&style_screen_1_menu_1_extra_option_btns_main_default, 10);
    lv_obj_add_style(ui->screen_1_menu_1_cont_3, &style_screen_1_menu_1_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_menu_1_cont_2, &style_screen_1_menu_1_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_menu_1_cont_1, &style_screen_1_menu_1_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_1_menu_1_extra_option_btns_main_checked
    static lv_style_t style_screen_1_menu_1_extra_option_btns_main_checked;
    ui_init_style(&style_screen_1_menu_1_extra_option_btns_main_checked);

    lv_style_set_bg_opa(&style_screen_1_menu_1_extra_option_btns_main_checked, 60);
    lv_style_set_bg_color(&style_screen_1_menu_1_extra_option_btns_main_checked, lv_color_hex(0x00e0b8));
    lv_style_set_bg_grad_dir(&style_screen_1_menu_1_extra_option_btns_main_checked, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_menu_1_extra_option_btns_main_checked, 0);
    lv_style_set_radius(&style_screen_1_menu_1_extra_option_btns_main_checked, 0);
    lv_style_set_text_color(&style_screen_1_menu_1_extra_option_btns_main_checked, lv_color_hex(0x9ab700));
    lv_style_set_text_font(&style_screen_1_menu_1_extra_option_btns_main_checked, &lv_font_SourceHanSerifSC_Regular_12);
    lv_style_set_text_opa(&style_screen_1_menu_1_extra_option_btns_main_checked, 255);
    lv_style_set_text_align(&style_screen_1_menu_1_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_style(ui->screen_1_menu_1_cont_3, &style_screen_1_menu_1_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->screen_1_menu_1_cont_2, &style_screen_1_menu_1_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->screen_1_menu_1_cont_1, &style_screen_1_menu_1_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_menu_1_extra_main_title_main_default
    static lv_style_t style_screen_1_menu_1_extra_main_title_main_default;
    ui_init_style(&style_screen_1_menu_1_extra_main_title_main_default);

    lv_style_set_bg_opa(&style_screen_1_menu_1_extra_main_title_main_default, 71);
    lv_style_set_bg_color(&style_screen_1_menu_1_extra_main_title_main_default, lv_color_hex(0xdaf2f8));
    lv_style_set_bg_grad_dir(&style_screen_1_menu_1_extra_main_title_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_text_color(&style_screen_1_menu_1_extra_main_title_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_menu_1_extra_main_title_main_default, &lv_font_SourceHanSerifSC_Regular_16);
    lv_style_set_text_opa(&style_screen_1_menu_1_extra_main_title_main_default, 255);
    lv_style_set_text_align(&style_screen_1_menu_1_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_screen_1_menu_1_extra_main_title_main_default, 0);
    lv_style_set_pad_bottom(&style_screen_1_menu_1_extra_main_title_main_default, 0);
    lv_menu_t * screen_1_menu_1_menu= (lv_menu_t *)ui->screen_1_menu_1;
    lv_obj_t * screen_1_menu_1_title = screen_1_menu_1_menu->sidebar_header_title;
    lv_obj_set_size(screen_1_menu_1_title, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_style(lv_menu_get_sidebar_header(ui->screen_1_menu_1), &style_screen_1_menu_1_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

#if (LEFT_OR_COFFEE == RIGHT)
    lv_obj_add_flag(ui->screen_1_menu_1_cont_2,LV_OBJ_FLAG_HIDDEN);
#endif



    //Write codes screen_1_btn_descale
    ui->screen_1_btn_descale = lv_btn_create(ui->screen_1_menu_1_subpage_2);
    ui->screen_1_btn_descale_label = lv_label_create(ui->screen_1_btn_descale);
    lv_label_set_text(ui->screen_1_btn_descale_label, "除垢");
    lv_label_set_long_mode(ui->screen_1_btn_descale_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_descale_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_descale, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_descale_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_descale, 117, 94);
    lv_obj_set_size(ui->screen_1_btn_descale, 100, 40);

    //Write style for screen_1_btn_descale, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_descale, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_descale, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_descale, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_descale, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_descale, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_descale, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_descale, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_descale, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_descale, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_descale, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_descale, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_1
    ui->screen_1_label_1 = lv_label_create(ui->screen_1_menu_1_subpage_2);
    lv_label_set_text(ui->screen_1_label_1, "Label");
    lv_label_set_long_mode(ui->screen_1_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_1, 190, 120);
    lv_obj_set_size(ui->screen_1_label_1, 100, 10);

    //Write style for screen_1_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_changewater
    ui->screen_1_btn_changewater = lv_btn_create(ui->screen_1_menu_1_subpage_2);
    ui->screen_1_btn_changewater_label = lv_label_create(ui->screen_1_btn_changewater);
    lv_label_set_text(ui->screen_1_btn_changewater_label, "锅炉换水");
    lv_label_set_long_mode(ui->screen_1_btn_changewater_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_changewater_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_changewater, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_changewater_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_changewater, 124, 135);
    lv_obj_set_size(ui->screen_1_btn_changewater, 100, 40);

    //Write style for screen_1_btn_changewater, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_btn_changewater, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_changewater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_changewater, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_changewater, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_changewater, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_changewater, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_changewater, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_changewater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_changewater, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_btn_changewater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_changewater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_2
    ui->screen_1_label_2 = lv_label_create(ui->screen_1_menu_1_subpage_2);
    lv_label_set_text(ui->screen_1_label_2, "Label");
    lv_label_set_long_mode(ui->screen_1_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_2, 192, 151);
    lv_obj_set_size(ui->screen_1_label_2, 100, 10);

    //Write style for screen_1_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_emptywater
    ui->screen_1_btn_emptywater = lv_btn_create(ui->screen_1_menu_1_subpage_2);
    ui->screen_1_btn_emptywater_label = lv_label_create(ui->screen_1_btn_emptywater);
    lv_label_set_text(ui->screen_1_btn_emptywater_label, "清空水路");
    lv_label_set_long_mode(ui->screen_1_btn_emptywater_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_emptywater_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_emptywater, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_emptywater_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_emptywater, 128, 146);
    lv_obj_set_size(ui->screen_1_btn_emptywater, 100, 40);

    //Write style for screen_1_btn_emptywater, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_emptywater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_emptywater, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_emptywater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_emptywater, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_emptywater, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_emptywater, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_emptywater, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_emptywater, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_emptywater, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_emptywater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_emptywater, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

#if (LEFT_OR_COFFEE == LEFT)

    //Write codes screen_1_cont_maintain
    ui->screen_1_cont_maintain = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cont_maintain, 0, 0);
    lv_obj_set_size(ui->screen_1_cont_maintain, 480, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_maintain, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_1_cont_maintain, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_cont_maintain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_cont_maintain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cont_maintain, lv_color_hex(0xfcfcfa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cont_maintain, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_maintain
    ui->screen_1_label_maintain = lv_label_create(ui->screen_1_cont_maintain);
    lv_label_set_text(ui->screen_1_label_maintain, "向水箱中加入4升除垢液，点击“确定”开始除垢。正在除垢，请注意蒸汽出口处的高温蒸汽。预计时间：30分钟。用4升清水更换水箱中的水。点击“确定”继续冲洗。用4升清水更换水箱中的水。点击“确定”继续冲洗。点击“确定”以开始锅炉水更换。将3升清水注入水箱。点击“确定”以开始锅炉水更换。更换锅炉水。注意废水盘处的水花溅出。预计时间：20分钟。切断供水。按下“确定”键以排空系统。排空水系统。注意防止废水盘处溅水。预计时间：10分钟.");
    lv_label_set_long_mode(ui->screen_1_label_maintain, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_maintain, 40, 62);
    lv_obj_set_size(ui->screen_1_label_maintain, 400, 110);

    //Write style for screen_1_label_maintain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_maintain, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_maintain, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_maintain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_maintain, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_maintain
    ui->screen_1_btn_maintain = lv_btn_create(ui->screen_1_cont_maintain);
    ui->screen_1_btn_maintain_label = lv_label_create(ui->screen_1_btn_maintain);
    lv_label_set_text(ui->screen_1_btn_maintain_label, "确定");
    lv_label_set_long_mode(ui->screen_1_btn_maintain_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_maintain_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_maintain, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_maintain_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_maintain, 288, 180);
    lv_obj_set_size(ui->screen_1_btn_maintain, 100, 50);

    //Write style for screen_1_btn_maintain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_maintain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_maintain, lv_color_hex(0x54606a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_maintain, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_maintain, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_maintain, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_maintain, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_maintain, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_maintain, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_bar_maintain
    ui->screen_1_bar_maintain = lv_bar_create(ui->screen_1_cont_maintain);
    lv_obj_set_style_anim_time(ui->screen_1_bar_maintain, 1000, 0);
    lv_bar_set_mode(ui->screen_1_bar_maintain, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_1_bar_maintain, 0, 100);
    lv_bar_set_value(ui->screen_1_bar_maintain, 0, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_1_bar_maintain, 40, 173);
    lv_obj_set_size(ui->screen_1_bar_maintain, 400, 5);

    //Write style for screen_1_bar_maintain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_1_bar_maintain, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_bar_maintain, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_bar_maintain, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_bar_maintain, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_bar_maintain, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_bar_maintain, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_1_bar_maintain, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_bar_maintain, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_bar_maintain, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_bar_maintain, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

#endif
    //Write codes screen_1_cont_setting
    ui->screen_1_cont_setting = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cont_setting, 144, 0);
    lv_obj_set_size(ui->screen_1_cont_setting, 336, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_cont_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_brewblock
    ui->screen_1_btn_brewblock = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_brewblock_label = lv_label_create(ui->screen_1_btn_brewblock);
    lv_label_set_text(ui->screen_1_btn_brewblock_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_brewblock_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_brewblock_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_brewblock, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_brewblock_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_brewblock, 150, 0);
    lv_obj_set_size(ui->screen_1_btn_brewblock, 100, 36);

    //Write style for screen_1_btn_brewblock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_brewblock, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_brewblock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_brewblock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_brewblock, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_brewblock, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_brewblock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_brewblock, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_brewblock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_brewblock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_brewblock
    ui->screen_1_label_brewblock = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_brewblock, "冲煮头(°C)");
    lv_label_set_long_mode(ui->screen_1_label_brewblock, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_brewblock, 20, 0);
    lv_obj_set_size(ui->screen_1_label_brewblock, 100, 36);

    //Write style for screen_1_label_brewblock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_brewblock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_brewblock, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_brewblock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_brewblock, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_brewblock, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_brewblock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_hotwaterset
    ui->screen_1_btn_hotwaterset = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_hotwaterset_label = lv_label_create(ui->screen_1_btn_hotwaterset);
    lv_label_set_text(ui->screen_1_btn_hotwaterset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_hotwaterset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_hotwaterset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_hotwaterset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_hotwaterset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_hotwaterset, 150, 76);
    lv_obj_set_size(ui->screen_1_btn_hotwaterset, 100, 36);

    //Write style for screen_1_btn_hotwaterset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_hotwaterset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_hotwaterset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_hotwaterset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_hotwaterset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_hotwaterset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_hotwaterset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_hotwaterset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_hotwaterset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_hotwaterset, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_hotwaterset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_hotwaterset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_hotwater
    ui->screen_1_label_hotwater = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_hotwater, "热水(s)");
    lv_label_set_long_mode(ui->screen_1_label_hotwater, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_hotwater, 20, 76);
    lv_obj_set_size(ui->screen_1_label_hotwater, 100, 36);

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

    //Write codes screen_1_btn_steamtempset
    ui->screen_1_btn_steamtempset = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_steamtempset_label = lv_label_create(ui->screen_1_btn_steamtempset);
    lv_label_set_text(ui->screen_1_btn_steamtempset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_steamtempset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_steamtempset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_steamtempset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_steamtempset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_steamtempset, 150, 76);
    lv_obj_set_size(ui->screen_1_btn_steamtempset, 100, 36);

    //Write style for screen_1_btn_steamtempset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_steamtempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_steamtempset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_steamtempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_steamtempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_steamtempset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_steamtempset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_steamtempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_steamtempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_steamtempset, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_steamtempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_steamtempset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_steamtemp
    ui->screen_1_label_steamtemp = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_steamtemp, "蒸汽锅炉(°C)");
    lv_label_set_long_mode(ui->screen_1_label_steamtemp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_steamtemp, 20, 76);
    lv_obj_set_size(ui->screen_1_label_steamtemp, 100, 36);

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

    //Write codes screen_1_btn_coffeetempset
    ui->screen_1_btn_coffeetempset = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_coffeetempset_label = lv_label_create(ui->screen_1_btn_coffeetempset);
    lv_label_set_text(ui->screen_1_btn_coffeetempset_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_coffeetempset_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_coffeetempset_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_coffeetempset, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_coffeetempset_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_coffeetempset, 150, 38);
    lv_obj_set_size(ui->screen_1_btn_coffeetempset, 100, 36);

    //Write style for screen_1_btn_coffeetempset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_coffeetempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_coffeetempset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_coffeetempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_coffeetempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_coffeetempset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_coffeetempset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_coffeetempset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_coffeetempset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_coffeetempset, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_coffeetempset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_coffeetempset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_coffeetemp
    ui->screen_1_label_coffeetemp = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_coffeetemp, "咖啡锅炉(°C)");
    lv_label_set_long_mode(ui->screen_1_label_coffeetemp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_coffeetemp, 20, 38);
    lv_obj_set_size(ui->screen_1_label_coffeetemp, 100, 36);

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

    //Write codes screen_1_btn_time1set
    ui->screen_1_btn_time1set = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_time1set_label = lv_label_create(ui->screen_1_btn_time1set);
    lv_label_set_text(ui->screen_1_btn_time1set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time1set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time1set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time1set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time1set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time1set, 150, 114);
    lv_obj_set_size(ui->screen_1_btn_time1set, 100, 36);

    //Write style for screen_1_btn_time1set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time1set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time1set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time1set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time1set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time1set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time1set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time1set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time1set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time1set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time1set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time1set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time1
    ui->screen_1_label_time1 = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_time1, "时间1");
    lv_label_set_long_mode(ui->screen_1_label_time1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time1, 20, 114);
    lv_obj_set_size(ui->screen_1_label_time1, 100, 36);

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

    //Write codes screen_1_btn_time2set
    ui->screen_1_btn_time2set = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_time2set_label = lv_label_create(ui->screen_1_btn_time2set);
    lv_label_set_text(ui->screen_1_btn_time2set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time2set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time2set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time2set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time2set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time2set, 150, 152);
    lv_obj_set_size(ui->screen_1_btn_time2set, 100, 36);

    //Write style for screen_1_btn_time2set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time2set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time2set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time2set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time2set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time2set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time2set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time2set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time2set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time2set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time2set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time2set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time2
    ui->screen_1_label_time2 = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_time2, "时间2");
    lv_label_set_long_mode(ui->screen_1_label_time2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time2, 20, 152);
    lv_obj_set_size(ui->screen_1_label_time2, 100, 36);

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

    //Write codes screen_1_btn_time3set
    ui->screen_1_btn_time3set = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_time3set_label = lv_label_create(ui->screen_1_btn_time3set);
    lv_label_set_text(ui->screen_1_btn_time3set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time3set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time3set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time3set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time3set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time3set, 150, 190);
    lv_obj_set_size(ui->screen_1_btn_time3set, 100, 36);

    //Write style for screen_1_btn_time3set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time3set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time3set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time3set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time3set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time3set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time3set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time3set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time3set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time3set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time3set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time3set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time3
    ui->screen_1_label_time3 = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_time3, "时间3");
    lv_label_set_long_mode(ui->screen_1_label_time3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time3, 20, 190);
    lv_obj_set_size(ui->screen_1_label_time3, 100, 36);

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

    //Write codes screen_1_btn_time4set
    ui->screen_1_btn_time4set = lv_btn_create(ui->screen_1_cont_setting);
    ui->screen_1_btn_time4set_label = lv_label_create(ui->screen_1_btn_time4set);
    lv_label_set_text(ui->screen_1_btn_time4set_label, "");
    lv_label_set_long_mode(ui->screen_1_btn_time4set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_time4set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_time4set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_time4set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_time4set, 150, 228);
    lv_obj_set_size(ui->screen_1_btn_time4set, 100, 36);

    //Write style for screen_1_btn_time4set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_time4set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_time4set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_btn_time4set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_btn_time4set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_btn_time4set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_time4set, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_time4set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_time4set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_time4set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_time4set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_time4set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_time4
    ui->screen_1_label_time4 = lv_label_create(ui->screen_1_cont_setting);
    lv_label_set_text(ui->screen_1_label_time4, "时间4");
    lv_label_set_long_mode(ui->screen_1_label_time4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_time4, 20, 228);
    lv_obj_set_size(ui->screen_1_label_time4, 100, 36);

    //Write style for screen_1_label_time4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_time4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_time4, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_time4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_time4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_time4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_cont_set
    ui->screen_1_cont_set = lv_obj_create(ui->screen_1_cont_setting);
    lv_obj_set_pos(ui->screen_1_cont_set, 14, 137);
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
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_montserratMedium_10, LV_PART_MAIN|LV_STATE_DEFAULT);
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

    //Write codes screen_1_btn_certain
    ui->screen_1_btn_certain = lv_btn_create(ui->screen_1_cont_set);
    ui->screen_1_btn_certain_label = lv_label_create(ui->screen_1_btn_certain);
    lv_label_set_text(ui->screen_1_btn_certain_label, "确定");
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

    //Write codes screen_1_cont_passwordset
    ui->screen_1_cont_passwordset = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cont_passwordset, 144, 0);
    lv_obj_set_size(ui->screen_1_cont_passwordset, 336, 272);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_passwordset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_1_cont_passwordset, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_cont_passwordset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_ta_passwordset
    ui->screen_1_ta_passwordset = lv_textarea_create(ui->screen_1_cont_passwordset);
    lv_textarea_set_text(ui->screen_1_ta_passwordset, "");
    lv_textarea_set_placeholder_text(ui->screen_1_ta_passwordset, "");
    lv_textarea_set_password_bullet(ui->screen_1_ta_passwordset, "*");
    lv_textarea_set_password_mode(ui->screen_1_ta_passwordset, false);
    lv_textarea_set_one_line(ui->screen_1_ta_passwordset, false);
    lv_textarea_set_accepted_chars(ui->screen_1_ta_passwordset, "");
    lv_textarea_set_max_length(ui->screen_1_ta_passwordset, 4);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->screen_1_ta_passwordset, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->screen_1_ta_passwordset, 59, 108);
    lv_obj_set_size(ui->screen_1_ta_passwordset, 111, 32);

    //Write style for screen_1_ta_passwordset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_ta_passwordset, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_ta_passwordset, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_ta_passwordset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_ta_passwordset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_ta_passwordset, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_ta_passwordset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_ta_passwordset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_ta_passwordset, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_ta_passwordset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_ta_passwordset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_ta_passwordset, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_ta_passwordset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_ta_passwordset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_ta_passwordset, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_ta_passwordset, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_ta_passwordset, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_ta_passwordset, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_ta_passwordset, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_ta_passwordset, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_ta_passwordset, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_ta_passwordset, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_ta_passwordset, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_passwordsave
    ui->screen_1_btn_passwordsave = lv_btn_create(ui->screen_1_cont_passwordset);
    ui->screen_1_btn_passwordsave_label = lv_label_create(ui->screen_1_btn_passwordsave);
    lv_label_set_text(ui->screen_1_btn_passwordsave_label, "保存");
    lv_label_set_long_mode(ui->screen_1_btn_passwordsave_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_passwordsave_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_passwordsave, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_passwordsave_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_passwordsave, 199, 106);
    lv_obj_set_size(ui->screen_1_btn_passwordsave, 100, 35);

    //Write style for screen_1_btn_passwordsave, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_passwordsave, 67, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_passwordsave, lv_color_hex(0xdaf2f8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_passwordsave, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_passwordsave, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_passwordsave, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_passwordsave, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_passwordsave, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_passwordsave, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_passwordsave, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_passwordsave, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_savesuccess
    ui->screen_1_label_savesuccess = lv_label_create(ui->screen_1_cont_passwordset);
    lv_label_set_text(ui->screen_1_label_savesuccess, "");
    lv_label_set_long_mode(ui->screen_1_label_savesuccess, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_savesuccess, 59, 84);
    lv_obj_set_size(ui->screen_1_label_savesuccess, 145, 15);

    //Write style for screen_1_label_savesuccess, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_savesuccess, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_savesuccess, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_savesuccess, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_savesuccess, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_savesuccess, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_back
    ui->screen_1_btn_back = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_back_label = lv_label_create(ui->screen_1_btn_back);
    lv_label_set_text(ui->screen_1_btn_back_label, "返回");
    lv_label_set_long_mode(ui->screen_1_btn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_back, 0, 237);
    lv_obj_set_size(ui->screen_1_btn_back, 144, 35);

    //Write style for screen_1_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_back, 71, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_back, lv_color_hex(0xdaf2f8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_back, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    
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
    lv_label_set_text_fmt(guider_ui.screen_1_btn_time4set_label, "%s", string_data3);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_coffeetempset_label, "%s", string_data5);
    lv_label_set_text_fmt(guider_ui.screen_1_btn_brewblock_label, "%s", string_data7);
    #if (LEFT_OR_COFFEE == RIGHT)
    lv_label_set_text_fmt(guider_ui.screen_1_btn_steamtempset_label, "%s", string_data4);
    lv_obj_add_flag(ui->screen_1_label_hotwater, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_1_btn_hotwaterset, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->screen_1_btn_hotwaterset_label, LV_OBJ_FLAG_HIDDEN);
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
