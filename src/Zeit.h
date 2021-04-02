#ifndef ZEIT_H
#define ZEIT_H

#include <Arduino.h>

const int utc = 3600; //offset ins sekunden für utc+1

class Zeit
{
private:
    String weather, zeitsystem;
    int seconds = 0, minutes = 0, hours = 0, dayMonth = 0, dayWeek = 0, month = 0, calendarYear = 0;
    int betterhours;

    void make_betterhours(); //wenn 1:30 dann muss halb *2* und nicht halb 1 stehen

    unsigned long epochTime;
    struct tm *ptm;

public:
    //geheimnisprinzip
    void set_weather(String yes)
    {
        weather = yes;
        //needs decode
    }
    String get_weather()
    {
        return weather;
    }
    void set_zeitsystem(String yes)
    {
        zeitsystem = yes;
    }
    String get_zeitsystem()
    {
        return zeitsystem;
    }
    void set_seconds(int yes)
    {
        seconds = yes;
    }
    int get_seconds()
    {
        return seconds;
    }
    void set_minutes(int yes)
    {
        minutes = yes;
    }
    int get_minutes()
    {
        return minutes;
    }
    void set_hours(int yes)
    {
        hours = yes;
    }
    int get_hours()
    {
        return hours;
    }
    void set_dayMonth(int yes)
    {
        dayMonth = yes;
    }
    int get_dayMonth()
    {
        return dayMonth;
    }
    void set_dayWeek(int yes)
    {
        dayWeek = yes;
    }
    int get_dayWeek()
    {
        return dayWeek;
    }
    void set_month(int yes)
    {
        month = yes;
    }
    int get_month()
    {
        return month;
    }
    void set_calendarYear(int yes)
    {
        calendarYear = yes;
    }
    int get_calendarYear()
    {
        return calendarYear;
    }

    boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours)
    // European Daylight Savings Time calculation by "jurs" for German Arduino Forum
    // input parameters: "normal time" for year, month, day, hour and tzHours (0=UTC, 1=MEZ)
    // return value: returns true during Daylight Saving Time, false otherwise
    {
        if (month < 3 || month > 10)
            return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
        if (month > 3 && month < 10)
            return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
        if (month == 3 && (hour + 24 * day) >= (1 + tzHours + 24 * (31 - (5 * year / 4 + 4) % 7)) || month == 10 && (hour + 24 * day) < (1 + tzHours + 24 * (31 - (5 * year / 4 + 1) % 7)))
            return true;
        else
            return false;
    }

    String update();
};

#endif