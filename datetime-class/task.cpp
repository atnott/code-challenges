#include<iostream>
#include"datetime.hpp"
#include<fstream>
#include <iomanip>
#include <filesystem>
#include<string>
#include<sstream>
#include <chrono>

namespace fs = std::filesystem;

class Moon {
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
        std::snprintf(buffer, sizeof(buffer), "Moon/Moon%04d.dat", dt.get_year());
        return buffer;
    }

    void calculate_events() {
        if (dt.get_year() < 1998 || dt.get_year() > 2023) {
            std::cerr << "WARNING: year out of range (1998-2023)" << std::endl;
            return;
        }

        std::ifstream file(get_name_file_by_year());

        if (!file.is_open()) {
            std::cout << "WARNING: file not open" << std::endl;
            return;
        }

        std::string header;
        std::getline(file, header);

        std::string rise = "not found", set = "not found", culm_time = "not found";
        double max_el = -1e9;
        double prev_el = -1e9;

        long target_date = dt.get_year() * 10000 + dt.get_month() * 100 + dt.get_day();
        bool is_new_format = header.find('T') == std::string::npos;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            long ymd;
            std::string hms;
            double col3, col4, col5, col6, col7, col8;

            ss >> ymd >> hms;

            if (ymd  > target_date) break;
            if (ymd < target_date) continue;

            while (hms.length() < 6) hms = "0" + hms;
            hms = hms.substr(0, 2) + ':' + hms.substr(2, 2) + ':' + hms.substr(4, 2);

            double el;
            if (is_new_format) {
                ss >> col3 >> el >> col5 >> col6 >> col7;
            }
            else {
                ss >> col3 >> col4 >> el >> col6 >> col7;
            }
            if (prev_el != -1e9) {
                if (prev_el > 0 && el <= 0) set = hms;
                if (prev_el < 0 && el >= 0) rise = hms;
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
        std::cout << "moonrise: " << rise << std::endl;
        std::cout << "culmination of the Moon: " << culm_time << " (El: " << max_el << ")" << std::endl;
        std::cout << "moonset: " << set << std::endl;
    }
};

int main() {
    using namespace std;
    Moon m;

    auto start = chrono::high_resolution_clock::now();

    m.calculate_events();

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> duration = end - start;
    cout << "lead time: " << duration.count() / 1000 << endl;
}