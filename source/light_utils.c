/*
    ===  Lighting Utilities  ===
    This file contains functions useful for coding lighting profiles
*/
#include "light_utils.h"

/*
    #define Directives declaration
*/
#define LEN(x)                                                                 \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

/*
    Static Declarations
*/

// C18 index of keys for the lights
/* ,-----------------------------------------------------------------------------------------.
 * |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  11 |  12 |    13     |
 * |-----------------------------------------------------------------------------------------+
 * |   14   |  15 |  16 |  17 |  18 |  19 |  20 |  21 |  22 |  23 |  24 |  25 |  26 |   27   |
 * |-----------------------------------------------------------------------------------------+
 * |    28   |  29 |  30 |  31 |  32 |  33 |  34 |  35 |  36 |  37 |  38 |  39 |     40      |
 * |-----------------------------------------------------------------------------------------+
 * |     42     |  44 |  45 |  46 |  47 |  48 |  49 |  50 |  51 |  52 |  53 |       54       |
 * |-----------------------------------------------------------------------------------------+
 * |   56  |   58  |   59  |               62                |   65  |   66  |  67   |   68  |
 * \-----------------------------------------------------------------------------------------/
 */
static const uint8_t modKeyIDs[] = {0,  13, 14, 28, 40, 41, 42, 54,
                                    55, 56, 57, 58, 59, 60, 61, 62,
                                    63, 64, 65, 66, 67, 68, 69};

/*
    Function declarations
*/

// Set all keys lighting to a specific color
void setAllKeysColor(led_t *ledColors, uint32_t color, uint8_t intensity) {
  const uint8_t red = (color >> 16) & 0xFF;
  const uint8_t green = (color >> 8) & 0xFF;
  const uint8_t blue = color & 0xFF;

  for (uint16_t i = 0; i < NUM_COLUMN * NUM_ROW; ++i) {
    ledColors[i].red = red >> intensity;
    ledColors[i].green = green >> intensity;
    ledColors[i].blue = blue >> intensity;
  }
}

// Set modifier keys lighting to a specific color
void setModKeysColor(led_t *ledColors, uint32_t color, uint8_t intensity) {
  const uint8_t red = (color >> 16) & 0xFF;
  const uint8_t green = (color >> 8) & 0xFF;
  const uint8_t blue = color & 0xFF;

  for (uint16_t i = 0; i < LEN(modKeyIDs); ++i) {
    ledColors[modKeyIDs[i]].red = red >> intensity;
    ledColors[modKeyIDs[i]].green = green >> intensity;
    ledColors[modKeyIDs[i]].blue = blue >> intensity;
  }
}

void setModKeysColorRGB(led_t *ledColors, uint8_t intensity) {
    uint8_t red, green, blue;
    for (uint16_t i = 0; i < LEN(modKeyIDs); ++i) {
        red = 0;
        green = 0;
        blue = 0;
        if (i % 3 == 0) red = 0xFF;
        if (i % 3 == 1) green = 0xFF;
        if (i % 3 == 2) blue = 0xFF;

        ledColors[modKeyIDs[i]].red = red >> intensity;
        ledColors[modKeyIDs[i]].green = green >> intensity;
        ledColors[modKeyIDs[i]].blue = blue >> intensity;
    }
}

// Set specific key color
inline void setKeyColor(led_t *key, uint32_t color, uint8_t intensity) {
  key->red = ((color >> 16) & 0xFF) >> intensity;
  key->green = ((color >> 8) & 0xFF) >> intensity;
  key->blue = (color & 0xFF) >> intensity;
}
