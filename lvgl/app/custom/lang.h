/*
 * Runtime language switch (Chinese / English) for the GUI-Guider user interface.
 *
 * The GUI is designed in Chinese.  Every Chinese text of the generated screens is
 * kept as the "key" and lang.c holds the English translation table, so the toggle
 * does not conflict with GUI-Guider code generation (no file in
 * lvgl/app/generated is modified by this module).
 *
 * Usage (see USER/main.c):
 *      lang_init();            once, after setup_ui() / events_init()
 *      lang_task();            every LVGL task loop, after the UI texts are updated
 */

#ifndef __LANG_H_
#define __LANG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

typedef enum {
    LANG_ZH = 0,
    LANG_EN
} lang_t;

/* Prepare the module (call once after setup_ui()) */
void lang_init(void);

/* Keep the UI in sync with the selected language (call in the LVGL task loop) */
void lang_task(void);

/* Switch the whole UI to the given language */
void lang_set(lang_t lang);

/* Currently selected language */
lang_t lang_get(void);

/* Translate a Chinese source string to the current language.
 * Returns zh_text itself when no translation is available. */
const char *lang_tr(const char *zh_text);

#ifdef __cplusplus
}
#endif

#endif /* __LANG_H_ */
