#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

enum Direction
{
    Up,
    Down,
    Right,
    Left
};

class Snake
{
private:
    int height = 10;
    int width = 11;

    struct Pixel
    {
        int XPos;
        int YPos;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        char who;
    };

    void DrawPixel(Pixel pixel);

    Direction ReadMovement(Direction movement);

    void Clear();

    void Gameover();

    Pixel head;
    Pixel food;
    Pixel body[110];
    Direction currentMovement = Right;
    int score = 5;
    bool gameover = false;
    int bodyLenght = 0;
    bool loopAllowed;
    unsigned long timestamp;

public:
    void init()
    {
        head = Pixel();
        food = Pixel();
        score = 0;
        head.XPos = width / 2;
        head.YPos = height / 2;
        head.r = 0;
        head.g = 255;
        head.b = 0;
        head.who = 'h';
        food.XPos = random(1, width - 2);
        food.YPos = random(1, height - 2);
        food.r = 255;
        food.g = 0;
        food.b = 0;
        food.who = 'f';
        gameover = false;
        bodyLenght = 0;
        currentMovement = Right;
        loopAllowed = true;
    }

    void loop()
    {
        if (loopAllowed)
        {
            Clear();
            //penis
            //gameover |= (head.XPos == width || head.XPos == -1 || head.YPos == height || head.YPos == -1);

            for (int i = 0; i < bodyLenght; i++)
            {
                DrawPixel(body[i]);
                gameover |= (body[i].XPos == head.XPos && body[i].YPos == head.YPos);
            }

            if (food.XPos == head.XPos && food.YPos == head.YPos)
            {
                score++;
                food.XPos = random(0, width);
                food.YPos = random(0, height);
                //maybe add if (food spawned in head or body?) make new food
            }

            if (gameover)
            {
                Gameover();
            }

            DrawPixel(head);
            DrawPixel(food);
            timestamp = millis();
            loopAllowed = false;
        }

        if (timestamp + 200 >= millis())
        {
            currentMovement = ReadMovement(currentMovement);
        }
        else
        {
            loopAllowed = true;
        }

        if (loopAllowed)
        {
            body[bodyLenght] = Pixel();
            body[bodyLenght].XPos = head.XPos;
            body[bodyLenght].YPos = head.YPos;
            body[bodyLenght].r = 0;
            body[bodyLenght].g = 0;
            body[bodyLenght].b = 255;
            body[bodyLenght].who = 'b';
            bodyLenght++;

            switch (currentMovement)
            {
            case Up:
                head.YPos--;
                if (head.YPos < 0)
                    head.YPos = height - 1;
                break;
            case Down:
                head.YPos++;
                if (head.YPos > height - 1)
                    head.YPos = 0;
                break;
            case Left:
                head.XPos--;
                if (head.XPos < 0)
                    head.XPos = width - 1;
                break;
            case Right:
                head.XPos++;
                if (head.XPos > width - 1)
                    head.XPos = 0;
                break;
            }

            if (bodyLenght > score)
            {
                for (int i = 0; i < bodyLenght; i++)
                {
                    body[i] = body[i + 1];
                }
                bodyLenght--;
            }
        }
    }

    void GameoverLoop();
};

#endif