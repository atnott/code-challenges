#include"datetime.hpp"

date_time::date_time() {
    year = 2026;
    month = 3;
    day = 30;
    hour = 0;
    minute = 0;
    second = 0;
}

date_time::date_time(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
    if (!is_valid()) {
        std::cerr << "invalid date! resetting to 2026-01-01" << std::endl;
        this->year = 2026; this->month = 1; this->day = 1;
        this->hour = 0; this->minute = 0; this->second = 0;
    }
}

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

date_time date_time::from_jdn(double jdn) {
    int int_jdn = static_cast<int>(jdn);
    double fractional_jdn = jdn - int_jdn;

    int f = int_jdn + 1401 + ((3 * (4 * int_jdn + 274277) / 146097) / 4) - 38;
    int e = f * 4 + 3;
    int g = (e % 1461) / 4;
    int h = 5 * g + 2;

    int d = (h % 153) / 5 + 1;
    int m = ((h / 153) + 2) % 12 + 1;
    int y = (e / 1461) - 4716 + (14 - m) / 12;

    int total_seconds = std::round(fractional_jdn * 86400);
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    return date_time(y, m, d, hours, minutes, seconds);
}

date_time date_time::operator + (double days) const {
    double jdn = this->to_jdn();
    double result = jdn + days;
    return from_jdn(result);
}

void date_time::print() const{
    std::cout << year << "-";
    for_print(month);
    std::cout << "-";
    for_print(day);
    std::cout << "T";
    for_print(hour);
    std::cout << ":";
    for_print(minute);
    std::cout << ":";
    for_print(second);
    std::cout << std::endl;
}

void date_time::for_print(int temp) const{
    if (temp < 10) std::cout << 0;
    std::cout << temp;
}

date_time date_time::operator - (double days) const {
    double jdn = this->to_jdn();
    double result = jdn - days;
    return from_jdn(result);
}

double date_time::operator - (const date_time& other) const {
    double jdn1 = this->to_jdn();
    double jdn2 = other.to_jdn();
    return std::abs(jdn1 - jdn2);
}

std::string date_time::get_day_of_week() const {
    static std::string days[] = {
        "Понедельник",
        "Вторник",
        "Среда",
        "Четверг",
        "Пятница",
        "Суббота",
        "Воскресенье"
    };
    int jdn = static_cast<int>(this->to_jdn());
    return days[jdn % 7];
}