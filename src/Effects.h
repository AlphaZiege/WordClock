#ifndef EFFECTS_H
#define EFFECTS_H

#include <Arduino.h>

class Effects
{
private:
    unsigned long timestamp, timestamp2;

    //breathe
    bool fade_in = true;
    int breathe_index = 0, breath_multiplikator;

    //colorCycle
    int R, G, B;
    bool rup = true, gup = false, bup = false;

    //explosion
    int explosion_i = 0, explosion_j = 0, explosion_b = 0;
    bool explosion_geht_an = true, explosion_timestamp2_enabled = false, explosion_p = false;

    //theme
    int counter = 0;

    //spiral
    int spiral_i = 0, spiral_j = 0;
    bool spiral_geht_an = true, spiral_timestamp2_enabled = false, spiral_p = false;                                                                                                                                                                                                                                                                                                                                                                                                                                               //timestamp1 für Pausen zwischen den einzelnen LEDs, timestamp 2 für Pause zwsichen angehen und ausgehen
    uint8_t spiral_sr[110] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 21, 32, 43, 54, 65, 76, 87, 98, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 88, 77, 66, 55, 44, 33, 22, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 31, 42, 53, 64, 75, 86, 97, 96, 95, 94, 93, 92, 91, 90, 89, 78, 67, 56, 45, 34, 23, 24, 25, 26, 27, 28, 29, 30, 41, 52, 63, 74, 85, 84, 83, 82, 81, 80, 79, 68, 57, 46, 35, 36, 37, 38, 39, 40, 51, 62, 73, 72, 71, 70, 69, 58, 47, 48, 49, 50, 61, 60, 59}; // Alle LED's der Wordclock in der Reihenfolge, dass sie beim nacheinander abspielen eine Spirale ergeben

public:
    void staticColor();

    void breathe();

    void colorCycle();

    void rainbowCycle();

    void fire()
    {
    }

    void saison(String theme);

    void explosion();

    void spiral();
};
#endif