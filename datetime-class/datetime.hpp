#pragma once
#include <iostream>
#include<string>

class date_time {
private:
    int year, month, day;
public:
    date_time();
    date_time(int year, int month, int day);
    date_time(std::string str);

    bool is_valid() const;

    void print();
    int change_day() const;
    static date_time reverse_change(int jdn);

    int operator - (const date_time &other);
    friend std::ostream& operator<<(std::ostream& os, const date_time& dt);
};

