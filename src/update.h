#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <HTTPClient.h>

int getMode()
{
  EVERY_N_SECONDS(2) {
    u8g2.clearBuffer();
    // Buffer for text
    char chBuffer[128];

    // Call Endpoint
    HTTPClient http;
    http.begin("http://192.168.178.86/light/"); 
    int httpCode = http.GET(); 

    // Process HTTP response
    sprintf(chBuffer, "%d", httpCode);
    u8g2.drawStr(0, 0, chBuffer);
    String payload;
    if (httpCode == 200) {
      payload = http.getString();
    } else {
    return 0;
    }
    //u8g2.sendBuffer();

    // Close HTTP connection
    http.end();
    mode = payload.c_str()[0] - '0';
    sprintf(chBuffer, "%d", mode);
    u8g2.drawStr(0, 8, chBuffer);
    char colorChar[6];
    colorChar[0] = payload.c_str()[1];
    colorChar[1] = payload.c_str()[2];
    colorChar[2] = payload.c_str()[3];
    colorChar[3] = payload.c_str()[4];
    colorChar[4] = payload.c_str()[5];
    colorChar[5] = payload.c_str()[6];
    slider_color = strtol(colorChar, NULL, 16);
    u8g2.sendBuffer();
  }  
  return mode;
}

void checkBrightness()
{
  // Call Endpoint
  HTTPClient http;
  http.begin("http://192.168.178.86/light/brightness.php"); 
  int httpCode = http.GET(); 
  String payload;
  if (httpCode == 200) {
    payload = http.getString();
  } else {
    brightness = 0;
  }
  http.end();
  brightness = (payload.c_str()[0] - '0') * 10 + (payload.c_str()[1] - '0');
  FastLED.setBrightness(brightness);
}