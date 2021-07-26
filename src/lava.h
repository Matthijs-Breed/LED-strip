#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

DEFINE_GRADIENT_PALETTE(lava_pallete) {
0,255,222,0,
24,255,255,0,
127,255,0,0,
233,255,222,0,
255,255,255,0,
};

void Lava()
{
    FastLED.clear();
    uint16_t l_brightnessScale = 150;
    uint16_t l_indexScale = 15;
    CRGBPalette16 lavaPallete = lava_pallete;
    while (getMode() == m_LAVA)
    {
        EVERY_N_MILLISECONDS(200) {
            for (int i = 0; i < NUM_LEDS ; i++) 
            {
                uint8_t l_brightness = inoise8(i * l_brightnessScale, millis() / 5);
                uint8_t index = inoise8(i * l_indexScale, millis() / 10);
                g_LEDs[i] = ColorFromPalette(lavaPallete, index, l_brightness);
            }

            FastLED.show();
        }
        EVERY_N_MILLISECONDS(500) {
            checkBrightness();
        }
    }
}