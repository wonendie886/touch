/*
 * Runtime language switch (Chinese / English) for the GUI-Guider user interface.
 *
 * How it works
 * ------------
 * 1. Every Chinese text used by the generated screens is listed in lang_table[]
 *    together with its English translation.  The Chinese text is the "key".
 * 2. lang_set() walks the widget tree of both screens and replaces every label
 *    text (and every button matrix map) by the text of the selected language.
 *    Because the table maps in both directions, switching back to Chinese also
 *    restores the original Chinese texts.
 * 3. Text that is set at runtime by the application (maintenance messages,
 *    password messages, the coffee/tea selector) is watched by lang_task(), which
 *    runs after the application updated the widgets and therefore fixes the text
 *    before it is drawn.
 * 4. The title of the menu sidebar page is a string owned by lv_menu, it has to
 *    be replaced in the page itself, otherwise lv_menu would restore the Chinese
 *    title on the next page change.
 *
 * Text that is not present in the table is simply left untouched, so adding new
 * Chinese texts only requires adding a line to lang_table[].
 */

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include "lvgl.h"
#include "lang.h"
#include "flash.h"

/*********************
 *      DEFINES
 *********************/
#define LANG_BTNM_MAX_BTN       4   /* max number of buttons tracked per button matrix */
#define LANG_BTNM_TEXT_LEN      48  /* max length of one translated button text */
#define LANG_BTNM_MAX_OBJ       2   /* number of button matrices of the UI */

/* label of the language toggle button: it always shows the language you can switch to */
#define LANG_BTN_TEXT_TO_EN     "English"
#define LANG_BTN_TEXT_TO_ZH     "Chinese"

/* language the UI starts with after power on (used when flash holds no valid value) */
#define LANG_DEFAULT            LANG_EN

/* Offset of the language value stored in flash.  An erased flash cell reads as
 * 0xFFFFFFFF, so LANG_ZH (0) and LANG_EN (1) are stored on top of this base to
 * tell "not written yet" apart from a real selection. */
#define LANG_FLASH_BASE         0x1000u

/* the title of the menu sidebar page (page->title of lv_menu) */
#define LANG_MENU_TITLE_ZH      "菜单"

/* Height of the sidebar header of the setting menu.
 * The generated style of that header uses pad_top = pad_bottom = 0 and let the
 * height follow the content, so the "菜单" title touches the first menu item.
 * A fixed height centres the title and gives it room above and below. */
#define LANG_MENU_HEADER_H      44

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    const char *zh;
    const char *en;
} lang_pair_t;

typedef struct {
    lv_obj_t *obj;
    char text[LANG_BTNM_MAX_BTN][LANG_BTNM_TEXT_LEN];
    const char *map[LANG_BTNM_MAX_BTN + 1];
} lang_btnm_cache_t;

/**********************
 *  STATIC VARIABLES
 **********************/
static const lang_pair_t lang_table[] = {
    /* ---- main screen ---- */
    {"咖啡萃取(s)",                 "Coffee (s)"},
    {"咖啡萃取(ml)",                "Coffee (ml)"},
    {"茶饮萃取",                    "Tea"},
    {"运行时间",                    "Run time"},
    {"暂停时间",                    "Pause time"},
    {"保存",                        "Save"},
    {"取消",                        "Cancel"},
    {"请输入密码.",                 "Enter password."},
    {"确认",                        "Confirm"},
    {"返回",                        "Back"},
    {"密码错误",                    "Wrong password"},

    /* ---- menu of the setting screen ---- */
    {LANG_MENU_TITLE_ZH,            "Menu"},
    {"设置",                        "Settings"},
    {"维护",                        "Maintenance"},
    {"密码",                        "Password"},
    {"咖啡锅炉(°C)",                "Coffee boiler (°C)"},
    {"除垢",                        "Descale"},
    {"锅炉换水",                    "Boiler water change"},
    {"清空水路",                    "Drain water line"},
    {"冲煮头逆洗",                  "Brew head backflush"},
    {"确定",                        "OK"},

    /* ---- setting screen ---- */
    {"冲煮头(°C)",                  "Brew head (°C)"},
    {"热水(s)",                     "Hot water (s)"},
    {"蒸汽锅炉(°C)",                "Steam boiler (°C)"},
    {"咖啡1",                       "Coffee 1"},
    {"咖啡2",                       "Coffee 2"},
    {"咖啡3",                       "Coffee 3"},
    {"咖啡4",                       "Coffee 4"},
    {"保存成功",                    "Saved"},

    /* ---- maintenance messages (set at runtime by the application) ---- */
    {"维护中.",                     "Maintaining."},
    {"系统已排空,请关闭电源.",      "System drained. Please switch off."},
    {"用4升清水更换水箱中的水.点击“确定”继续冲洗.",
     "Replace the water in the tank with 4 L fresh water. Press OK to continue rinsing."},
    {"点击“确定”以开始锅炉水更换.",
     "Press OK to start the boiler water change."},
    {"清洗盲碗,点击“确定”,再次清洗.",
     "Clean the blind filter, press OK and rinse again."},
    {"向水箱中加入4升除垢液,点击“确定”开始除垢.",
     "Add 4 L of descaler to the water tank. Press OK to start descaling."},
    {"将3升清水注入水箱.点击“确定”以开始锅炉水更换.",
     "Fill the tank with 3 L fresh water. Press OK to start the boiler water change."},
    {"切断供水.按下“确定”键以排空系统.",
     "Cut off the water supply. Press OK to drain the system."},
    {"将1升清水注入水箱,盲碗中加入5g清洁片/粉,再点“确定”开始冲煮头逆洗.",
     "Fill the tank with 1 L fresh water, put 5 g of cleaner in the blind filter, press OK to backflush."},
    {"排空水系统.注意防止废水盘处溅水.预计时间:10分钟.",
     "Draining the water system. Watch out for splashing at the drip tray. Time: about 10 min."},
    {"更换锅炉水.注意废水盘处的水花溅出.预计时间:20分钟.",
     "Changing the boiler water. Watch out for splashing at the drip tray. Time: about 20 min."},
    {"正在除垢,请注意蒸汽出口处的高温蒸汽.预计时间:30分钟.",
     "Descaling. Beware of hot steam at the steam outlet. Time: about 30 min."},
    {"正在冲煮头逆洗,预计时间:5分钟.",
     "Backflushing the brew head. Time: about 5 min."},

    /* ---- design time placeholder of the maintenance label ---- */
    {"向水箱中加入4升除垢液，点击“确定”开始除垢。正在除垢，请注意蒸汽出口处的高温蒸汽。预计时间：30分钟。用4升清水更换水箱中的水。点击“确定”继续冲洗。用4升清水更换水箱中的水。点击“确定”继续冲洗。点击“确定”以开始锅炉水更换。将3升清水注入水箱。点击“确定”以开始锅炉水更换。更换锅炉水。注意废水盘处的水花溅出。预计时间：20分钟。切断供水。按下“确定”键以排空系统。排空水系统。注意防止废水盘处溅水。预计时间：10分钟.",
     "Maintenance"},
};

#define LANG_TABLE_NUM  (sizeof(lang_table) / sizeof(lang_table[0]))

static lang_t g_lang = LANG_DEFAULT;        /* current language */
static lv_obj_t *g_lang_btn = NULL;         /* the language toggle button of screen_1 */
static lv_obj_t *g_lang_btn_label = NULL;   /* label of the language toggle button */
static lv_obj_t *g_lang_screen_1 = NULL;    /* screen_1 this module is already prepared for */

static lang_btnm_cache_t g_btnm_cache[LANG_BTNM_MAX_OBJ];
static uint8_t g_btnm_cache_cnt = 0;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lang_refr(void);
static void lang_apply_obj(lv_obj_t *obj);
static void lang_btnm_apply(lv_obj_t *obj);
static void lang_menu_title_apply(void);
static void lang_menu_header_apply(void);
static void lang_prepare_screen_1(void);
static void lang_create_button(void);
static void lang_button_label_refr(void);
static void lang_button_sync_maintain(void);
static lang_t lang_flash_load(void);


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Look up a text of the table.
 * @param text      text to look up
 * @param from_zh   true: `text` is Chinese (the English text is returned),
 *                  false: `text` is English (the Chinese text is returned)
 * @return the translated text or NULL if `text` is no entry of the table
 */
static const char *lang_lookup(const char *text, bool from_zh)
{
    uint32_t i;

    if(text == NULL) return NULL;

    for(i = 0; i < LANG_TABLE_NUM; i++) {
        const char *key = from_zh ? lang_table[i].zh : lang_table[i].en;

        if(strcmp(text, key) == 0) {
            return from_zh ? lang_table[i].en : lang_table[i].zh;
        }
    }

    return NULL;
}

/**
 * Translate `text` into the target language.
 * @return the translation or NULL if `text` is no entry of the table
 */
static const char *lang_translate(const char *text, lang_t target)
{
    return lang_lookup(text, target == LANG_EN);
}

/**
 * Translate the map of a button matrix into the current language.
 * lv_btnmatrix only stores the pointers, so the translated strings are kept in
 * a static cache that lives as long as the map is used.
 */
static void lang_btnm_apply(lv_obj_t *obj)
{
    const char **cur_map;
    const char *desired[LANG_BTNM_MAX_BTN];
    lang_btnm_cache_t *cache = NULL;
    uint8_t btn_cnt = 0;
    uint8_t i;
    bool changed = false;

    if(obj == NULL) return;

    cur_map = lv_btnmatrix_get_map(obj);
    if(cur_map == NULL) return;

    /* count the buttons: a map with more buttons than the cache can hold must not
     * be replaced, otherwise the additional buttons would get lost */
    for(i = 0; ; i++) {
        if(cur_map[i] == NULL || cur_map[i][0] == '\0') break;
        if(i >= LANG_BTNM_MAX_BTN) return;
    }
    btn_cnt = i;

    if(btn_cnt == 0) return;

    for(i = 0; i < btn_cnt; i++) {
        const char *cur = cur_map[i];
        const char *tr = lang_translate(cur, g_lang);

        desired[i] = (tr != NULL) ? tr : cur;

        if(tr != NULL && strcmp(tr, cur) != 0) changed = true;
    }

    if(changed == false) return;

    /* find (or allocate) the cache slot of this button matrix */
    for(i = 0; i < g_btnm_cache_cnt; i++) {
        if(g_btnm_cache[i].obj == obj) {
            cache = &g_btnm_cache[i];
            break;
        }
    }
    if(cache == NULL) {
        if(g_btnm_cache_cnt >= LANG_BTNM_MAX_OBJ) return;

        cache = &g_btnm_cache[g_btnm_cache_cnt];
        cache->obj = obj;
        g_btnm_cache_cnt++;
    }

    for(i = 0; i < btn_cnt; i++) {
        /* the string may already be stored in the cache, never copy onto itself */
        if(desired[i] != cache->text[i]) {
            strncpy(cache->text[i], desired[i], LANG_BTNM_TEXT_LEN - 1);
            cache->text[i][LANG_BTNM_TEXT_LEN - 1] = '\0';
        }
        cache->map[i] = cache->text[i];
    }
    cache->map[btn_cnt] = "";

    lv_btnmatrix_set_map(obj, cache->map);
}

/**
 * Translate all labels (and button matrices) of a widget and of its children.
 */
static void lang_apply_obj(lv_obj_t *obj)
{
    uint32_t i;
    uint32_t child_cnt;

    if(obj == NULL) return;

    if(lv_obj_check_type(obj, &lv_label_class)) {
        const char *cur = lv_label_get_text(obj);

        if(cur != NULL && cur[0] != '\0') {
            /* when switching to English only Chinese texts can be translated, skip ASCII fast */
            if(g_lang != LANG_EN || (uint8_t)cur[0] >= 0x80) {
                const char *tr = lang_translate(cur, g_lang);

                if(tr != NULL && strcmp(tr, cur) != 0) {
                    lv_label_set_text(obj, tr);
                }
            }
        }
    }
    else if(lv_obj_check_type(obj, &lv_btnmatrix_class)) {
        lang_btnm_apply(obj);
    }

    child_cnt = lv_obj_get_child_cnt(obj);
    for(i = 0; i < child_cnt; i++) {
        lang_apply_obj(lv_obj_get_child(obj, i));
    }
}

/**
 * Update the title of the menu sidebar page.
 * lv_menu keeps the title in the page and writes it into the header label again
 * on every page change, so the page itself has to be updated.
 */
static void lang_menu_title_apply(void)
{
    lv_obj_t *page_obj = guider_ui.screen_1_menu_1_sidebar_page;
    lv_obj_t *menu = guider_ui.screen_1_menu_1;
    lv_menu_page_t *page;
    const char *title;
    char *new_title;
    size_t len;

    if(page_obj == NULL || menu == NULL) return;

    page = (lv_menu_page_t *)page_obj;
    title = lang_tr(LANG_MENU_TITLE_ZH);

    if(page->title != NULL && strcmp(page->title, title) == 0) return;

    len = strlen(title) + 1;
    new_title = (char *)lv_mem_alloc(len);
    if(new_title == NULL) return;

    memcpy(new_title, title, len);
    if(page->title != NULL) lv_mem_free(page->title);
    page->title = new_title;

    /* let lv_menu take the new page title over into its header label */
    lv_event_send(menu, LV_EVENT_VALUE_CHANGED, NULL);
}

/**
 * Give the "菜单" title of the setting menu more room.
 * The header is a flex row with LV_FLEX_ALIGN_CENTER on the cross axis, so with a
 * fixed height the title is centred instead of sitting on the first menu item.
 * The height of the sidebar header is not touched by lv_menu when the page
 * changes, so this has to run only once per created screen_1.
 */
static void lang_menu_header_apply(void)
{
    lv_obj_t *header;

    if(guider_ui.screen_1_menu_1 == NULL) return;

    header = lv_menu_get_sidebar_header(guider_ui.screen_1_menu_1);
    if(header == NULL) return;

    lv_obj_set_height(header, LANG_MENU_HEADER_H);
}

/**
 * Show the language the button switches to.
 */
static void lang_button_label_refr(void)
{
    if(g_lang_btn_label == NULL) return;

    lv_label_set_text(g_lang_btn_label,
                      (g_lang == LANG_ZH) ? LANG_BTN_TEXT_TO_EN : LANG_BTN_TEXT_TO_ZH);
}

static void lang_button_event_cb(lv_event_t *e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lang_set((g_lang == LANG_ZH) ? LANG_EN : LANG_ZH);
    }
}

/**
 * The maintenance view (screen_1_cont_maintain) is a full screen overlay of
 * screen_1, and the language toggle button is a child of screen_1 created at
 * runtime, so it would be drawn on top of the maintenance view.  While the
 * maintenance view is up the toggle must be neither visible nor usable.
 *
 * The check runs in lang_task(), so it follows the application that shows and
 * hides the container without touching any of those places.
 */
static void lang_button_sync_maintain(void)
{
    lv_obj_t *cont = guider_ui.screen_1_cont_maintain;
    bool maintain_active;
    bool btn_hidden;

    if(g_lang_btn == NULL) return;

    /* screen_1 may not have been created yet, then there is no maintenance view */
    maintain_active = (guider_ui.screen_1 != NULL) && (cont != NULL) &&
                      (lv_obj_has_flag(cont, LV_OBJ_FLAG_HIDDEN) == false);

    btn_hidden = lv_obj_has_flag(g_lang_btn, LV_OBJ_FLAG_HIDDEN);
    if(btn_hidden == maintain_active) return;    /* already in the wanted state */

    if(maintain_active) {
        lv_obj_add_state(g_lang_btn, LV_STATE_DISABLED);  /* not usable */
        lv_obj_add_flag(g_lang_btn, LV_OBJ_FLAG_HIDDEN);  /* not visible */
    }
    else {
        lv_obj_clear_flag(g_lang_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(g_lang_btn, LV_STATE_DISABLED);
    }
}

/**
 * Create the language toggle button in the top right corner of screen_1.
 */
static void lang_create_button(void)
{
    lv_obj_t *btn;
    lv_obj_t *label;

    if(guider_ui.screen_1 == NULL || g_lang_btn != NULL) return;

    btn = lv_btn_create(guider_ui.screen_1);
    if(btn == NULL) return;

    lv_obj_set_pos(btn, 400, 2);
    lv_obj_set_size(btn, 76, 30);
    lv_obj_set_style_radius(btn, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x54606a), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(btn, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(btn, &lv_font_SourceHanSerifSC_Regular_16,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn, lang_button_event_cb, LV_EVENT_CLICKED, NULL);

    label = lv_label_create(btn);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_SourceHanSerifSC_Regular_16,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);

    g_lang_btn = btn;
    g_lang_btn_label = label;
    lang_button_label_refr();
    lang_button_sync_maintain();
}

/**
 * Language selected at the last power down.
 * flashGetLanguage() holds LANG_FLASH_BASE + lang, or 0xFFFFFFFF if the flash
 * was never written (first power on, or a firmware update from a version
 * without the language field) - then LANG_DEFAULT is used.
 */
static lang_t lang_flash_load(void)
{
    uint32_t stored = flashGetLanguage();

    if(stored == LANG_FLASH_BASE + (uint32_t)LANG_ZH) return LANG_ZH;
    if(stored == LANG_FLASH_BASE + (uint32_t)LANG_EN) return LANG_EN;

    return LANG_DEFAULT;
}

/**
 * Apply the current language to the whole UI.
 */
static void lang_refr(void)
{
    lang_apply_obj(guider_ui.screen);
    lang_apply_obj(guider_ui.screen_1);
    lang_menu_title_apply();
    lang_button_label_refr();
}

/**
 * screen_1 was created (first visit of the setting screen): add the toggle
 * button and translate the new screen if English is already selected.
 */
static void lang_prepare_screen_1(void)
{
    g_lang_screen_1 = guider_ui.screen_1;
    /* a previous screen_1 may have been deleted, its button is invalid now */
    g_lang_btn = NULL;
    g_lang_btn_label = NULL;

    lang_menu_header_apply();
    lang_create_button();
    lang_refr();
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lang_init(void)
{
    g_lang = lang_flash_load();
    g_lang_btn = NULL;
    g_lang_btn_label = NULL;
    g_btnm_cache_cnt = 0;
    g_lang_screen_1 = guider_ui.screen_1;

    if(g_lang_screen_1 != NULL) {
        /* screen_1 is already there: prepare it (this translates the whole UI) */
        lang_prepare_screen_1();
    }
    else {
        /* screen_1 is created on the first visit of the setting screen, but the
         * start screen must already show the default language */
        lang_refr();
    }
}

void lang_task(void)
{
    /* screen_1 does not exist before the setting screen is opened the first time */
    if(g_lang_screen_1 != guider_ui.screen_1) {
        if(guider_ui.screen_1 != NULL) {
            lang_prepare_screen_1();
        }
        else {
            g_lang_screen_1 = NULL;
        }
    }

    /* the language toggle must be hidden and disabled while the maintenance
     * view of screen_1 is up (independent of the selected language) */
    lang_button_sync_maintain();

    if(g_lang != LANG_EN) return;

    /* texts that are written by the application at runtime */
    lang_apply_obj(guider_ui.screen_1_label_maintain);
    lang_apply_obj(guider_ui.screen_1_label_savesuccess);
    lang_apply_obj(guider_ui.screen_label_passworderror);
    lang_btnm_apply(guider_ui.screen_btnm_choosemode);
}

void lang_set(lang_t lang)
{
    if((lang != LANG_ZH) && (lang != LANG_EN)) return;
    if(lang == g_lang) return;

    g_lang = lang;
    lang_refr();

    /* remember the selection for the next power on; this erases the parameter
     * sector, so the UI is refreshed above first */
    flashSetLanguage(LANG_FLASH_BASE + (uint32_t)lang);
}

lang_t lang_get(void)
{
    return g_lang;
}

const char *lang_tr(const char *zh_text)
{
    const char *tr;

    if(zh_text == NULL || g_lang == LANG_ZH) return zh_text;

    tr = lang_lookup(zh_text, true);

    return (tr != NULL) ? tr : zh_text;
}

