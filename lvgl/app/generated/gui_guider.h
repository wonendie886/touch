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
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_img_2;
	lv_obj_t *screen_img_3;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_img_4;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_img_5;
	lv_obj_t *screen_img_6;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_label_6;
	lv_obj_t *screen_img_7;
	lv_obj_t *screen_label_7;
	lv_obj_t *screen_label_8;
	lv_obj_t *screen_img_8;
	lv_obj_t *screen_img_10;
	lv_obj_t *screen_img_9;
	lv_obj_t *screen_label_9;
	lv_obj_t *screen_img_11;
	lv_obj_t *screen_img_12;
	lv_obj_t *screen_label_10;
	lv_obj_t *screen_img_13;
	lv_obj_t *screen_label_11;
	lv_obj_t *screen_label_12;
	lv_obj_t *screen_label_13;
	lv_obj_t *screen_label_14;
	lv_obj_t *screen_label_15;
	lv_obj_t *screen_label_16;
	lv_obj_t *screen_label_18;
	lv_obj_t *screen_img_14;
	lv_obj_t *screen_img_15;
	lv_obj_t *screen_img_16;
	lv_obj_t *screen_label_19;
	lv_obj_t *screen_img_17;
	lv_obj_t *screen_img_18;
	lv_obj_t *screen_label_20;
	lv_obj_t *screen_img_20;
	lv_obj_t *screen_img_21;
	lv_obj_t *screen_img_22;
	lv_obj_t *screen_cont_1;
	lv_obj_t *screen_img_23;
	lv_obj_t *screen_img_24;
	lv_obj_t *screen_img_25;
	lv_obj_t *screen_label_21;
	lv_obj_t *screen_label_22;
	lv_obj_t *screen_label_23;
	lv_obj_t *screen_label_24;
	lv_obj_t *screen_label_25;
	lv_obj_t *screen_label_26;
	lv_obj_t *screen_chart_1;
	lv_chart_series_t *screen_chart_1_0;
	lv_obj_t *screen_btn_coffee1;
	lv_obj_t *screen_btn_coffee1_label;
	lv_obj_t *screen_btn_coffee3;
	lv_obj_t *screen_btn_coffee3_label;
	lv_obj_t *screen_btn_coffee2;
	lv_obj_t *screen_btn_coffee2_label;
	lv_obj_t *screen_btn_coffee4;
	lv_obj_t *screen_btn_coffee4_label;
	lv_obj_t *screen_btn_steam;
	lv_obj_t *screen_btn_steam_label;
	lv_obj_t *screen_btn_rinse;
	lv_obj_t *screen_btn_rinse_label;
	lv_obj_t *screen_btn_cancel;
	lv_obj_t *screen_btn_cancel_label;
	lv_obj_t *screen_btn_menu;
	lv_obj_t *screen_btn_menu_label;
	lv_obj_t *screen_img_hotwater;
	lv_obj_t *screen_img_stop;
	lv_obj_t *screen_btn_hotwater;
	lv_obj_t *screen_btn_hotwater_label;
	lv_obj_t *screen_btnm_choosemode;
	lv_obj_t *screen_btnm_choosemode_label;
	lv_obj_t *screen_img_tea1;
	lv_obj_t *screen_img_tea2;
	lv_obj_t *screen_img_tea3;
	lv_obj_t *screen_img_tea4;
	lv_obj_t *screen_cont_M;
	lv_obj_t *screen_btn_teaset1;
	lv_obj_t *screen_btn_teaset1_label;
	lv_obj_t *screen_btn_teaset2;
	lv_obj_t *screen_btn_teaset2_label;
	lv_obj_t *screen_btn_teaset3;
	lv_obj_t *screen_btn_teaset3_label;
	lv_obj_t *screen_btn_teaset4;
	lv_obj_t *screen_btn_teaset4_label;
	lv_obj_t *screen_cont_teaset;
	lv_obj_t *screen_label_startime;
	lv_obj_t *screen_label_suspendtime;
	lv_obj_t *screen_label_one;
	lv_obj_t *screen_label_two;
	lv_obj_t *screen_label_three;
	lv_obj_t *screen_label_four;
	lv_obj_t *screen_label_five;
	lv_obj_t *screen_ta_1stepoff;
	lv_obj_t *screen_ta_1stepon;
	lv_obj_t *screen_ta_2stepon;
	lv_obj_t *screen_ta_2stepoff;
	lv_obj_t *screen_ta_3;
	lv_obj_t *screen_ta_4;
	lv_obj_t *screen_ta_5;
	lv_obj_t *screen_ta_6;
	lv_obj_t *screen_ta_7;
	lv_obj_t *screen_ta_8;
	lv_obj_t *screen_btn_save;
	lv_obj_t *screen_btn_save_label;
	lv_obj_t *screen_btn_teacancel;
	lv_obj_t *screen_btn_teacancel_label;
	lv_obj_t *screen_arc_1;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_label_steamtemp;
	lv_obj_t *screen_1_btn_steamtempset;
	lv_obj_t *screen_1_btn_steamtempset_label;
	lv_obj_t *screen_1_label_coffeetemp;
	lv_obj_t *screen_1_btn_coffeetempset;
	lv_obj_t *screen_1_btn_coffeetempset_label;
	lv_obj_t *screen_1_btn_back;
	lv_obj_t *screen_1_btn_back_label;
	lv_obj_t *screen_1_label_time1;
	lv_obj_t *screen_1_label_time2;
	lv_obj_t *screen_1_label_time3;
	lv_obj_t *screen_1_label_time4;
	lv_obj_t *screen_1_btn_time1set;
	lv_obj_t *screen_1_btn_time1set_label;
	lv_obj_t *screen_1_btn_time2set;
	lv_obj_t *screen_1_btn_time2set_label;
	lv_obj_t *screen_1_btn_time3set;
	lv_obj_t *screen_1_btn_time3set_label;
	lv_obj_t *screen_1_btn_time4set;
	lv_obj_t *screen_1_btn_time4set_label;
	lv_obj_t *screen_1_cont_set;
	lv_obj_t *screen_1_btn_cancel;
	lv_obj_t *screen_1_btn_cancel_label;
	lv_obj_t *screen_1_btn_certain;
	lv_obj_t *screen_1_btn_certain_label;
	lv_obj_t *screen_1_spinbox_1;
	lv_obj_t *screen_1_spinbox_1_btn_plus;
	lv_obj_t *screen_1_spinbox_1_btn_minus;
	lv_obj_t *screen_1_label_hotwater;
	lv_obj_t *screen_1_btn_hotwaterset;
	lv_obj_t *screen_1_btn_hotwaterset_label;
	lv_obj_t *screen_1_label_brewblock;
	lv_obj_t *screen_1_btn_brewblock;
	lv_obj_t *screen_1_btn_brewblock_label;
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
LV_IMG_DECLARE(_yuyan_8x8);
LV_IMG_DECLARE(_logo_alpha_47x19);
LV_IMG_DECLARE(_9_14x13);
LV_IMG_DECLARE(_kafeibei_14x13);
LV_IMG_DECLARE(_caidan_alpha_8x7);
LV_IMG_DECLARE(_17_alpha_68x67);
LV_IMG_DECLARE(_17_alpha_63x63);
LV_IMG_DECLARE(_18_alpha_54x206);
LV_IMG_DECLARE(_juxing9_alpha_78x70);
LV_IMG_DECLARE(_weitu_alpha_40x40);
LV_IMG_DECLARE(_juxing9_alpha_78x70);
LV_IMG_DECLARE(_meishikafei_alpha_40x40);
LV_IMG_DECLARE(_2_alpha_188x99);
LV_IMG_DECLARE(_19_alpha_54x206);
LV_IMG_DECLARE(_juxing9_alpha_78x70);
LV_IMG_DECLARE(_weitu1_alpha_40x40);
LV_IMG_DECLARE(_juxing9_alpha_78x70);
LV_IMG_DECLARE(_jingdiankafei_alpha_40x40);
LV_IMG_DECLARE(_7_alpha_38x38);
LV_IMG_DECLARE(_11_alpha_47x47);
LV_IMG_DECLARE(_6_alpha_38x38);
LV_IMG_DECLARE(_juxing_alpha_65x38);
LV_IMG_DECLARE(_juxing_alpha_65x38);
LV_IMG_DECLARE(_juxing_alpha_65x38);
LV_IMG_DECLARE(_hotwater_alpha_35x35);
LV_IMG_DECLARE(_1tea_alpha_25x45);
LV_IMG_DECLARE(_2tea_alpha_25x47);
LV_IMG_DECLARE(_3tea_alpha_25x47);
LV_IMG_DECLARE(_4tea_alpha_24x44);
LV_IMG_DECLARE(_1coffee_alpha_52x52);
LV_IMG_DECLARE(_3coffee_alpha_52x52);
LV_IMG_DECLARE(_2coffee_alpha_52x52);
LV_IMG_DECLARE(_4coffee_alpha_52x52);
LV_IMG_DECLARE(_btn1_alpha_104x100);
LV_IMG_DECLARE(_hotwater24_alpha_30x37);
LV_IMG_DECLARE(_start_alpha_32x32);
LV_IMG_DECLARE(_steam_alpha_27x32);
LV_IMG_DECLARE(_stop_alpha_32x32);
LV_IMG_DECLARE(_btnnew_alpha_104x100);
LV_IMG_DECLARE(_brew_alpha_8x8);
LV_IMG_DECLARE(_steamblock_alpha_14x13);
LV_IMG_DECLARE(_coffeebock_alpha_14x13);
LV_IMG_DECLARE(_menu_alpha_8x7);
// LV_FONT_DECLARE(lv_font_montserratMedium_10)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_10)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_25)
#ifdef __cplusplus
}
#endif
#endif
