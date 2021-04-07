#include <Read_Write.h>
#include <Settings.h>
#include <Adafruit_NeoPixel.h>
#include <NTPClient.h>
#include <Zeit.h>

extern Read_write storage;
extern Adafruit_NeoPixel strip;
extern NTPClient timeClient;
extern Zeit zeit;

void Settings::update() //wird immer dann aufgerufen wenn es eine änderung aus der Appperspektive gab
{
    strip.setBrightness(brigthness);
}

String Settings::get_settings(String wer)
{
    String data;

    if (wer == "ram")
    {
        data += "ColorMode: " + String(colorMode) + "\n";
        data += "timeType: " + String(timeType) + "\n";
        data += "clockType: " + String(clockType) + "\n";
        data += "DcfWlanMode: " + String(DcfWlanMode) + "\n";
        data += "Brightness: " + String(brigthness) + "\n";
        data += "SolidColorRed: " + String(SC_RED) + "\n";
        data += "SolidColorGreen: " + String(SC_GREEN) + "\n";
        data += "SolidColorBlue: " + String(SC_BLUE) + "\n";
        data += "BreatheColorRed: " + String(breathe_red) + "\n";
        data += "BreatheColorGreen: " + String(breathe_green) + "\n";
        data += "BreatheColorBlue: " + String(breathe_blue) + "\n";
        data += "BreatheColorDelay: " + String(breathe_delay) + "\n";
        data += "RainbowCycleDelay: " + String(rainbowcycle_verzoegerung) + "\n";
        data += "RainbowCycleFarbsprung: " + String(rainbowcycle_farbsprung) + "\n";
        data += "ExplosionRed: " + String(explosion_red) + "\n";
        data += "ExplosionGreen: " + String(explosion_green) + "\n";
        data += "ExplosionBlue: " + String(explosion_blue) + "\n";
        data += "ExplosionRed2: " + String(explosion_red2) + "\n";
        data += "ExplosionGreen2: " + String(explosion_green2) + "\n";
        data += "ExplosionBlue2: " + String(explosion_blue2) + "\n";
        data += "ExplosionDelay: " + String(explosion_delay) + "\n";
        data += "SpiralRed: " + String(spiral_red) + "\n";
        data += "SpiralGreen: " + String(spiral_green) + "\n";
        data += "SpiralBlue: " + String(spiral_blue) + "\n";
        data += "SpiralRed2: " + String(spiral_red2) + "\n";
        data += "SpiralGreen2: " + String(spiral_green2) + "\n";
        data += "SpiralBlue2: " + String(spiral_blue2) + "\n";
        data += "SpiralDelay: " + String(spiral_delay) + "\n";
        data += "Wlan_ssid: " + wlan1_ssid + "\n";
    }
    else if (wer == "rom")
    {
        data += "ColorMode: " + String(storage.get_colorMode()) + "\n";
        data += "timeType: " + String(storage.get_timeType()) + "\n";
        data += "clockType: " + String(storage.get_clockType()) + "\n";
        data += "DcfWlanMode: " + String(storage.get_DcfWlanMode()) + "\n";
        data += "Brightness: " + String(storage.get_brightness()) + "\n";
        data += "SolidColorRed: " + String(storage.get_SC_RED()) + "\n";
        data += "SolidColorGreen: " + String(storage.get_SC_GREEN()) + "\n";
        data += "SolidColorBlue: " + String(storage.get_SC_BLUE()) + "\n";
        data += "BreatheColorRed: " + String(storage.get_breatheRed()) + "\n";
        data += "BreatheColorGreen: " + String(storage.get_breatheGreen()) + "\n";
        data += "BreatheColorBlue: " + String(storage.get_breatheBlue()) + "\n";
        data += "BreatheColorDelay: " + String(storage.get_breatheDelay()) + "\n";
        data += "RainbowCycleDelay: " + String(storage.get_rainbowcycle_verzoegerung()) + "\n";
        data += "RainbowCycleFarbsprung: " + String(storage.get_rainbowcycle_farbsprung()) + "\n";
        data += "ExplosionRed: " + String(storage.get_explosion_red()) + "\n";
        data += "ExplosionGreen: " + String(storage.get_explosion_green()) + "\n";
        data += "ExplosionBlue: " + String(storage.get_explosion_blue()) + "\n";
        data += "ExplosionRed2: " + String(storage.get_explosion_red2()) + "\n";
        data += "ExplosionGreen2: " + String(storage.get_explosion_green2()) + "\n";
        data += "ExplosionBlue2: " + String(storage.get_explosion_blue2()) + "\n";
        data += "ExplosionDelay: " + String(storage.get_explosion_delay()) + "\n";
        data += "SpiralRed: " + String(storage.get_spiral_red()) + "\n";
        data += "SpiralGreen: " + String(storage.get_spiral_green()) + "\n";
        data += "SpiralBlue: " + String(storage.get_spiral_blue()) + "\n";
        data += "SpiralRed2: " + String(storage.get_spiral_red2()) + "\n";
        data += "SpiralGreen2: " + String(storage.get_spiral_green2()) + "\n";
        data += "SpiralBlue2: " + String(storage.get_spiral_blue2()) + "\n";
        data += "SpiralDelay: " + String(storage.get_spiral_delay()) + "\n";
        data += "Wlan_ssid: " + String(storage.get_wlan_ssid()) + "\n";
    }

    return data;
}

String Settings::get_time()
{
    String data;

    data += "Uhrzeit: " + String(zeit.get_hours());
    data += ":" + String(zeit.get_minutes());
    data += ":" + String(zeit.get_seconds()) + "\n";
    data += "Datum: " + String(zeit.get_calendarYear());
    data += ":" + String(zeit.get_month());
    data += ":" + String(zeit.get_dayMonth()) + "\n";

    return data;
}
