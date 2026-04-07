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
    date_time(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
    date_time(std::string str);

    bool is_valid() const;
    void print() const;
    int get_year() const;
    int get_month() const;
    int get_day() const;

    bool operator < (const date_time& other) const;
    bool operator > (const date_time& other) const;
    bool operator == (const date_time& other) const;
    bool operator != (const date_time& other) const;

    date_time operator + (double days) const;
    date_time operator - (double days) const;
    double operator - (const date_time& other) const;

    std::string get_day_of_week() const;

    friend std::ostream& operator << (std::ostream& os, const date_time& dt);
    friend std::istream& operator >> (std::istream& is, date_time& dt);
};

