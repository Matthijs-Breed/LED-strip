#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void PoPi()
{
  FastLED.clear();
  int bar_width = 10;
  unsigned int current_color_rb = CRGB::Blue;
  unsigned int current_color = CRGB::Blue;

  while (getMode() == m_POPI) {
    EVERY_N_MILLISECONDS(500)
    {
      for (int n = 0; n < NUM_LEDS; n += bar_width) {
        for (int i = 0; i < bar_width; i++) {
          g_LEDs[n+i] = current_color;
        } 
        if (current_color != CRGB::White) {
          current_color = CRGB::White;
        } else {
          current_color = current_color_rb;
        }
      }
      if (current_color_rb != CRGB::Red){
        current_color_rb = CRGB::Red;
      } else {
        current_color_rb = CRGB::Blue;
      }
      if (current_color != CRGB::White) {
        current_color = CRGB::White;
      } else {
        current_color = current_color_rb;
      }
      checkBrightness();
      FastLED.show();
    }
  }
}