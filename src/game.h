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
    void Calc();

public:
    Snake()
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
            // gameover |= (head.XPos == width || head.XPos == -1 || head.YPos == height || head.YPos == -1);

            for (int i = 0; i < bodyLenght; i++)
            {
                DrawPixel(body[i]);
                gameover |= (body[i].XPos == head.XPos && body[i].YPos == head.YPos);
            }

            if (food.XPos == head.XPos && food.YPos == head.YPos)
            {
                score++;

                int x = random(0, width);
                int y = random(0, height);

                bool isFoodValid = false;
                do
                {
                    // spawn food
                    x = random(0, width);
                    y = random(0, height);
                    // check if food in snake
                    for (int i = 0; i < bodyLenght; i++)
                    {
                        if ((x == body[i].XPos && y == body[i].YPos) ||
                            (x == head.XPos && y == head.YPos))
                            isFoodValid = false;
                        else
                            isFoodValid = true;
                    }
                } while (!isFoodValid);

                food.XPos = x;
                food.YPos = y;
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

class TicTacToe
{
private:
    int grid[38] = {3, 14, 25, 36, 47, 58, 69, 80, 91, 102, 7, 18, 29, 40, 51, 62, 73, 84, 95, 106, 33, 34, 35, 37, 38, 39, 41, 42, 43, 77, 78, 79, 81, 82, 83, 85, 86, 87};
    int field[9][10] = {{0, 0, 1, 2, 11, 12, 13, 22, 23, 24}, {0, 4, 5, 6, 15, 16, 17, 26, 27, 28}, {0, 8, 9, 10, 19, 20, 21, 30, 31, 32}, {0, 44, 45, 46, 55, 56, 57, 66, 67, 68}, {0, 48, 49, 50, 59, 60, 61, 70, 71, 72}, {0, 52, 53, 54, 63, 64, 65, 74, 75, 76}, {0, 88, 89, 90, 99, 100, 101, -1, -1, -1}, {0, 92, 93, 94, 103, 104, 105, -1, -1, -1}, {0, 96, 97, 98, 107, 108, 109, -1, -1, -1}};
    int player;
    void DrawGrid(int r, int g, int b);
    int Field();
    void Clear();
    void Win(int who);
    bool Play(int where, int who);
    unsigned long timestamp;
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    Color P1;
    Color P2;
    Color Cgrid;

public:
    TicTacToe()
    {
        P1 = Color();
        P1.r = 255;
        P1.g = 72;
        P1.b = 0;
        P2 = Color();
        P2.r = 0;
        P2.g = 107;
        P2.b = 255;
        Cgrid = Color();
        Cgrid.r = 255;
        Cgrid.g = 0;
        Cgrid.b = 0;
        Clear();
        DrawGrid(Cgrid.r, Cgrid.g, Cgrid.b);
        player = 1;
    }
    void Loop()
    {
        if (
            (field[0][0] == field[1][0] && field[1][0] == field[2][0] && field[0][0] != 0) ||
            (field[3][0] == field[4][0] && field[4][0] == field[5][0] && field[3][0] != 0) ||
            (field[6][0] == field[7][0] && field[7][0] == field[8][0] && field[6][0] != 0) ||
            (field[0][0] == field[3][0] && field[3][0] == field[6][0] && field[0][0] != 0) ||
            (field[1][0] == field[4][0] && field[4][0] == field[7][0] && field[1][0] != 0) ||
            (field[2][0] == field[5][0] && field[5][0] == field[8][0] && field[2][0] != 0) ||
            (field[0][0] == field[4][0] && field[4][0] == field[8][0] && field[0][0] != 0) ||
            (field[2][0] == field[4][0] && field[4][0] == field[6][0] && field[2][0] != 0))
        {
            if (player == 1)
            {
                Win(2);
            }
            if (player == 2)
            {
                Win(1);
            }
        }
        else if (field[0][0] != 0 && field[1][0] != 0 && field[2][0] != 0 && field[3][0] != 0 && field[4][0] != 0 && field[5][0] != 0 && field[6][0] != 0 && field[7][0] != 0 && field[8][0] != 0)
        {
            Win(3);
        }
        else if (Field() != 0)
        {
            if (Play(Field(), player))
            {
                if (player == 1)
                {
                    player = 2;
                    // Serial.println("player set to 2");
                }
                else if (player == 2)
                {
                    player = 1;
                    // Serial.println("player set to 1");
                }
            }
            timestamp = millis();
        }
    }
};

#endif