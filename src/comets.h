#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void DrawComet()
{
  while (getMode() == m_COMET)
  {
    EVERY_N_MILLISECONDS(40) {
      const byte fadeAmt = 128;
      const int cometSize = 5;
      const int deltaHue  = 4;

      static byte hue[5] = {HUE_RED, HUE_GREEN, HUE_BLUE, HUE_YELLOW, HUE_PURPLE};
      static int iDirection[5] = {1, 2, 3, 4, 5};
      static int iPos[5] = {0, (int)random(NUM_LEDS), (int)random(NUM_LEDS), (int)random(NUM_LEDS), (int)random(NUM_LEDS)};

      for (int n = 0; n < 5; n++) {
        hue[n] += deltaHue * (int)abs(iDirection[n]);

        iPos[n] += iDirection[n];
        if (iPos[n] > (NUM_LEDS - cometSize) || iPos[n] < 0) {
          iDirection[n] *= -1;
          iPos[n] += iDirection[n];
        }
        for (int i = 0; i < cometSize; i++) {
          g_LEDs[iPos[n] + i].setHue(hue[n]);
        }     
      }
         
      
      // Randomly fade the LEDs
      for (int j = 0; j < NUM_LEDS; j++) {
        if (random(10) > 5) {
          g_LEDs[j] = g_LEDs[j].fadeToBlackBy(fadeAmt);
        }
      }  
      FastLED.show();
    }
  }
  EVERY_N_MILLISECONDS(500) {
      checkBrightness();
    }
}