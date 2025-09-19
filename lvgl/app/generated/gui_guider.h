/*
* Copyright 2025 NXP
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
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_img_2;
	lv_obj_t *screen_img_3;
	lv_obj_t *screen_img_4;
	lv_obj_t *screen_btn_1;
	lv_obj_t *screen_btn_1_label;
	lv_obj_t *screen_btn_2;
	lv_obj_t *screen_btn_2_label;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_btn_5;
	lv_obj_t *screen_btn_5_label;
	lv_obj_t *screen_btn_7;
	lv_obj_t *screen_btn_7_label;
	lv_obj_t *screen_img_8;
	lv_obj_t *screen_btn_4;
	lv_obj_t *screen_btn_4_label;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_label_6;
	lv_obj_t *screen_btn_11;
	lv_obj_t *screen_btn_11_label;
	lv_obj_t *screen_btn_12;
	lv_obj_t *screen_btn_12_label;
	lv_obj_t *screen_img_9;
	lv_obj_t *screen_img_10;
	lv_obj_t *screen_img_12;
	lv_obj_t *screen_btn_13;
	lv_obj_t *screen_btn_13_label;
	lv_obj_t *screen_img_11;
	lv_obj_t *screen_cont_1;
	lv_obj_t *screen_spinbox_1;
	lv_obj_t *screen_spinbox_1_btn_plus;
	lv_obj_t *screen_spinbox_1_btn_minus;
	lv_obj_t *screen_btn_14;
	lv_obj_t *screen_btn_14_label;
	lv_obj_t *screen_btn_15;
	lv_obj_t *screen_btn_15_label;
	lv_obj_t *screen_label_11;
	lv_obj_t *screen_label_12;
	lv_obj_t *screen_label_9;
	lv_obj_t *screen_label_10;
	lv_obj_t *screen_label_8;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_btn_1;
	lv_obj_t *screen_1_btn_1_label;
	lv_obj_t *screen_1_btn_2;
	lv_obj_t *screen_1_btn_2_label;
	lv_obj_t *screen_1_btn_3;
	lv_obj_t *screen_1_btn_3_label;
	lv_obj_t *g_kb_top_layer;
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
LV_IMG_DECLARE(_logo_alpha_128x30);
LV_IMG_DECLARE(_uxdb_alpha_40x40);
LV_IMG_DECLARE(_shuangfen_alpha_100x108);
LV_IMG_DECLARE(_danfen_alpha_100x108);
LV_IMG_DECLARE(_shoudonganniu_alpha_72x72);
LV_IMG_DECLARE(_chengzhong_alpha_50x50);
LV_IMG_DECLARE(_16Bjishi_alpha_50x50);
LV_IMG_DECLARE(_shezhi_alpha_40x40);
LV_IMG_DECLARE(_yuyan_alpha_40x40);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)


#ifdef __cplusplus
}
#endif
#endif
