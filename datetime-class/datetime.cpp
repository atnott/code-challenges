#include"datetime.hpp"

DateTime::DateTime() {
    year = 2026;
    month = 3;
    day = 30;
}

DateTime::DateTime(int year, int month, int day) : year(year), month(month), day(day) {
    if (!is_valid()) {
        year = 2026;
        month = 3;
        day = 30;
        std::cout << "uncorrect date" << std::endl;
    }
}

void DateTime::print() {
    std::cout << day << '.' << month << '.' << year << std::endl;
}

int DateTime::change_day() const {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    int jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn;
}

DateTime DateTime::reverse_change(int jdn) {
    int f = jdn + 1401 + ((3 * (4 * jdn + 274277) / 146097) / 4) - 38;
    int e = f * 4 + 3;
    int g = (e % 1461) / 4;
    int h = 5 * g + 2;

    int d = (h % 153) / 5 + 1;
    int m = ((h / 153) + 2) % 12 + 1;
    int y = (e / 1461) - 4716 + (14 - m) / 12;
    return DateTime(y, m, d);
}

int DateTime::operator - (const DateTime &other) {
    return this->change_day() - other.change_day();
}

bool DateTime::is_valid() const {
    if (month < 1 || month > 12) return false;
    if (year < 0) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) daysInMonth[1] = 29;
    }
    if (day < 1 || day > daysInMonth[month - 1]) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    os << dt.day << '.' << dt.month << '.' << dt.year << std::endl;
    return os;
}