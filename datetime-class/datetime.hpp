#pragma once
#include <iostream>
#include<string>

class date_time {
private:
    int year, month, day, hour, minute, second;
    void for_print(int temp) const;
    double to_jdn() const;
    static date_time from_jdn(double jdn);
public:
    date_time();
    date_time(int year, int month, int day, int hour, int minute, int second);
    date_time(std::string str);

    bool is_valid() const;
    void print() const;

    bool operator < (const date_time& other) const;
    bool operator > (const date_time& other) const;
    bool operator == (const date_time& other) const;
    bool operator != (const date_time& other) const;

    date_time operator + (double days) const;
    date_time operator - (double days) const;
    double operator - (const date_time& other) const;

    std::string get_day_of_week() const;
};

