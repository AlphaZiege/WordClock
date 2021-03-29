#include <Effects.h>
#include <Settings.h>
#include <Adafruit_NeoPixel.h>

extern Settings settings;
extern Adafruit_NeoPixel strip;

const int led_count = 110;


//rainbowcycle
struct colors
{
    uint8_t r = 255;
    uint8_t g;
    uint8_t b;
};
colors Pixel_0;
//Adafruit_NeoPixel strip(settings.get_LedCount(), settings.get_LedPin(), NEO_GRB + NEO_KHZ800);

void Effects::staticColor()
{
    for (int i = 0; i < led_count; i++)
    {
        strip.setPixelColor(i, settings.get_SC_RED(), settings.get_SC_GREEN(), settings.get_SC_BLUE());
    }
}

void Effects::breathe()
{
    if (settings.get_brightestBreatheColor() == 0)
    {
        breath_multiplikator = 0;
    }
    else
    {
        breath_multiplikator = 255 / settings.get_brightestBreatheColor();
    }
    if (millis() >= timestamp + settings.get_breathe_delay())
    {
        if (fade_in)
        {
            strip.setBrightness(breathe_index);
            for (int b = 0; b < led_count; b++)
                strip.setPixelColor(b, settings.get_breathe_RED() * breath_multiplikator, settings.get_breathe_GREEN() * breath_multiplikator, settings.get_breathe_BLUE() * breath_multiplikator);
            breathe_index++;
            if (breathe_index >= settings.get_brightestBreatheColor())
                fade_in = false;
        }
        else
        {
            strip.setBrightness(breathe_index);
            for (int b = 0; b < led_count; b++)
                strip.setPixelColor(b, settings.get_breathe_RED() * breath_multiplikator, settings.get_breathe_GREEN() * breath_multiplikator, settings.get_breathe_BLUE() * breath_multiplikator);
            breathe_index--;
            if (breathe_index <= 1)
                fade_in = true;
        }
        timestamp = millis();
    }
}

void Effects::colorCycle()
{

    if (rup)
    {
        R++;
    }
    else if (gup)
    {
        G++;
    }
    else if (bup)
    {
        B++;
    }
    if (R == 255)
    {
        rup = false;
        gup = true;
    }
    if (G == 255)
    {
        gup = false;
        bup = true;
    }
    if (B == 255)
    {
        bup = false;
        rup = true;
    }
    if (!rup && R != 0)
    {
        R--;
    }
    else if (!gup && G != 0)
    {
        G--;
    }
    else if (!bup && B != 0)
    {
        B--;
    }

    for (int i = 0; i < led_count; i++)
    {
        strip.setPixelColor(i, R, G, B);
    }
}

void Effects::rainbowCycle()
{
    if (millis() >= timestamp + settings.get_rainbowcycle_verzoegerung())
    {
        colors Pixelfarben = Pixel_0;
        for (int LED = 0; LED < led_count; LED++)
        {
            strip.setPixelColor(LED, Pixelfarben.r, Pixelfarben.g, Pixelfarben.b);
            for (uint8_t Durchgaenge = 0; Durchgaenge < settings.get_rainbowcycle_farbsprung(); Durchgaenge++)
            {
                if (Pixelfarben.r > 0 && Pixelfarben.b == 0)
                { // Zustand 0
                    Pixelfarben.r--;
                    Pixelfarben.g++;
                }
                if (Pixelfarben.g > 0 && Pixelfarben.r == 0)
                { // Zustand 1
                    Pixelfarben.g--;
                    Pixelfarben.b++;
                }
                if (Pixelfarben.b > 0 && Pixelfarben.g == 0)
                { // Zustand 2
                    Pixelfarben.b--;
                    Pixelfarben.r++;
                }
            }
        }
        for (uint8_t Durchgaenge = 0; Durchgaenge < settings.get_rainbowcycle_farbsprung(); Durchgaenge++)
        {
            if (Pixel_0.r > 0 && Pixel_0.b == 0)
            { // Zustand 0
                Pixel_0.r--;
                Pixel_0.g++;
            }
            if (Pixel_0.g > 0 && Pixel_0.r == 0)
            { // Zustand 1
                Pixel_0.g--;
                Pixel_0.b++;
            }
            if (Pixel_0.b > 0 && Pixel_0.g == 0)
            { // Zustand 2
                Pixel_0.b--;
                Pixel_0.r++;
            }
        }
        timestamp = millis();
    }
}

void Effects::saison(String theme)
{
    uint32_t color1;
    uint32_t color2;
    uint32_t color3;
    if (theme == "Halloween")
    {
        color1 = 247095028;
        color2 = 138030228;
        color3 = 133226031;
    }

    if (timestamp > millis() - 200)
    {
        uint32_t farbe1 = 0;
        uint32_t farbe2 = 0;
        uint32_t farbe3 = 0;
        timestamp = millis();
        switch (counter)
        {
        case 0:
            counter++;
            farbe1 = color1;
            farbe2 = color2;
            farbe3 = color3;
            break;

        case 1:
            counter++;
            farbe1 = color2;
            farbe2 = color3;
            farbe3 = color1;

        case 2:
            counter = 0;
            farbe1 = color3;
            farbe2 = color1;
            farbe3 = color2;
        }
        for (int i = 0; i <= led_count; i = i + 3)
        {
            strip.setPixelColor(i, farbe1);
            strip.setPixelColor(i + 1, farbe2);
            strip.setPixelColor(i + 2, farbe3);
        }
    }
}

void Effects::explosion()
{
    if (millis() > timestamp + settings.get_explosion_delay())
    {
        if (explosion_geht_an)
        {
            if (explosion_j < 5)
            {
                for (int explosion_b = 1 + 12 * explosion_j; explosion_b <= 9 + 10 * explosion_j; explosion_b++)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                for (int explosion_b = 100 - 10 * explosion_j; explosion_b <= 108 - 12 * explosion_j; explosion_b++)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                for (int explosion_b = 12 * explosion_j; explosion_b <= 99 - 10 * explosion_j; explosion_b += 11)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                for (int explosion_b = 10 + 10 * explosion_j; explosion_b <= 109 - 12 * explosion_j; explosion_b += 11)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                if (explosion_j == 4 && !explosion_p)
                {
                    explosion_timestamp2_enabled = true;
                    explosion_p = true;
                }
                if (explosion_j == 4 && millis() > timestamp2 + settings.get_explosion_delay())
                {
                    explosion_geht_an = false;
                    explosion_p = false;
                }
                if (explosion_j < 4)
                    explosion_j++;
            }
        }
        else
        {
            if (explosion_j >= 0)
            {
                for (int explosion_b = 1 + 12 * explosion_j; explosion_b <= 9 + 10 * explosion_j; explosion_b++)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                for (int explosion_b = 100 - 10 * explosion_j; explosion_b <= 108 - 12 * explosion_j; explosion_b++)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                for (int explosion_b = 12 * explosion_j; explosion_b <= 99 - 10 * explosion_j; explosion_b += 11)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                for (int explosion_b = 10 + 10 * explosion_j; explosion_b <= 109 - 12 * explosion_j; explosion_b += 11)
                    strip.setPixelColor(explosion_b, settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                if (explosion_j == 0 && !explosion_p)
                {
                    explosion_timestamp2_enabled = true;
                    explosion_p = true;
                }
                if (explosion_j == 0 && millis() > timestamp2 + settings.get_explosion_delay())
                {
                    explosion_geht_an = true;
                    explosion_p = false;
                }
                if (explosion_j > 0)
                    explosion_j--;
            }
        }
        timestamp = millis();
        if (explosion_timestamp2_enabled)
        {
            timestamp2 = millis();
            explosion_timestamp2_enabled = false;
        }
    }
}

void Effects::spiral()
{

    if (millis() > timestamp + settings.get_spiral_delay())
    {
        if (spiral_geht_an)
        {
            if (spiral_j < led_count - 1)
            {
                strip.setPixelColor(spiral_sr[spiral_j], settings.get_spiral_red(), settings.get_spiral_green(), settings.get_spiral_blue()); //100,20,0 ist schönes braunrot
                spiral_j++;
            }
            else if (spiral_j == led_count - 1 && spiral_p == false && spiral_timestamp2_enabled == false)
            {
                spiral_p = true;
                strip.setPixelColor(spiral_sr[spiral_j], settings.get_spiral_red(), settings.get_spiral_green(), settings.get_spiral_blue());
            }
            else if (spiral_j == led_count - 1 && spiral_p == true && spiral_timestamp2_enabled == false)
            {
                spiral_p = false;
                spiral_timestamp2_enabled = true;
            }
            else if (spiral_j == led_count - 1 && millis() > timestamp2 + settings.get_spiral_delay())
            {
                spiral_geht_an = false;
                spiral_timestamp2_enabled = false;
            }
        }
        else
        {
            if (spiral_j > 0)
            {
                strip.setPixelColor(spiral_sr[spiral_j], settings.get_spiral_red2(), settings.get_spiral_green2(), settings.get_spiral_blue2());
                spiral_j--;
            }
            else if (spiral_j == 0 && spiral_p == false && spiral_timestamp2_enabled == false)
            {
                spiral_p = true;
                //strip.setPixelColor(spiral_sr[spiral_j], 100, 20, 0);
            }
            else if (spiral_j == 0 && spiral_p == true && spiral_timestamp2_enabled == false)
            {
                spiral_p = false;
                spiral_timestamp2_enabled = true;
            }
            else if (spiral_j == 0 && millis() > timestamp2 + settings.get_spiral_delay())
            {
                spiral_geht_an = true;
                spiral_timestamp2_enabled = false;
            }
        }
        timestamp = millis();
        if (spiral_timestamp2_enabled == true)
            timestamp2 = millis();
    }
}