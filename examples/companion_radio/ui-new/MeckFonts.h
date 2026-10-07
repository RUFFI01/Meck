#pragma once

// ---------------------------------------------------------------------------
// MeckFonts.h — Font style system for Meck
// ---------------------------------------------------------------------------
// Defines font styles (Classic, Noto Sans, Montserrat) and provides lookup
// tables for each display driver's setTextSize() method.
//
// Place this file in: examples/companion_radio/ui-new/
// Place font .h files in: examples/companion_radio/ui-new/fonts/
//
// GxEPDDisplay.h includes this file.
// The -I examples/companion_radio/ui-new flag (already in platformio.ini)
// makes everything resolve.
// ---------------------------------------------------------------------------

#include <Adafruit_GFX.h>  // GFXfont type

// ---------------------------------------------------------------------------
// Font style IDs — stored in NodePrefs.ui_font_style
// ---------------------------------------------------------------------------
#define MECK_FONT_CLASSIC    0   // FreeSans (original Meck look)
#define MECK_FONT_NOTO       1   // Noto Sans — clean, excellent Latin Extended
#define MECK_FONT_MONTSERRAT 2   // Montserrat — geometric, distinctive
#define MECK_FONT_STYLE_COUNT 3

static inline const char* meckFontStyleName(uint8_t style) {
  switch (style) {
    case MECK_FONT_CLASSIC:    return "Classic";
    case MECK_FONT_NOTO:       return "Noto Sans";
    case MECK_FONT_MONTSERRAT: return "Montserrat";
    default:                   return "Classic";
  }
}

// ---------------------------------------------------------------------------
// Font includes — Noto Sans family
// ---------------------------------------------------------------------------
#include "fonts/NotoSans7pt8b.h"
#include "fonts/NotoSans9pt8b.h"
#include "fonts/NotoSansBold7pt7b.h"
#include "fonts/NotoSansBold9pt7b.h"
#include "fonts/NotoSansBold12pt8b.h"

// ---------------------------------------------------------------------------
// Font includes — Montserrat family
// ---------------------------------------------------------------------------
#include "fonts/Montserrat7pt8b.h"
#include "fonts/Montserrat9pt7b.h"
#include "fonts/MontserratBold7pt7b.h"
#include "fonts/MontserratBold9pt8b.h"
#include "fonts/MontserratBold12pt8b.h"

// ---------------------------------------------------------------------------
// T-Deck Pro font lookup (240×320, GxEPD2)
// ---------------------------------------------------------------------------
// Maps (fontStyle, textSize) → GFXfont*.
// Returns NULL for textSize 0 with Classic (built-in 6×8 font).
//
// textSize values used by Meck screens:
//   0 = tiny body    (built-in 6×8 or 7pt with custom fonts)
//   1 = body         (9pt)
//   2 = medium       (9pt, same as body in current layout)
//   3 = title        (12pt bold)
//   5 = clock face   (12pt bold ×2 scaling — caller handles setTextSize(2))
//
// yAdvance reference (physical pixels):
//   Classic 9pt=22, Noto 9pt=24, Montserrat 9pt=21  — close enough
//   Classic 12ptB=29, Noto 12ptB=32, Montserrat 12ptB=29  — close
// ---------------------------------------------------------------------------

static inline const GFXfont* meckGetFont_TDeckPro(uint8_t style, int textSize) {
  // Classic — return NULL to let display driver use its defaults
  if (style == MECK_FONT_CLASSIC) return nullptr;

  if (style == MECK_FONT_NOTO) {
    switch (textSize) {
      case 0:  return &NotoSans_Regular7pt8b;
      case 1:  return &NotoSans9pt8b;
      case 2:  return &NotoSans9pt8b;
      case 3:  return &NotoSans_Bold12pt8b;
      case 5:  return &NotoSans_Bold12pt8b;  // caller applies x2 scale
      default: return &NotoSans9pt8b;
    }
  }

  // MECK_FONT_MONTSERRAT
  switch (textSize) {
    case 0:  return &Montserrat_Regular7pt8b;
    case 1:  return &Montserrat_Regular9pt7b;
    case 2:  return &Montserrat_Regular9pt7b;
    case 3:  return &MontserratBold12pt8b;
    case 5:  return &MontserratBold12pt8b;  // caller applies x2 scale
    default: return &Montserrat_Regular9pt7b;
  }
}

// ---------------------------------------------------------------------------
// Unified lookup — called from display driver setTextSize()
// ---------------------------------------------------------------------------
// Returns the GFXfont* for the given style and textSize.
// If nullptr is returned, the display driver should use its built-in default
// (FreeSans for Classic style, or built-in 6×8 for textSize 0).
// ---------------------------------------------------------------------------
static inline const GFXfont* meckGetFont(uint8_t style, int textSize) {
  return meckGetFont_TDeckPro(style, textSize);
}