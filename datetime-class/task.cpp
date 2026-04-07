#include<iostream>
#include"datetime.hpp"
#include<fstream>
#include <iomanip>
#include <filesystem>
#include<string>

namespace fs = std::filesystem;

class Moon {
private:
    date_time dt;

public:
    Moon() {
        std::cout << "enter your date: yyyy-mm-ddThh:mm:ss" << std::endl;
        std::cin >> dt;
    }
    Moon(int year, int month, int day) : dt(year, month, day) {}

    void print() {
        std::cout << dt << std::endl;
    }

    std::string get_name_file_by_year() {
        char buffer[64];
        std::snprintf(buffer,  sizeof(buffer), "moon/moon%04d.dat", dt.get_year());
        std::cout << buffer << std::endl;
        return buffer;
    }

    void calculate_events() {
        std::ifstream file(get_name_file_by_year());

        if (!file.is_open()) {
            std::cout << "ОШИБКА: Не могу открыть файл " << std::endl;
            return;
        }

        std::string header; // скипаем заголовочную строку
        std::getline(file, header);

        std::string rise = "--:--:--", set = "--:--:--", culm_time = "--:--:--";
        double max_el = -999.0;
        double prev_el = -999.0;

        std::string ymd;
        std::string hms;
        double t, r, el, az, fi, lg;

        while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
            if (prev_el != -999.0 && prev_el < 0 && el >= 0) {
                rise = hms;
            }
            if (prev_el != -999.0 && prev_el > 0 && el <= 0) {
                set = hms;
            }
            if (el > max_el) {
                max_el = el;
                culm_time = hms;
            }
            prev_el = el;
        }
        std::cout << dt << std::endl;
        std::cout << "Восход Луны: " << rise << std::endl;
        std::cout << "Кульминация Луны: " << culm_time << " (El: " << max_el << ")" << std::endl;
        std::cout << "Заход Луны: " << set << std::endl;
    }
};

int main() {
    using namespace std;
    Moon m(2001, 01, 01);
    m.calculate_events();
}