#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Settings.h>

extern Settings settings;

class Read_write
{
private:
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

public:
  void saveAllSettings();

  void readAllSettings();

  void saveWlan()
  {
    writeStringToEEPROM(addr_wlan1_ssid, settings.get_wlan_ssid());
    writeStringToEEPROM(addr_wlan1_pw, settings.get_wlan_pw());
  }

  uint8_t get_SC_RED()
  {
    return EEPROM.read(addr_SC_RED);
  }
  uint8_t get_SC_GREEN()
  {
    return EEPROM.read(addr_SC_GREEN);
  }
  uint8_t get_SC_BLUE()
  {
    return EEPROM.read(addr_SC_BLUE);
  }
  uint8_t get_colorMode()
  {
    return EEPROM.read(addr_colorMode);
  }
  uint8_t get_DcfWlanMode()
  {
    return EEPROM.read(addr_DcfWlanMode);
  }
  uint8_t get_clockType()
  {
    return EEPROM.read(addr_clockType);
  }
  uint8_t get_brightness()
  {
    return EEPROM.read(addr_brightness);
  }
  uint8_t get_breatheDelay()
  {
    return EEPROM.read(addr_breatheDelay);
  }
  uint8_t get_breatheRed()
  {
    return EEPROM.read(addr_breatheRed);
  }
  uint8_t get_breatheGreen()
  {
    return EEPROM.read(addr_breatheGreen);
  }
  uint8_t get_breatheBlue()
  {
    return EEPROM.read(addr_breatheBlue);
  }
  uint8_t get_timeType()
  {
    return EEPROM.read(addr_timeType);
  }
  uint8_t get_rainbowcycle_verzoegerung()
  {
    return EEPROM.read(addr_rainbowcycle_verzoegerung);
  }
  uint8_t get_rainbowcycle_farbsprung()
  {
    return EEPROM.read(addr_rainbowcycle_farbsprung);
  }
  uint8_t get_explosion_red()
  {
    return EEPROM.read(addr_explosion_red);
  }
  uint8_t get_explosion_green()
  {
    return EEPROM.read(addr_explosion_green);
  }
  uint8_t get_explosion_blue()
  {
    return EEPROM.read(addr_explosion_blue);
  }
  uint8_t get_explosion_red2()
  {
    return EEPROM.read(addr_explosion_red2);
  }
  uint8_t get_explosion_green2()
  {
    return EEPROM.read(addr_explosion_green2);
  }
  uint8_t get_explosion_blue2()
  {
    return EEPROM.read(addr_explosion_blue2);
  }
  uint8_t get_explosion_delay()
  {
    return EEPROM.read(addr_explosion_delay);
  }
  uint8_t get_spiral_red()
  {
    return EEPROM.read(addr_spiral_red);
  }
  uint8_t get_spiral_green()
  {
    return EEPROM.read(addr_spiral_green);
  }
  uint8_t get_spiral_blue()
  {
    return EEPROM.read(addr_spiral_blue);
  }
  uint8_t get_spiral_red2()
  {
    return EEPROM.read(addr_spiral_red2);
  }
  uint8_t get_spiral_green2()
  {
    return EEPROM.read(addr_spiral_green2);
  }
  uint8_t get_spiral_blue2()
  {
    return EEPROM.read(addr_spiral_blue2);
  }
  uint8_t get_spiral_delay()
  {
    return EEPROM.read(addr_spiral_delay);
  }
  String get_wlan_ssid()
  {
    return readStringFromEEPROM(addr_wlan1_ssid);
  }
  String get_wlan_pw()
  {
    return readStringFromEEPROM(addr_wlan1_pw);
  }
  uint8_t get_offhours_begin_h()
  {
    return EEPROM.read(addr_offhours_begin_h);
  }
  uint8_t get_offhours_end_h()
  {
    return EEPROM.read(addr_offhours_end_h);
  }
  uint8_t get_offhours_begin_m()
  {
    return EEPROM.read(addr_offhours_begin_m);
  }
  uint8_t get_offhours_end_m()
  {
    return EEPROM.read(addr_offhours_end_m);
  }
  uint8_t get_offhours_brightness()
  {
    return EEPROM.read(addr_offhours_brightness);
  }
  String get_hostname{
    return EEPROM.read(addr_hostname);
  }
};
#endif