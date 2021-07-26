#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void initStars(int amount, int *star_loc, int *star_bri, int *star_ddr, CRGB *star_clr, uint32_t *color_Cache) 
{
  FastLED.clear();
  int gen_dir =1;
  for (int n = 0; n < amount; n++) {
    star_loc[n] = rand() % NUM_LEDS;
    star_bri[n] = (float)n;
    star_ddr[n] = gen_dir;
    if (slider_color != 0xFFFFFF) {
      star_clr[n] = rand() % 0xFFFFFF;
    } else {
      star_clr[n] = 0xFFFFFF;
    }
    *color_Cache = slider_color;
    gen_dir = -gen_dir;
    g_LEDs[star_loc[n]] = star_clr[n];
  }
}

void Twinkle(int amount)
{
  FastLED.clear();
  int star_loc[amount] = {0};
  int star_bri[amount] = {0};
  int star_ddr[amount] = {0};
  CRGB star_clr[amount] = {0};
  uint32_t color_Cache;
  // Generate Stars
  initStars(amount, star_loc, star_bri, star_ddr, star_clr, &color_Cache);

  while (getMode() == m_TWINKLE) {    
    twinkle_Cache = clock() / CLOCKS_PER_SEC;
    for (int n = 0; n < amount; n++) {
      star_bri[n] += star_ddr[n];
      if (star_bri[n] == 0) {
        g_LEDs[star_loc[n]] = CRGB::Black;
        star_loc[n] = rand() % NUM_LEDS;
        star_ddr[n] = -star_ddr[n];
        g_LEDs[star_loc[n]] = star_clr[n];
      }
      if (star_bri[n] > 60) {
        star_ddr[n] = -star_ddr[n];
      }
      g_LEDs[star_loc[n]] = star_clr[n];
      g_LEDs[star_loc[n]] %= (star_bri[n] * 4);
    }
    FastLED.show();
    EVERY_N_SECONDS(2) {
      getMode();
      if (color_Cache != slider_color) {
      initStars(amount, star_loc, star_bri, star_ddr, star_clr, &color_Cache);
      }
    }  
  }
}