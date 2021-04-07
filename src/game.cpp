#include <game.h>
#include <Settings.h>
#include <Adafruit_NeoPixel.h>

//extern Snake snake;
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
        Calc();
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

void Snake::Gameover()
{
    Serial.println("Game over, Score: " + String(score));
    timestamp = millis();
    settings.set_colorMode(102);
}

void Snake::GameoverLoop()
{
    //Serial.println("Gameover Loop: timestamp:" + String(timestamp) + " millis(): " + String(millis()));
    if (timestamp + 1000 > millis() and timestamp + 500 < millis())
    {
        strip.setBrightness(1);
    }
    if (timestamp + 1500 > millis() and timestamp + 1000 < millis())
    {
        strip.setBrightness(settings.get_brightness());
    }
    if (timestamp + 2000 > millis() and timestamp + 1500 < millis())
    {
        strip.setBrightness(1);
    }
    if (timestamp + 2500 > millis() and timestamp + 2000 < millis())
    {
        strip.setBrightness(settings.get_brightness());
    }
    if (timestamp + 3000 > millis() and timestamp + 2500 < millis())
    {
        strip.setBrightness(1);
    }
    if (timestamp + 3500 > millis() and timestamp + 3000 < millis())
    {
        strip.setBrightness(settings.get_brightness());
        settings.set_colorMode(100);
    }
    Serial.println(String(strip.getBrightness()));
}

void Snake::Calc(){

    if (settings.get_SC_DELAY() == 333){
        settings.set_SC_DELAY(0);
        Serial.println("sssss");
    }
    if (head.XPos == 0 && head.YPos == 0){
        settings.set_SC_DELAY(420);
        Serial.println("yyyy");
    }
}

void TicTacToe::DrawGrid(int r, int g, int b)
{
    for (int i = 0; i < 38; i++)
    {
        strip.setPixelColor(grid[i], r, g, b);
    }
}

void TicTacToe::Clear()
{
    for (int i = 0; i < 110; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
}

int TicTacToe::Field()
{
    return settings.get_tictactoe_field();
}

bool TicTacToe::Play(int where, int who)
{
    if (field[where - 1][0] == 0)
    {
        field[where - 1][0] = who;
        for (int i = 1; i < 10; i++)
        {
            if (who == 1)
            {
                strip.setPixelColor(field[where - 1][i], P1.r, P1.g, P1.b);
            }
            if (who == 2)
            {
                strip.setPixelColor(field[where - 1][i], P2.r, P2.g, P2.b);
            }
        }
        Serial.println("Array: " + String(where - 1) + " set to: " + String(field[where - 1][0]));
        return true;
    }
    else
        //Serial.println("No Array player set");
        return false;
}

void TicTacToe::Win(int who)
{
    int r = 0, g = 255, b = 0;
    if (who == 1)
    {
        r = P1.r;
        g = P1.g;
        b = P1.b;
    }
    if (who == 2)
    {
        r = P2.r;
        g = P2.g;
        b = P2.b;
    }
    if (timestamp + 1000 > millis() and timestamp + 500 < millis())
    {
        DrawGrid(r, g, b);
    }
    if (timestamp + 1500 > millis() and timestamp + 1000 < millis())
    {
        DrawGrid(Cgrid.r, Cgrid.g, Cgrid.b);
    }
    if (timestamp + 2000 > millis() and timestamp + 1500 < millis())
    {
        DrawGrid(r, g, b);
    }
    if (timestamp + 2500 > millis() and timestamp + 2000 < millis())
    {
        DrawGrid(Cgrid.r, Cgrid.g, Cgrid.b);
    }
    if (timestamp + 3000 > millis() and timestamp + 2500 < millis())
    {
        DrawGrid(r, g, b);
    }
    if (timestamp + 3500 > millis() and timestamp + 3000 < millis())
    {
        DrawGrid(Cgrid.r, Cgrid.g, Cgrid.b);
        settings.set_colorMode(103);
    }
}