#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void RainbowWave()
{
  FastLED.clear();

  while (getMode() == m_RAINBOWWAVE) {
    EVERY_N_MILLISECONDS(100)
    {
      uint16_t beatA = beatsin16(30, 0, 255);
      uint16_t beatB = beatsin16(20, 0, 255);
      fill_rainbow(g_LEDs, NUM_LEDS, (beatA+beatB)/2, 8);
      FastLED.show();
    }
    EVERY_N_MILLISECONDS(500) {
      checkBrightness();
    }
  }  
}