#include"datetime.hpp"

date_time::date_time() {
    year = 2026;
    month = 3;
    day = 30;
}

date_time::date_time(int year, int month, int day) : year(year), month(month), day(day) {
    if (!is_valid()) {
        year = 2026;
        month = 3;
        day = 30;
        std::cout << "uncorrect date" << std::endl;
    }
}

date_time::date_time(std::string str) {
    std::string str_year, str_month, str_day;
    int temp = 0;
    int cnt = 0;
    while (temp != str.length()) {
        if (str[temp] == '-') {
            cnt++;
            temp++;
            continue;
        }
        if (cnt < 1) str_year += str[temp];
        else if (cnt == 1) str_month += str[temp];
        else if (cnt == 2) str_day += str[temp];
        else if (cnt == 3) {
            std::cout << "overflow" << std::endl;
            break;
        }
        temp++;
    }
    try {
        year = atoi(str_year.c_str());
        month = atoi(str_month.c_str());
        day = atoi(str_day.c_str());
    }
    catch (...) {
        std::cout << "error" << std::endl;
        year = 2026;
        month = 3;
        day = 30;
    }
    if (!is_valid()) {
        year = 2026;
        month = 3;
        day = 30;
    }
}

void date_time::print() {
    std::cout << day << '.' << month << '.' << year << std::endl;
}

int date_time::change_day() const {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    int jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn;
}

date_time date_time::reverse_change(int jdn) {
    int f = jdn + 1401 + ((3 * (4 * jdn + 274277) / 146097) / 4) - 38;
    int e = f * 4 + 3;
    int g = (e % 1461) / 4;
    int h = 5 * g + 2;

    int d = (h % 153) / 5 + 1;
    int m = ((h / 153) + 2) % 12 + 1;
    int y = (e / 1461) - 4716 + (14 - m) / 12;
    return date_time(y, m, d);
}

int date_time::operator - (const date_time &other) {
    return this->change_day() - other.change_day();
}

bool date_time::is_valid() const {
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

std::ostream& operator<<(std::ostream& os, const date_time& dt) {
    os << dt.day << '.' << dt.month << '.' << dt.year << std::endl;
    return os;
}