#include <ArduinoJson.h>
#include <NTPClient.h>
#include <Read_Write.h>
#include <Settings.h>
#include <Zeit.h>
#include <ESP8266WiFi.h>

const int led_count = 110;

extern DynamicJsonDocument doc;
extern NTPClient timeClient;
extern Read_write storage;
extern Zeit zeit;

void Settings::update() //wird immer dann aufgerufen wenn es eine änderung aus der Appperspektive gab
{
}

void Settings::generateJson(String version)
{
    doc["ClockName"] = hostname;

    doc["ColorMode"] = colorMode;
    doc["timeType"] = timeType;
    doc["clockType"] = clockType;
    doc["DcfWlanMode"] = DcfWlanMode;
    doc["Brightness"] = brigthness;
    doc["SolidColorRed"] = SC_RED;
    doc["SolidColorGreen"] = SC_GREEN;
    doc["SolidColorBlue"] = SC_BLUE;
    doc["BreatheColorRed"] = breathe_red;
    doc["BreatheColorGreen"] = breathe_green;
    doc["BreatheColorBlue"] = breathe_blue;
    doc["BreatheColorDelay"] = breathe_delay;
    doc["RainbowCycleDelay"] = rainbowcycle_verzoegerung;
    doc["RainbowCycleFarbsprung"] = rainbowcycle_farbsprung;
    doc["ExplosionRed"] = explosion_red;
    doc["ExplosionGreen"] = explosion_green;
    doc["ExplosionBlue"] = explosion_blue;
    doc["ExplosionRed2"] = explosion_red2;
    doc["ExplosionGreen2"] = explosion_green2;
    doc["ExplosionBlue2"] = explosion_blue2;
    doc["ExplosionDelay"] = explosion_delay;
    doc["SpiralRed"] = spiral_red;
    doc["SpiralGreen"] = spiral_green;
    doc["SpiralBlue"] = spiral_blue;
    doc["SpiralRed2"] = spiral_red2;
    doc["SpiralGreen2"] = spiral_green2;
    doc["SpiralBlue2"] = spiral_blue2;
    doc["SpiralDelay"] = spiral_delay;
    doc["NoiseRed"] = noise_redval;
    doc["NoiseGreen"] = noise_greenval;
    doc["NoiseBlue"] = noise_blueval;
    doc["NoiseDelay"] = noise_delay;
    doc["NoiseRange"] = noise_range;
    doc["Wlan_ssid"] = wlan1_ssid;
    doc["OffhoursBegin_h"] = offhours_begin_h;
    doc["OffhoursEnd_h"] = offhours_end_h;
    doc["OffhoursBegin_m"] = offhours_begin_m;
    doc["OffhoursEnd_m"] = offhours_end_m;
    doc["OffhoursBrightness"] = offhours_brightness;

    doc["ipaddr"] = WiFi.localIP();
    doc["version"] = version;
    doc["Uptime"] = millis();
    doc["ntp_time"] = String(timeClient.getFormattedTime());
    doc["local_time"] = String(zeit.get_hours()) + ":" + String(zeit.get_minutes()) + ":" + String(zeit.get_seconds());
    doc["local_date"] = String(zeit.get_calendarYear()) + ":" + String(zeit.get_month()) + ":" + String(zeit.get_dayMonth());
    doc["Free_Memory"] = String(ESP.getFreeHeap()) + "B";
    doc["CPU_Speed"] = String(ESP.getCpuFreqMHz()) + "MHz";
}
