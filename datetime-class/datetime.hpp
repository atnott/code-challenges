#pragma once
#include <iostream>

class DateTime {
private:
    int year, month, day;
public:
    DateTime();
    DateTime(int year, int month, int day);

    bool is_valid() const;

    void print();
    int change_day() const;
    static DateTime reverse_change(int jdn);

    int operator - (const DateTime &other);
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
};

