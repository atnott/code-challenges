#include"datetime.hpp"

date_time::date_time() {
    year = 2026;
    month = 3;
    day = 30;
    hour = 0;
    minute = 0;
    second = 0;
}

date_time::date_time(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}

date_time::date_time(std::string str) {
    std::string arr[6]{"", "", "", "", "", ""};
    int cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'T' || str[i] == '-' || str[i] == ':') {
            cnt++;
            continue;
        }
        arr[cnt] += str[i];
    }
    year = std::stoi(arr[0]);
    month = std::stoi(arr[1]);
    day = std::stoi(arr[2]);
    hour = std::stoi(arr[3]);
    minute = std::stoi(arr[4]);
    second = std::stoi(arr[5]);
    if (!is_valid()) {
        std::cerr << "invalid date! resetting to 2026-01-01" << std::endl;
        year = 2026; month = 1; day = 1;
        hour = 0; minute = 0; second = 0;
    }
}

bool date_time::is_valid() const {
    if (year < 0) return false;
    if (month < 1 || month > 12) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    if (second < 0 || second > 59) return false;
    int days_in_month[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (is_leap) days_in_month[1] = 29;
    }
    if (day < 1 || day > days_in_month[month - 1]) return false;
    return true;
}

double date_time::to_jdn() const {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    double jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn + (hour / 24.0) + (minute / 1440.0) + (second / 86400.0);
}

bool date_time::operator < (const date_time& other) const {
    return this->to_jdn() < other.to_jdn();
}

bool date_time::operator > (const date_time& other) const {
    return other < *this;
}

bool date_time::operator == (const date_time& other) const {
    return this->to_jdn() == other.to_jdn();
}

bool date_time::operator != (const date_time& other) const {
    return !(*this == other);
}