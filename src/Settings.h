#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class Settings
{
private:
    String hostname;

    // modes
    int colorMode, colorNightMode;

    // offhours
    bool isOffHours;

    // overall settings
    int timeType /*timos kack oder normal*/,
        clockType /*analog / digital idk*/,
        DcfWlanMode /*dcf oder wlan als Uhrzeitsquelle*/,
        brigthness /*allgemeine Helligkeit*/,
        offhours_begin_h /*nachtzeit ein hours*/,
        offhours_end_h /*nachtzeit aus*/,
        offhours_begin_m /*nachtzeit ein minutes*/,
        offhours_end_m /*nachtzeit aus*/,
        offhours_brightness /*alternative helligkeit für nachtzeit*/;

    // solid color
    int SC_RED,
        SC_GREEN,
        SC_BLUE,
        SC_DELAY;

    // uint32_t solidColor = 155255255;

    // breathe
    int breathe_delay;
    int breathe_red,
        breathe_green,
        breathe_blue;

    // rainbowCycle
    int rainbowcycle_verzoegerung,
        rainbowcycle_farbsprung;

    // explosion
    int explosion_red,
        explosion_green,
        explosion_blue,
        explosion_red2,
        explosion_green2,
        explosion_blue2,
        explosion_delay;

    // spiral
    int spiral_red,
        spiral_green,
        spiral_blue,
        spiral_red2,
        spiral_green2,
        spiral_blue2,
        spiral_delay;

    // noise
    int noise_redval,
        noise_greenval,
        noise_blueval,
        noise_delay,
        noise_range;

    // wlan
    String wlan1_ssid, wlan1_pw;

    // snake
    int snake_dir = 0; // 0 = noDir, 1 = up, 2 = left, 3 = right, 4 = down
    int tictactoe_field = 0;

public:
    void update(); // wird immer dann aufgerufen wenn es eine änderung aus der Appperspektive gab

    void generateJson(String version);

    void calcOffHours();

    // hostname
    void set_hostname(String yes)
    {
        hostname = yes;
    }
    String get_hostname()
    {
        return hostname;
    }

    // modes z.B. breathe oder rainbow
    void set_colorMode(int yes)
    {
        colorMode = yes;
    }
    int get_colorMode()
    {
        return colorMode;
    }
    int get_ColorNightMode()
    {
        return colorNightMode;
    }
    int get_CurrentColorMode()
    {
        if (!isOffHours)
            return colorMode;
        else
            return colorNightMode;
    }

    void set_colorNightMode(int yes)
    {
        colorNightMode = yes;
    }

    // overall settings
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
    int get_currentBrightness(){
        if (!isOffHours)
            return brigthness;
        else
            return offhours_brightness;
    }
    void set_offhours_begin_h(int yes)
    {
        offhours_begin_h = yes;
    }
    int get_offhours_begin_h()
    {
        return offhours_begin_h;
    }
    void set_offhours_end_h(int yes)
    {
        offhours_end_h = yes;
    }
    int get_offhours_end_h()
    {
        return offhours_end_h;
    }

    void set_offhours_begin_m(int yes)
    {
        offhours_begin_m = yes;
    }
    int get_offhours_begin_m()
    {
        return offhours_begin_m;
    }
    void set_offhours_end_m(int yes)
    {
        offhours_end_m = yes;
    }
    int get_offhours_end_m()
    {
        return offhours_end_m;
    }
    void set_offhours_brightness(int yes)
    {
        offhours_brightness = yes;
    }
    int get_offhours_brightness()
    {
        return offhours_brightness;
    }

    // solid color vars
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
    void set_SC_DELAY(int delay)
    {
        SC_DELAY = delay;
    }
    int get_SC_DELAY()
    {
        return SC_DELAY;
    }

    // breathe
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

    // rainbowcycle
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

    // explosion
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
    void set_explosion_red2(int red)
    {
        explosion_red2 = red;
    }
    void set_explosion_green2(int green)
    {
        explosion_green2 = green;
    }
    void set_explosion_blue2(int blue)
    {
        explosion_blue2 = blue;
    }
    int get_explosion_red2()
    {
        return explosion_red2;
    }
    int get_explosion_green2()
    {
        return explosion_green2;
    }
    int get_explosion_blue2()
    {
        return explosion_blue2;
    }
    void set_explosion_delay(int delay)
    {
        explosion_delay = delay;
    }
    int get_explosion_delay()
    {
        return explosion_delay;
    }

    // spiral
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

    // noise
    void set_noise_red(int val)
    {
        noise_redval = val;
    }
    int get_noise_red()
    {
        return noise_redval;
    }
    void set_noise_green(int val)
    {
        noise_greenval = val;
    }
    int get_noise_green()
    {
        return noise_greenval;
    }
    void set_noise_blue(int val)
    {
        noise_blueval = val;
    }
    int get_noise_blue()
    {
        return noise_blueval;
    }
    void set_noise_delay(int val)
    {
        noise_delay = val;
    }
    int get_noise_delay()
    {
        return noise_delay;
    }
    void set_noise_range(int val)
    {
        noise_range = val;
    }
    int get_noise_range()
    {
        return noise_range;
    }

    // wlan
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

    // snake
    void set_snake_dir(int dir)
    {
        snake_dir = dir;
    }
    int get_snake_dir()
    {
        return snake_dir;
    }

    // tictactoe
    void set_tictactoe_field(int dir)
    {
        tictactoe_field = dir;
    }
    int get_tictactoe_field()
    {
        return tictactoe_field;
    }
};

#endif