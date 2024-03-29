#include <Effects.h>
#include <Adafruit_NeoPixel.h>
#include <Settings.h>

const int led_count = 110;

extern Adafruit_NeoPixel strip;
extern Settings settings;

void Effects::setAllLEDs(int r, int g, int b)
{
    for (int i = 0; i < led_count; i++)
    {
        strip.setPixelColor(i, r, g, b);
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
                    strip.setPixelColor(i, 255, 255 - (i * 2.34), 255 - (i * 2.34));
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 2500 > millis() and timestamp + 1500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    strip.setPixelColor(i, 255, 200 - (i * 1.83), 200 - (i * 1.83));
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 3500 > millis() and timestamp + 2500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    strip.setPixelColor(i, 255, 150 - (i * 1.38), 150 - (i * 1.38));
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 4500 > millis() and timestamp + 3500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    strip.setPixelColor(i, 255, 100 - (i * 0.92), 100 - (i * 0.92));
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 5500 > millis() and timestamp + 4500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    strip.setPixelColor(i, 255, 50 - (i * 0.46), 50 - (i * 0.46));
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 9500 > millis() and timestamp + 5500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(2) == 1)
                {
                    strip.setPixelColor(i, 0xFF0000);
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 10500 > millis() and timestamp + 9500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(3) == 1)
                {
                    strip.setPixelColor(i, 0xFF0000);
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 11500 > millis() and timestamp + 10500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(4) == 1)
                {
                    strip.setPixelColor(i, 0xFF0000);
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 12500 > millis() and timestamp + 11500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(6) == 1)
                {
                    strip.setPixelColor(i, 0xFF0000);
                }
                if (random(20) == 1)
                {
                    setAllLEDs(0, 255, 0);
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 11500 > millis() and timestamp + 10500 < millis())
        {
            for (int i = 0; i < led_count; i++)
            {
                if (random(10) == 1)
                {
                    strip.setPixelColor(i, 0xFF0000);
                }
                else
                    strip.setPixelColor(i, 0x0);
            }
        }
        if (timestamp + 11800 > millis() and timestamp + 11500 < millis())
        {
            strip.setPixelColor(25, 255, 0, 0);
            strip.setPixelColor(29, 255, 0, 0);
            strip.setPixelColor(68, 255, 0, 0);
            strip.setPixelColor(80, 255, 0, 0);
            strip.setPixelColor(92, 255, 0, 0);
            strip.setPixelColor(93, 255, 0, 0);
            strip.setPixelColor(94, 255, 0, 0);
            strip.setPixelColor(84, 255, 0, 0);
            strip.setPixelColor(74, 255, 0, 0);
        }
        if (timestamp + 12000 > millis() and timestamp + 11800 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 14800 > millis() and timestamp + 12000 < millis())
        {
            strip.setPixelColor(25, 255, 0, 0);
            strip.setPixelColor(29, 255, 0, 0);
            strip.setPixelColor(68, 255, 0, 0);
            strip.setPixelColor(80, 255, 0, 0);
            strip.setPixelColor(92, 255, 0, 0);
            strip.setPixelColor(93, 255, 0, 0);
            strip.setPixelColor(94, 255, 0, 0);
            strip.setPixelColor(84, 255, 0, 0);
            strip.setPixelColor(74, 255, 0, 0);
        }
        if (timestamp + 14900 > millis() and timestamp + 14800 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 15000 > millis() and timestamp + 14900 < millis())
        {
            strip.setPixelColor(25, 255, 0, 0);
            strip.setPixelColor(29, 255, 0, 0);
            strip.setPixelColor(68, 255, 0, 0);
            strip.setPixelColor(80, 255, 0, 0);
            strip.setPixelColor(92, 255, 0, 0);
            strip.setPixelColor(93, 255, 0, 0);
            strip.setPixelColor(94, 255, 0, 0);
            strip.setPixelColor(84, 255, 0, 0);
            strip.setPixelColor(74, 255, 0, 0);
        }
        if (timestamp + 15100 > millis() and timestamp + 15000 < millis())
        {
            setAllLEDs(0, 0, 0);
        }
        if (timestamp + 18000 > millis() and timestamp + 15100 < millis())
        {
            strip.setPixelColor(25, 255, 0, 0);
            strip.setPixelColor(29, 255, 0, 0);
            strip.setPixelColor(68, 255, 0, 0);
            strip.setPixelColor(80, 255, 0, 0);
            strip.setPixelColor(92, 255, 0, 0);
            strip.setPixelColor(93, 255, 0, 0);
            strip.setPixelColor(94, 255, 0, 0);
            strip.setPixelColor(84, 255, 0, 0);
            strip.setPixelColor(74, 255, 0, 0);
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
            strip.setBrightness(breathe_index);
            setAllLEDs(settings.get_breathe_RED() * breath_multiplikator, settings.get_breathe_GREEN() * breath_multiplikator, settings.get_breathe_BLUE() * breath_multiplikator);
            breathe_index++;
            if (breathe_index >= settings.get_brightestBreatheColor())
                fade_in = false;
        }
        else
        {
            strip.setBrightness(breathe_index);
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

    if (rup)
        R++;
    else if (gup)
        G++;
    else if (bup)
        B++;
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
        R--;
    else if (!gup && G != 0)
        G--;
    else if (!bup && B != 0)
        B--;

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
    // yes
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
                strip.setPixelColor(spiral_sr[spiral_j], settings.get_spiral_red(), settings.get_spiral_green(), settings.get_spiral_blue());
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

        // runterschieben
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

        // anzeigen
        for (int x = 0; x < 11; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                if (rain_arr[x][y])
                {
                    strip.setPixelColor(y * 11 + x, 0xFF00FF);
                }
                else
                {
                    strip.setPixelColor(y * 11 + x, 0x0);
                }
            }
        }

        timestamp = millis();
    }
}

void Effects::noise()
{
    noiseColor.r = settings.get_noise_red();
    noiseColor.g = settings.get_noise_green();
    noiseColor.b = settings.get_noise_blue();
    noiseDelay = settings.get_noise_delay();
    noiseRange = settings.get_noise_range();
    rangeUpper = 100 + noiseRange;
    rangeLower = 100 - noiseRange;
    rangeLower = (rangeLower < 0 ? 0 : rangeLower);

    for (int i = 0; i < 110; i++)
    {
        if (pixels[i].transitionFinished)
        {
            pixels[i].transitionDuration = random(noiseDelay * 0.75, noiseDelay * 1.5);
            pixels[i].transitionFinished = false;
            pixels[i].stepTime = pixels[i].transitionDuration / 20;
            pixels[i].currentStep = 0;

            pixels[i].oldcolor = pixels[i].color;
            pixels[i].color = noisyColor(noiseColor);
        }
        if (pixels[i].timestamp + pixels[i].transitionDuration < millis())
        {
            pixels[i].transitionFinished = true;
            pixels[i].timestamp = millis();
        }
    }

    for (int i = 0; i < 110; i++)
    {
        FadeCalc(pixels[i]);
        strip.setPixelColor(i, pixels[i].currentColor.r, pixels[i].currentColor.g, pixels[i].currentColor.b);
    }
}

Effects::colors Effects::noisyColor(colors normalColor)
{
    int r, g, b;
    r = random(normalColor.r * rangeLower, normalColor.r * rangeUpper) / 100;
    g = random(normalColor.g * rangeLower, normalColor.g * rangeUpper) / 100;
    b = random(normalColor.b * rangeLower, normalColor.b * rangeUpper) / 100;
    r = (r > 255 ? 255 : r);
    g = (g > 255 ? 255 : g);
    b = (b > 255 ? 255 : b);
    return {r, g, b};
}

void Effects::FadeCalc(noiseColors &pixel)
{
    if (pixel.timestamp2 + pixel.stepTime < millis())
    {
        pixel.currentStep++;
        int diffColor_r;
        int diffColor_g;
        int diffColor_b;

        diffColor_r = pixel.color.r - pixel.oldcolor.r;
        diffColor_g = pixel.color.g - pixel.oldcolor.g;
        diffColor_b = pixel.color.b - pixel.oldcolor.b;
        pixel.currentColor.r = pixel.oldcolor.r + (diffColor_r * ((float)pixel.currentStep / 20));
        pixel.currentColor.g = pixel.oldcolor.g + (diffColor_g * ((float)pixel.currentStep / 20));
        pixel.currentColor.b = pixel.oldcolor.b + (diffColor_b * ((float)pixel.currentStep / 20));
        pixel.timestamp2 = millis();
    }
}