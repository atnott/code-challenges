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
        std::cout << "enter your date: yyyy-mm-dd" << std::endl;
        std::cin >> dt;
    }
    Moon(int year, int month, int day) : dt(year, month, day) {}

    void print() {
        std::cout << dt << std::endl;
    }

    std::string get_name_file_by_year() {
        char buffer[64];
        std::snprintf(buffer, sizeof(buffer), "moon/moon%04d.dat", dt.get_year());
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

        std::string rise = "not found", set = "not found", culm_time = "not found";
        double max_el = -INT8_MAX;
        double prev_el = -INT8_MAX;

        long ymd;
        std::string hms;
        double t, r, el, az, fi, lg;

        long tarhet_date = dt.get_year() * 10000 + dt.get_month() * 100 + dt.get_day();

        while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
            hms = hms.substr(0, 2) + ':' + hms.substr(2, 2) + ':' + hms.substr(4, 2);

            if (ymd > tarhet_date) break;
            if (ymd < tarhet_date) continue;

            if (prev_el != -INT8_MAX && prev_el < 0 && el >= 0) {
                rise = hms;
            }
            if (prev_el != -INT8_MAX && prev_el > 0 && el <= 0) {
                set = hms;
            }
            if (el > max_el) {
                max_el = el;
                culm_time = hms;
            }
            prev_el = el;
        }
        print_results(rise, set, culm_time, max_el);
    }
    void print_results(std::string rise, std::string set, std::string culm_time, double max_el) {
        std::cout << dt << std::endl;
        std::cout << "Восход Луны: " << rise << std::endl;
        std::cout << "Кульминация Луны: " << culm_time << " (El: " << max_el << ")" << std::endl;
        std::cout << "Заход Луны: " << set << std::endl;
    }
};

int main() {
    using namespace std;
    Moon m;
    m.calculate_events();
}