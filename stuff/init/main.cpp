#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define LED_PIN D6 //LED-Pin

Adafruit_NeoPixel strip(110, LED_PIN, NEO_GRB + NEO_KHZ800);

#define addr_colorMode 0
#define addr_SC_RED 1
#define addr_SC_GREEN 2
#define addr_SC_BLUE 3
#define addr_clockType 4
#define addr_DcfWlanMode 5
#define addr_brightness 6
#define addr_breatheDelay 7
#define addr_breatheRed 8
#define addr_breatheGreen 9
#define addr_breatheBlue 10
#define addr_timeType 11
#define addr_rainbowcycle_verzoegerung 12
#define addr_rainbowcycle_farbsprung 13
#define addr_explosion_red 14
#define addr_explosion_green 15
#define addr_explosion_blue 16
#define addr_explosion_delay 17
#define addr_spiral_red 18
#define addr_spiral_green 19
#define addr_spiral_blue 20
#define addr_spiral_delay 21
#define addr_spiral_red2 22
#define addr_spiral_green2 23
#define addr_spiral_blue2 24
#define addr_explosion_red2 25
#define addr_explosion_green2 26
#define addr_explosion_blue2 27
#define addr_offhours_begin_h 28
#define addr_offhours_end_h 29
#define addr_offhours_brightness 30
#define addr_offhours_begin_m 31
#define addr_offhours_end_m 32

#define addr_wlan1_ssid 200
#define addr_wlan1_pw 300
#define addr_hostname 400

String readStringFromEEPROM(int addrOffset)
  {
    int newStrLen = EEPROM.read(addrOffset);
    char data[newStrLen + 1];
    for (int i = 0; i < newStrLen; i++)
    {
      data[i] = EEPROM.read(addrOffset + 1 + i);
    }
    data[newStrLen] = '\0'; // the character may appear in a weird way, you should read: 'only one backslash and 0'
    return String(data);
  }

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
  {
    byte len = strToWrite.length();
    EEPROM.write(addrOffset, len);

    for (int i = 0; i < len; i++)
    {
      EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
    }
    EEPROM.commit();
  }

void setup()
{
    strip.begin();
    Serial.begin(115200); //115200 : 9600
    while (!Serial);
    Serial.println("kekw");
    EEPROM.begin(1024);

    EEPROM.write(addr_SC_RED, 255);
    EEPROM.write(addr_SC_GREEN, 0);
    EEPROM.write(addr_SC_BLUE, 0);
    EEPROM.write(addr_colorMode, 4);
    EEPROM.write(addr_DcfWlanMode, 1);
    EEPROM.write(addr_clockType, 0);
    EEPROM.write(addr_brightness, 100);
    EEPROM.write(addr_breatheDelay, 1);
    EEPROM.write(addr_breatheRed, 0);
    EEPROM.write(addr_breatheGreen, 255);
    EEPROM.write(addr_breatheBlue, 0);
    EEPROM.write(addr_timeType, 0);
    EEPROM.write(addr_rainbowcycle_verzoegerung, 20);
    EEPROM.write(addr_rainbowcycle_farbsprung, 3);
    EEPROM.write(addr_explosion_red, 255);
    EEPROM.write(addr_explosion_green, 0);
    EEPROM.write(addr_explosion_blue, 255);
    EEPROM.write(addr_explosion_red2, 0);
    EEPROM.write(addr_explosion_green2, 0);
    EEPROM.write(addr_explosion_blue2, 255);
    EEPROM.write(addr_explosion_delay, 100);
    EEPROM.write(addr_spiral_red, 255);
    EEPROM.write(addr_spiral_green, 255);
    EEPROM.write(addr_spiral_blue, 0);
    EEPROM.write(addr_spiral_red2, 0);
    EEPROM.write(addr_spiral_green2, 255);
    EEPROM.write(addr_spiral_blue2, 255);
    EEPROM.write(addr_spiral_delay, 10);
    EEPROM.write(addr_offhours_brightness, 10);
    EEPROM.write(addr_offhours_begin_h, 23);
    EEPROM.write(addr_offhours_begin_m, 30);
    EEPROM.write(addr_offhours_end_h, 8);
    EEPROM.write(addr_offhours_end_m, 0);
    writeStringToEEPROM(addr_hostname, "WordClock_0");

    EEPROM.commit();
}

void loop()
{
    if (EEPROM.read(addr_colorMode) == 4 && EEPROM.read(addr_brightness) == 100 && EEPROM.read(addr_DcfWlanMode) == 1 && EEPROM.read(addr_timeType) == 0)
    {
        strip.setPixelColor(25, 0, 255, 0, 0);
        strip.setPixelColor(29, 0, 255, 0, 0);
        strip.setPixelColor(68, 0, 255, 0, 0);
        strip.setPixelColor(80, 0, 255, 0, 0);
        strip.setPixelColor(92, 0, 255, 0, 0);
        strip.setPixelColor(93, 0, 255, 0, 0);
        strip.setPixelColor(94, 0, 255, 0, 0);
        strip.setPixelColor(84, 0, 255, 0, 0);
        strip.setPixelColor(74, 0, 255, 0, 0);
    }
    else
    {
        strip.setPixelColor(25, 255, 0, 0, 0);
        strip.setPixelColor(29, 255, 0, 0, 0);
        strip.setPixelColor(68, 255, 0, 0, 0);
        strip.setPixelColor(80, 255, 0, 0, 0);
        strip.setPixelColor(92, 255, 0, 0, 0);
        strip.setPixelColor(93, 255, 0, 0, 0);
        strip.setPixelColor(94, 255, 0, 0, 0);
        strip.setPixelColor(84, 255, 0, 0, 0);
        strip.setPixelColor(74, 255, 0, 0, 0);
    }
    strip.show();
}
