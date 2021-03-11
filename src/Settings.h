#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class Settings
{
private:
    //modes
    int colorMode;

    //overall settings
    int timeType /*timos kack oder normal*/,
        clockType /*analog / digital idk*/,
        DcfWlanMode /*dcf oder wlan als Uhrzeitsquelle*/,
        brigthness /*allgemeine Helligkeit*/;

    //solid color
    int SC_RED,
        SC_GREEN,
        SC_BLUE;

    //uint32_t solidColor = 155255255;

    //breathe
    int breathe_delay;
    int breathe_red,
        breathe_green,
        breathe_blue;

    //rainbowCycle
    int rainbowcycle_verzoegerung,
        rainbowcycle_farbsprung;

    //explosion
    int explosion_red,
        explosion_green,
        explosion_blue,
        explosion_delay;

    //spiral
    int spiral_red,
        spiral_green,
        spiral_blue,
        spiral_red2,
        spiral_green2,
        spiral_blue2,
        spiral_delay;

    //wlan
    String wlan1_ssid, wlan1_pw;

public:
    void update(); //wird immer dann aufgerufen wenn es eine änderung aus der Appperspektive gab

    String get_settings(String wer);

    String get_networkInfo()
    {
        String data;

        data += "SSID: " + WiFi.SSID() + "\n";
        data += "Hostname: " + String(WiFi.hostname()) + "\n";
        data += "MacAdress: " + String(WiFi.macAddress()) + "\n";
        data += "IPAdress: " + WiFi.localIP().toString() + "\n";
        data += "Gateway: " + WiFi.gatewayIP().toString() + "\n";
        data += "dnsIP: " + WiFi.dnsIP().toString() + "\n";
        data += "Saved SSID: " + String(wlan1_ssid) + "\n";

        return data;
    }
    String get_time();

    String get_all()
    {
        String data;

        data += "Settings in Ram: \n" + get_settings("ram") + "\n";
        data += "Settings in Rom: \n" + get_settings("rom") + "\n";
        data += "Network Info: \n" + get_networkInfo() + "\n";
        data += "Time: \n" + get_time() + "\n";

        return data;
    }

    //modes z.B. breathe oder rainbow
    void set_colorMode(int yes)
    {
        colorMode = yes;
    }
    int get_colorMode()
    {
        return colorMode;
    }

    //overall settings
    void set_timeType(int yes)
    {
        timeType = yes;
    }
    int get_timeType()
    {
        return timeType;
    }
    void set_clockType(int yes)
    {
        clockType = yes;
    }
    int get_clockType()
    {
        return clockType;
    }
    void set_DcfWlanMode(int yes)
    {
        DcfWlanMode = yes;
    }
    int get_DcfWlanMode()
    {
        return DcfWlanMode;
    }
    void set_brightness(int yes)
    {
        brigthness = yes;
    }
    int get_brightness()
    {
        return brigthness;
    }

    //solid color vars
    void set_SC_RED(int red)
    {
        SC_RED = red;
    }
    void set_SC_GREEN(int green)
    {
        SC_GREEN = green;
    }
    void set_SC_BLUE(int blue)
    {
        SC_BLUE = blue;
    }
    int get_SC_RED()
    {
        return SC_RED;
    }
    int get_SC_GREEN()
    {
        return SC_GREEN;
    }
    int get_SC_BLUE()
    {
        return SC_BLUE;
    }

    //breathe
    void set_breathe_RED(int red)
    {
        breathe_red = red;
    }
    void set_breathe_GREEN(int green)
    {
        breathe_green = green;
    }
    void set_breathe_BLUE(int blue)
    {
        breathe_blue = blue;
    }
    int get_breathe_RED()
    {
        return breathe_red;
    }
    int get_breathe_GREEN()
    {
        return breathe_green;
    }
    int get_breathe_BLUE()
    {
        return breathe_blue;
    }

    void set_breathe_delay(int yes)
    {
        breathe_delay = yes;
    }
    int get_breathe_delay()
    {
        return breathe_delay;
    }

    int get_brightestBreatheColor()
    {
        if ((breathe_red > breathe_green && breathe_red > breathe_blue) || (breathe_red == breathe_green && breathe_red > breathe_blue) || (breathe_red > breathe_green && breathe_red == breathe_blue))
            return breathe_red;
        else if ((breathe_red < breathe_green && breathe_green > breathe_blue) || (breathe_red == breathe_green && breathe_green > breathe_blue) || (breathe_red < breathe_green && breathe_green == breathe_blue))
            return breathe_green;
        else if ((breathe_blue > breathe_green && breathe_red < breathe_blue) || (breathe_blue == breathe_green && breathe_red < breathe_blue) || (breathe_red == breathe_blue && breathe_green < breathe_blue))
            return breathe_blue;
        else
            return breathe_red;
    }

    //rainbowcycle
    void set_rainbowcycle_verzoegerung(int yes)
    {
        rainbowcycle_verzoegerung = yes;
    }
    int get_rainbowcycle_verzoegerung()
    {
        return rainbowcycle_verzoegerung;
    }
    void set_rainbowcycle_farbsprung(int yes)
    {
        rainbowcycle_farbsprung = yes;
    }
    int get_rainbowcycle_farbsprung()
    {
        return rainbowcycle_farbsprung;
    }

    //explosion
    void set_explosion_red(int red)
    {
        explosion_red = red;
    }
    void set_explosion_green(int green)
    {
        explosion_green = green;
    }
    void set_explosion_blue(int blue)
    {
        explosion_blue = blue;
    }
    int get_explosion_red()
    {
        return explosion_red;
    }
    int get_explosion_green()
    {
        return explosion_green;
    }
    int get_explosion_blue()
    {
        return explosion_blue;
    }
    void set_explosion_delay(int delay)
    {
        explosion_delay = delay;
    }
    int get_explosion_delay()
    {
        return explosion_delay;
    }

    //spiral
    void set_spiral_red(int red)
    {
        spiral_red = red;
    }
    void set_spiral_green(int green)
    {
        spiral_green = green;
    }
    void set_spiral_blue(int blue)
    {
        spiral_blue = blue;
    }
    int get_spiral_red()
    {
        return spiral_red;
    }
    int get_spiral_green()
    {
        return spiral_green;
    }
    int get_spiral_blue()
    {
        return spiral_blue;
    }
    void set_spiral_red2(int red)
    {
        spiral_red2 = red;
    }
    void set_spiral_green2(int green)
    {
        spiral_green2 = green;
    }
    void set_spiral_blue2(int blue)
    {
        spiral_blue2 = blue;
    }
    int get_spiral_red2()
    {
        return spiral_red2;
    }
    int get_spiral_green2()
    {
        return spiral_green2;
    }
    int get_spiral_blue2()
    {
        return spiral_blue2;
    }
    void set_spiral_delay(int delay)
    {
        spiral_delay = delay;
    }
    int get_spiral_delay()
    {
        return spiral_delay;
    }

    //wlan
    void set_wlan_ssid(String ssid)
    {
        wlan1_ssid = ssid;
    }
    void set_wlan_pw(String pw)
    {
        wlan1_pw = pw;
    }
    String get_wlan_ssid()
    {
        return wlan1_ssid;
    }
    String get_wlan_pw()
    {
        return wlan1_pw;
    }
};

#endif