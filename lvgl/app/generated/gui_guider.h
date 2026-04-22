/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_img_logo1;
	lv_obj_t *screen_btn_cancel;
	lv_obj_t *screen_btn_cancel_label;
	lv_obj_t *screen_btn_steam4;
	lv_obj_t *screen_btn_steam4_label;
	lv_obj_t *screen_btn_steam3;
	lv_obj_t *screen_btn_steam3_label;
	lv_obj_t *screen_btn_steam2;
	lv_obj_t *screen_btn_steam2_label;
	lv_obj_t *screen_btn_rinse;
	lv_obj_t *screen_btn_rinse_label;
	lv_obj_t *screen_label_temp;
	lv_obj_t *screen_img_celsius;
	lv_obj_t *screen_img_menu;
	lv_obj_t *screen_btn_menu;
	lv_obj_t *screen_btn_menu_label;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_btn_back;
	lv_obj_t *screen_1_btn_back_label;
	lv_obj_t *screen_1_menu;
	lv_obj_t *screen_1_menu_tab_1;
	lv_obj_t *screen_1_menu_tab_2;
	lv_obj_t *screen_1_label_boilertemp;
	lv_obj_t *screen_1_label_set;
	lv_obj_t *screen_1_btn_set;
	lv_obj_t *screen_1_btn_set_label;
	lv_obj_t *screen_1_btn_settime1;
	lv_obj_t *screen_1_btn_settime1_label;
	lv_obj_t *screen_1_btn_settime2;
	lv_obj_t *screen_1_btn_settime2_label;
	lv_obj_t *screen_1_btn_settime3;
	lv_obj_t *screen_1_btn_settime3_label;
	lv_obj_t *screen_1_label_time1;
	lv_obj_t *screen_1_label_time2;
	lv_obj_t *screen_1_label_time3;
	lv_obj_t *screen_1_cont_set;
	lv_obj_t *screen_1_spinbox_set;
	lv_obj_t *screen_1_spinbox_set_btn_plus;
	lv_obj_t *screen_1_spinbox_set_btn_minus;
	lv_obj_t *screen_1_btn_certain;
	lv_obj_t *screen_1_btn_certain_label;
	lv_obj_t *screen_1_btn_cancel;
	lv_obj_t *screen_1_btn_cancel_label;
	lv_obj_t *screen_1_btn_descale;
	lv_obj_t *screen_1_btn_descale_label;
	lv_obj_t *screen_1_btn_waterempty;
	lv_obj_t *screen_1_btn_waterempty_label;
	lv_obj_t *screen_1_btn_waterchange;
	lv_obj_t *screen_1_btn_waterchange_label;
	lv_obj_t *screen_1_cont_matain;
	lv_obj_t *screen_1_label_hint;
	lv_obj_t *screen_1_btn_maintenancecancellation;
	lv_obj_t *screen_1_btn_maintenancecancellation_label;
	lv_obj_t *screen_1_btn_maintenancebegins;
	lv_obj_t *screen_1_btn_maintenancebegins_label;
	lv_obj_t *screen_1_bar_maintain;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);
LV_IMG_DECLARE(_loge_alpha_200x60);
LV_IMG_DECLARE(_sheshidu_alpha_10x10);
LV_IMG_DECLARE(_shezhi_alpha_34x31);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)


#ifdef __cplusplus
}
#endif
#endif
