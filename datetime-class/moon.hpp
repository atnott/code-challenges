#pragma once
#include <iosfwd>
#include <iostream>
#include <ostream>
#include<sstream>
#include<fstream>
#include <string>
#include"datetime.hpp"

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

    std::string get_name_file_by_year();

    void calculate_events();

    void print_results(std::string rise, std::string set, std::string culm_time, double max_el);
};
