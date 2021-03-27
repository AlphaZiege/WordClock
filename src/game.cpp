#include <game.h>
#include <Settings.h>
#include <Adafruit_NeoPixel.h>

extern Snake snake;
extern Adafruit_NeoPixel strip;
extern Settings settings;

void Snake::DrawPixel(Pixel pixel)
{
    int pixelpos = pixel.YPos * width + pixel.XPos;
    strip.setPixelColor(pixelpos, pixel.r, pixel.g, pixel.b);
    //strip.show();
    //Serial.println("Drew " + String(pixel.who) + ": " + String(pixel.YPos * width + pixel.XPos) + " (x: " + String(pixel.XPos) + ", y: " + String(pixel.YPos) + ") with Color: " + String(pixel.color));
}

Direction Snake::ReadMovement(Direction movement)
{
    if (settings.get_snake_dir() != 0)
    {
        //0 = noDir, 1 = up, 2 = left, 3 = right, 4 = down

        if (settings.get_snake_dir() == 1 && movement != Down)
        {
            movement = Up;
        }
        else if (settings.get_snake_dir() == 4 && movement != Up)
        {
            movement = Down;
        }
        else if (settings.get_snake_dir() == 2 && movement != Right)
        {
            movement = Left;
        }
        else if (settings.get_snake_dir() == 3 && movement != Left)
        {
            movement = Right;
        }
        settings.set_snake_dir(0);
        //Serial.println("snake movement: " + String(movement));
    }

    return movement;
}

void Snake::Clear()
{
    for (int i = 0; i < 110; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
        //strip.show();
    }
}

void Snake::initGameover()
{
    Serial.println("Game over, Score: " + String(score));
    timestamp = millis();
    settings.set_colorMode(100);
}

