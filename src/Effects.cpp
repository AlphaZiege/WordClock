#include <Effects.h>
#include <FastLED.h>
#include <Settings.h>

const int led_count = 110;

extern CFastLED FastLED;
extern CRGB leds[led_count];
extern Settings settings;


//rainbowcycle
struct colors
{
    uint8_t r = 255;
    uint8_t g;
    uint8_t b;
};
colors Pixel_0;

void Effects::setAllLEDs(int r, int g, int b)
{
    for (int i = 0; i < led_count; i++)
    {
        leds[i] = CRGB(r, g, b);
    }
}

void Effects::staticColor()
{
    if (settings.get_SC_DELAY() == 420)
    {
        timestamp = millis();
        settings.set_SC_DELAY(4200);
        settings.set_clockType(1);
    }
    else if (settings.get_SC_DELAY() == 4200)
    {
        if (timestamp + 200 > millis() and timestamp + 100 < millis())
        {
            setAllLEDs(255, 255, 255);
        }
        if (timestamp + 300 > millis() and timestamp + 200 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 400 > millis() and timestamp + 300 < millis())
        {
            setAllLEDs(255, 255, 255);
        }
        if (timestamp + 500 > millis() and timestamp + 400 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 1500 > millis() and timestamp + 500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    leds[i] = CRGB(255, 255 - (i * 2.34), 255 - (i * 2.34));
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 2500 > millis() and timestamp + 1500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    leds[i] = CRGB(255, 200 - (i * 1.83), 200 - (i * 1.83));
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 3500 > millis() and timestamp + 2500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    leds[i] = CRGB(255, 150 - (i * 1.38), 150 - (i * 1.38));
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 4500 > millis() and timestamp + 3500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    leds[i] = CRGB(255, 100 - (i * 0.92), 100 - (i * 0.92));
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 5500 > millis() and timestamp + 4500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    leds[i] = CRGB(255, 50 - (i * 0.46), 50 - (i * 0.46));
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 9500 > millis() and timestamp + 5500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    leds[i] = CRGB::Red;
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 10500 > millis() and timestamp + 9500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(3) == 1)
                {
                    leds[i] = CRGB::Red;
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 11500 > millis() and timestamp + 10500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(4) == 1)
                {
                    leds[i] = CRGB::Red;
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 12500 > millis() and timestamp + 11500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(6) == 1)
                {
                    leds[i] = CRGB::Red;
                }
                if (random(20) == 1)
                {
                    setAllLEDs(0, 255, 0);
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 11500 > millis() and timestamp + 10500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(10) == 1)
                {
                    leds[i] = CRGB::Red;
                }
                else
                    leds[i] = CRGB::Black;
            }
        }
        if (timestamp + 11800 > millis() and timestamp + 11500 < millis())
        {
            leds[25] = CRGB(255, 0, 0);
            leds[29] = CRGB(255, 0, 0);
            leds[68] = CRGB(255, 0, 0);
            leds[80] = CRGB(255, 0, 0);
            leds[92] = CRGB(255, 0, 0);
            leds[93] = CRGB(255, 0, 0);
            leds[94] = CRGB(255, 0, 0);
            leds[84] = CRGB(255, 0, 0);
            leds[74] = CRGB(255, 0, 0);
        }
        if (timestamp + 12000 > millis() and timestamp + 11800 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 14800 > millis() and timestamp + 12000 < millis())
        {
            leds[25] = CRGB(255, 0, 0);
            leds[29] = CRGB(255, 0, 0);
            leds[68] = CRGB(255, 0, 0);
            leds[80] = CRGB(255, 0, 0);
            leds[92] = CRGB(255, 0, 0);
            leds[93] = CRGB(255, 0, 0);
            leds[94] = CRGB(255, 0, 0);
            leds[84] = CRGB(255, 0, 0);
            leds[74] = CRGB(255, 0, 0);
        }
        if (timestamp + 14900 > millis() and timestamp + 14800 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 15000 > millis() and timestamp + 14900 < millis())
        {
            leds[25] = CRGB(255, 0, 0);
            leds[29] = CRGB(255, 0, 0);
            leds[68] = CRGB(255, 0, 0);
            leds[80] = CRGB(255, 0, 0);
            leds[92] = CRGB(255, 0, 0);
            leds[93] = CRGB(255, 0, 0);
            leds[94] = CRGB(255, 0, 0);
            leds[84] = CRGB(255, 0, 0);
            leds[74] = CRGB(255, 0, 0);
        }
        if (timestamp + 15100 > millis() and timestamp + 15000 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 18000 > millis() and timestamp + 15100 < millis())
        {
            leds[25] = CRGB(255, 0, 0);
            leds[29] = CRGB(255, 0, 0);
            leds[68] = CRGB(255, 0, 0);
            leds[80] = CRGB(255, 0, 0);
            leds[92] = CRGB(255, 0, 0);
            leds[93] = CRGB(255, 0, 0);
            leds[94] = CRGB(255, 0, 0);
            leds[84] = CRGB(255, 0, 0);
            leds[74] = CRGB(255, 0, 0);
        }
        if (timestamp + 20000 > millis() and timestamp + 18000 < millis())
        {
            settings.set_SC_DELAY(0);
            settings.set_clockType(0);
        }
    }

    else
    {
        setAllLEDs(settings.get_SC_RED(), settings.get_SC_GREEN(), settings.get_SC_BLUE());
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
            FastLED.setBrightness(breathe_index);
            setAllLEDs(settings.get_breathe_RED() * breath_multiplikator, settings.get_breathe_GREEN() * breath_multiplikator, settings.get_breathe_BLUE() * breath_multiplikator);
            breathe_index++;
            if (breathe_index >= settings.get_brightestBreatheColor())
                fade_in = false;
        }
        else
        {
            FastLED.setBrightness(breathe_index);
            setAllLEDs(settings.get_breathe_RED() * breath_multiplikator, settings.get_breathe_GREEN() * breath_multiplikator, settings.get_breathe_BLUE() * breath_multiplikator);
            breathe_index--;
            if (breathe_index <= 1)
                fade_in = true;
        }
        timestamp = millis();
    }
}

void Effects::colorCycle()
{

    if (rup) R++;
    else if (gup) G++;
    else if (bup) B++;
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
    if (!rup && R != 0) R--;
    else if (!gup && G != 0) G--;
    else if (!bup && B != 0) B--;

    for (int i = 0; i < led_count; i++)
        setAllLEDs(R, G, B);
}

void Effects::rainbowCycle()
{
    if (millis() >= timestamp + settings.get_rainbowcycle_verzoegerung())
    {
        colors Pixelfarben = Pixel_0;
        for (int LED = 0; LED < led_count; LED++)
        {
            leds[LED] = CRGB(Pixelfarben.r, Pixelfarben.g, Pixelfarben.b);
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
    //yes
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
                    leds[explosion_b] = CRGB(settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                for (int explosion_b = 100 - 10 * explosion_j; explosion_b <= 108 - 12 * explosion_j; explosion_b++)
                    leds[explosion_b] = CRGB(settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                for (int explosion_b = 12 * explosion_j; explosion_b <= 99 - 10 * explosion_j; explosion_b += 11)
                    leds[explosion_b] = CRGB(settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
                for (int explosion_b = 10 + 10 * explosion_j; explosion_b <= 109 - 12 * explosion_j; explosion_b += 11)
                    leds[explosion_b] = CRGB(settings.get_explosion_red(), settings.get_explosion_green(), settings.get_explosion_blue());
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
                    leds[explosion_b] = CRGB(settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                for (int explosion_b = 100 - 10 * explosion_j; explosion_b <= 108 - 12 * explosion_j; explosion_b++)
                    leds[explosion_b] = CRGB(settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                for (int explosion_b = 12 * explosion_j; explosion_b <= 99 - 10 * explosion_j; explosion_b += 11)
                    leds[explosion_b] = CRGB(settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
                for (int explosion_b = 10 + 10 * explosion_j; explosion_b <= 109 - 12 * explosion_j; explosion_b += 11)
                    leds[explosion_b] = CRGB(settings.get_explosion_red2(), settings.get_explosion_green2(), settings.get_explosion_blue2());
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
                leds[spiral_sr[spiral_j]] = CRGB(settings.get_spiral_red(), settings.get_spiral_green(), settings.get_spiral_blue());
                spiral_j++;
            }
            else if (spiral_j == led_count - 1 && spiral_p == false && spiral_timestamp2_enabled == false)
            {
                spiral_p = true;
                leds[spiral_sr[spiral_j]] = CRGB(settings.get_spiral_red(), settings.get_spiral_green(), settings.get_spiral_blue());
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
                leds[spiral_sr[spiral_j]] = CRGB(settings.get_spiral_red2(), settings.get_spiral_green2(), settings.get_spiral_blue2());
                spiral_j--;
            }
            else if (spiral_j == 0 && spiral_p == false && spiral_timestamp2_enabled == false)
            {
                spiral_p = true;
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

void Effects::rain()
{
    if (timestamp + 100 < millis())
    {
        // for (int j = 0; j < 110; j++)
        // {
        //     strip.setPixelColor(j, 0, 0, 0);
        // }

        //runterschieben
        bool rain_arr_speichern[11][10];

        for (int i = 0; i < 10; i++)
        {
            for (int x = 0; x < 11; x++)
            {
                rain_arr_speichern[x][i + 1] = rain_arr[x][i];
            }
        }
        for (int i = 0; i < 10; i++)
        {
            for (int x = 0; x < 11; x++)
            {
                rain_arr[x][i] = rain_arr_speichern[x][i];
            }
        }

        for (int x = 0; x < 11; x++)
        {
            rain_arr[x][0] = false;
        }

        for (int i = 0; i < 11; i++)
        {
            int y = 0;
            int rand = random(11);
            if (0 == random(15))
            {
                rain_arr[rand][y] = true;
                for (int j = 0; j <= random(0, 2); j++)
                {
                    y++;
                    rain_arr[rand][y] = true;
                }
            }
        }

        //anzeigen
        for (int x = 0; x < 11; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                if (rain_arr[x][y])
                {
                    leds[y * 11 + x] = CRGB::Purple;
                    
                }
                else
                {
                    leds[y * 11 + x] = CRGB::Black;
                }
            }
        }

        timestamp = millis();
    }
}
