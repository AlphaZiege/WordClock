bool checkValidity(bool Kodierung[62])
{/*
    bool outside_range = true;
    //outside range check
    int Minute = Kodierung[22] + 2 * Kodierung[23] + 4 * Kodierung[24] + 8 * Kodierung[25] + 10 * Kodierung[26] + 20 * Kodierung[27] + 40 * Kodierung[28];
    int Stunde = Kodierung[30] + 2 * Kodierung[31] + 4 * Kodierung[32] + 8 * Kodierung[33] + 10 * Kodierung[34] + 20 * Kodierung[35];
    int Tag = Kodierung[37] + 2 * Kodierung[38] + 4 * Kodierung[39] + 8 * Kodierung[40] + 10 * Kodierung[41] + 20 * Kodierung[42];
    int Monat = Kodierung[46] + 2 * Kodierung[47] + 4 * Kodierung[48] + 8 * Kodierung[49] + 10 * Kodierung[50];
    int Jahr = Kodierung[51] + 2 * Kodierung[52] + 4 * Kodierung[53] + 8 * Kodierung[54] + 10 * Kodierung[55] + 20 * Kodierung[56] + 40 * Kodierung[57] + 80 * Kodierung[58];

    if (Minute > 59) outside_range = false;
    if (Stunde > 23) outside_range = false;
    if (Tag == 0 ||Tag > 31) outside_range = false;
    if (Monat == 0 || Monat > 12) outside_range = false;
    if (Jahr < 2020) outside_range = false;
*/
    // parity check
    bool minute_parity = false;
    bool hour_parity = false;
    // minute parity check
    for (int i = 22; i < 29; i++)
    {
        if (Kodierung[i])
            minute_parity = !minute_parity;
    }
    if (minute_parity == Kodierung[29])
        minute_parity = true;
    // hour parity check
    for (int i = 30; i < 36; i++)
    {
        if (Kodierung[i])
            hour_parity = !hour_parity;
    }
    if (hour_parity == Kodierung[36])
        hour_parity = true;

    return (minute_parity && hour_parity && outside_range);
}