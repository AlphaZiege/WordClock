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

    String update();
};

#endif