#pragma once
#include <iostream>
#include<string>

class date_time {
private:
    int year, month, day, hour, minute, second;
public:
    date_time();
    date_time(int year, int month, int day, int hour, int minute, int second);
    date_time(std::string str);

    bool is_valid() const;
};

