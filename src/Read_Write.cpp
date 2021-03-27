#include <Settings.h>
#include <Read_Write.h>
#include <Arduino.h>

extern Settings settings;

void Read_write::saveAllSettings()
{
  EEPROM.write(addr_SC_RED, (uint8_t)settings.get_SC_RED());
  EEPROM.write(addr_SC_GREEN, (uint8_t)settings.get_SC_GREEN());
  EEPROM.write(addr_SC_BLUE, (uint8_t)settings.get_SC_BLUE());
  EEPROM.write(addr_colorMode, (uint8_t)settings.get_colorMode());
  EEPROM.write(addr_DcfWlanMode, (uint8_t)settings.get_DcfWlanMode());
  EEPROM.write(addr_clockType, (uint8_t)settings.get_clockType());
  EEPROM.write(addr_brightness, (uint8_t)settings.get_brightness());
  EEPROM.write(addr_breatheDelay, (uint8_t)settings.get_breathe_delay());
  EEPROM.write(addr_breatheRed, (uint8_t)settings.get_breathe_RED());
  EEPROM.write(addr_breatheGreen, (uint8_t)settings.get_breathe_GREEN());
  EEPROM.write(addr_breatheBlue, (uint8_t)settings.get_breathe_BLUE());
  EEPROM.write(addr_timeType, (uint8_t)settings.get_timeType());
  EEPROM.write(addr_rainbowcycle_verzoegerung, (uint8_t)settings.get_rainbowcycle_verzoegerung());
  EEPROM.write(addr_rainbowcycle_farbsprung, (uint8_t)settings.get_rainbowcycle_farbsprung());
  EEPROM.write(addr_explosion_red, (uint8_t)settings.get_explosion_red());
  EEPROM.write(addr_explosion_green, (uint8_t)settings.get_explosion_green());
  EEPROM.write(addr_explosion_blue, (uint8_t)settings.get_explosion_blue());
  EEPROM.write(addr_explosion_delay, (uint8_t)settings.get_explosion_delay());
  EEPROM.write(addr_spiral_red, (uint8_t)settings.get_spiral_red());
  EEPROM.write(addr_spiral_green, (uint8_t)settings.get_spiral_green());
  EEPROM.write(addr_spiral_blue, (uint8_t)settings.get_spiral_blue());
  EEPROM.write(addr_spiral_red2, (uint8_t)settings.get_spiral_red2());
  EEPROM.write(addr_spiral_green2, (uint8_t)settings.get_spiral_green2());
  EEPROM.write(addr_spiral_blue2, (uint8_t)settings.get_spiral_blue2());
  EEPROM.write(addr_spiral_delay, (uint8_t)settings.get_spiral_delay());

  EEPROM.commit();
}

void Read_write::readAllSettings()
{
  settings.set_SC_RED(EEPROM.read(addr_SC_RED));
  settings.set_SC_GREEN(EEPROM.read(addr_SC_GREEN));
  settings.set_SC_BLUE(EEPROM.read(addr_SC_BLUE));
  settings.set_colorMode(EEPROM.read(addr_colorMode));
  settings.set_DcfWlanMode(EEPROM.read(addr_DcfWlanMode));
  settings.set_clockType(EEPROM.read(addr_clockType));
  settings.set_brightness(EEPROM.read(addr_brightness));
  settings.set_breathe_delay(EEPROM.read(addr_breatheDelay));
  settings.set_breathe_RED(EEPROM.read(addr_breatheRed));
  settings.set_breathe_GREEN(EEPROM.read(addr_breatheGreen));
  settings.set_breathe_BLUE(EEPROM.read(addr_breatheBlue));
  settings.set_timeType(EEPROM.read(addr_timeType));
  settings.set_rainbowcycle_verzoegerung(EEPROM.read(addr_rainbowcycle_verzoegerung));
  settings.set_rainbowcycle_farbsprung(EEPROM.read(addr_rainbowcycle_farbsprung));
  settings.set_explosion_red(EEPROM.read(addr_explosion_red));
  settings.set_explosion_green(EEPROM.read(addr_explosion_green));
  settings.set_explosion_blue(EEPROM.read(addr_explosion_blue));
  settings.set_explosion_delay(EEPROM.read(addr_explosion_delay));
  settings.set_spiral_red(EEPROM.read(addr_spiral_red));
  settings.set_spiral_green(EEPROM.read(addr_spiral_green));
  settings.set_spiral_blue(EEPROM.read(addr_spiral_blue));
  settings.set_spiral_red2(EEPROM.read(addr_spiral_red2));
  settings.set_spiral_green2(EEPROM.read(addr_spiral_green2));
  settings.set_spiral_blue2(EEPROM.read(addr_spiral_blue2));
  settings.set_spiral_delay(EEPROM.read(addr_spiral_delay));
  settings.set_wlan_ssid(String(readStringFromEEPROM(addr_wlan1_ssid)));
  settings.set_wlan_pw(String(readStringFromEEPROM(addr_wlan1_pw)));
}