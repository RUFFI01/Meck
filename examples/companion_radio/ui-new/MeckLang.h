#pragma once

// UI language (Settings > Experimental Features > Language).
//
// MECK_TR("English text", "French text") picks the string for the current
// language. French strings are UTF-8. Classic has no accents, so choosing
// French swaps Classic to Noto Sans (SettingsScreen). Noto Sans has the
// accents at every size; Montserrat has them except at Larger (9pt).

#include <stdint.h>

#define MECK_LANG_EN 0
#define MECK_LANG_FR 1

uint8_t meckUiLang();   // NodePrefs::ui_lang; defined in main.cpp

#define MECK_TR(en, fr) (meckUiLang() == MECK_LANG_FR ? (fr) : (en))
