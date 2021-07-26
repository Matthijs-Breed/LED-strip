#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void ColorSlider()
{
  FastLED.clear();
  while (getMode() == m_COLOR_SLIDER)
  {
    EVERY_N_MILLISECONDS(100)
    {
      fill_solid(g_LEDs, NUM_LEDS, slider_color);
      FastLED.show();
    }  

    EVERY_N_MILLISECONDS(500) {
      checkBrightness();
    }
  }
}