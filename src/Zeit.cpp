#include <Zeit.h>
#include <Settings.h>
#include <NTPClient.h>

extern Settings settings;
extern NTPClient timeClient;

void Zeit::make_betterhours() //wenn 1:30 dann muss halb *2* und nicht halb 1 stehen
{
    if (minutes >= 18 && settings.get_timeType() == 0)
    {
        betterhours = hours + 1;
    }
    else if (minutes < 18 && settings.get_timeType() == 0)
    {
        betterhours = hours;
    }

    if (minutes >= 12 && settings.get_timeType() == 1)
    {
        betterhours = hours + 1;
    }
    else if (minutes < 12 && settings.get_timeType() == 1)
    {
        betterhours = hours;
    }

    if (betterhours > 12)
    {
        betterhours -= 12;
    }

    if (betterhours == 0)
    {
        betterhours = 12;
    }
    //Serial.println("Betterhours: " + String(betterhours));
    //Serial.println("Minutes: " + String(minutes));
}

String Zeit::update()
{
    String table = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    make_betterhours();
    if (settings.get_clockType() == 0 && settings.get_colorMode() < 100) //buchstaben uhr
    {
        table[0] = '1'; //es ist
        table[1] = '1';
        table[3] = '1';
        table[4] = '1';
        table[5] = '1';

        switch (betterhours)
        {
        case 1:
            table[55] = '1'; //eins
            table[56] = '1';
            table[57] = '1';
            table[58] = '1';
            break;

        case 2:
            table[62] = '1'; //zwei
            table[63] = '1';
            table[64] = '1';
            table[65] = '1';
            break;

        case 3:
            table[66] = '1'; //drei
            table[67] = '1';
            table[68] = '1';
            table[69] = '1';
            break;

        case 4:
            table[73] = '1'; //vier
            table[74] = '1';
            table[75] = '1';
            table[76] = '1';
            break;

        case 5:
            table[51] = 'i'; //fünf
            table[52] = '1';
            table[53] = '1';
            table[54] = '1';
            break;

        case 6:
            table[77] = 'i'; //sechs
            table[78] = '1';
            table[79] = '1';
            table[80] = '1';
            table[81] = '1';
            break;

        case 7:
            table[88] = '1'; //sieben
            table[89] = '1';
            table[90] = '1';
            table[91] = '1';
            table[92] = '1';
            table[93] = '1';
            break;

        case 8:
            table[84] = '1'; //acht
            table[85] = '1';
            table[86] = '1';
            table[87] = '1';
            break;

        case 9:
            table[44] = 'i'; //neun
            table[45] = '1';
            table[46] = '1';
            table[47] = '1';
            break;

        case 10:
            table[99] = 'i'; //zehn
            table[100] = '1';
            table[101] = '1';
            table[102] = '1';
            break;

        case 11:
            table[103] = 'i'; //elf
            table[104] = '1';
            table[105] = '1';
            break;

        case 12:
            table[94] = 'i'; //zwölf
            table[95] = '1';
            table[96] = '1';
            table[97] = '1';
            table[98] = '1';
            break;
        }

        switch (minutes)
        {
        case 0 ... 2:
            if (betterhours == 1)
            {
                table[58] = '0'; //bei ein's' dass s (wird nur bei "es ist ein uhr" nicht gebraucht)
            }
            table[107] = '1'; //uhr
            table[108] = '1';
            table[109] = '1';
            break;

        case 3 ... 7:
            table[7] = '1'; //fünf nach
            table[8] = '1';
            table[9] = '1';
            table[10] = '1';
            table[18] = '1';
            table[19] = '1';
            table[20] = '1';
            table[21] = '1';
            break;

        case 8 ... 12:
            table[11] = '1'; //zehn nach
            table[12] = '1';
            table[13] = '1';
            table[14] = '1';
            table[18] = '1';
            table[19] = '1';
            table[20] = '1';
            table[21] = '1';
            break;

        case 13 ... 17:
            if (settings.get_timeType() == 0) //normale menschen (anto jan)
            {
                table[7] = '1'; //fünfzehn nach
                table[8] = '1';
                table[9] = '1';
                table[10] = '1';
                table[11] = '1';
                table[12] = '1';
                table[13] = '1';
                table[14] = '1';
                table[18] = '1';
                table[19] = '1';
                table[20] = '1';
                table[21] = '1';
            }
            else if (settings.get_timeType() == 1) //timo mit "viertel eins"
            {
                table[25] = '1'; //viertel
                table[26] = '1';
                table[27] = '1';
                table[28] = '1';
                table[29] = '1';
                table[30] = '1';
                table[31] = '1';
            }
            break;

        case 18 ... 22:
            table[11] = '1'; //zehn vor halb
            table[12] = '1';
            table[13] = '1';
            table[14] = '1';
            table[34] = '1';
            table[35] = '1';
            table[36] = '1';
            table[40] = '1';
            table[41] = '1';
            table[42] = '1';
            table[43] = '1';
            break;

        case 23 ... 27:
            table[7] = '1'; //fünf vor halb
            table[8] = '1';
            table[9] = '1';
            table[10] = '1';
            table[34] = '1';
            table[35] = '1';
            table[36] = '1';
            table[40] = '1';
            table[41] = '1';
            table[42] = '1';
            table[43] = '1';
            break;

        case 28 ... 32:
            table[40] = '1'; //halb
            table[41] = '1';
            table[42] = '1';
            table[43] = '1';
            break;

        case 33 ... 37:
            table[7] = '1'; //fünf nach halb
            table[8] = '1';
            table[9] = '1';
            table[10] = '1';
            table[18] = '1';
            table[19] = '1';
            table[20] = '1';
            table[21] = '1';
            table[40] = '1';
            table[41] = '1';
            table[42] = '1';
            table[43] = '1';
            break;

        case 38 ... 42:
            table[11] = '1'; //zehn nach halb
            table[12] = '1';
            table[13] = '1';
            table[14] = '1';
            table[18] = '1';
            table[19] = '1';
            table[20] = '1';
            table[21] = '1';
            table[40] = '1';
            table[41] = '1';
            table[42] = '1';
            table[43] = '1';
            break;

        case 43 ... 47:
            table[25] = '1'; //viertel vor
            table[26] = '1';
            table[27] = '1';
            table[28] = '1';
            table[29] = '1';
            table[30] = '1';
            table[31] = '1';
            table[34] = '1';
            table[35] = '1';
            table[36] = '1';
            break;

        case 48 ... 52:
            table[11] = '1'; //zehn vor
            table[12] = '1';
            table[13] = '1';
            table[14] = '1';
            table[34] = '1';
            table[35] = '1';
            table[36] = '1';
            break;

        case 53 ... 57:
            table[7] = '1'; //fünf vor
            table[8] = '1';
            table[9] = '1';
            table[10] = '1';
            table[34] = '1';
            table[35] = '1';
            table[36] = '1';
            break;

        case 58 ... 62:
            //gleich wie 0 ... 2
            table[58] = '0'; //bei ein's' das s (wird nur bei nicht "es ist ein uhr" gebraucht)

            table[107] = '1';
            table[108] = '1';
            table[109] = '1';
            break;
        }
    }

    else /*if (settings.get_clockType() == 1)*/ //lampe uhr
    {
        return "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    }
    return table;
}

