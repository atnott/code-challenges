#include<iostream>
#include"moon.hpp"
#include<fstream>
#include <iomanip>
#include <filesystem>
#include<string>
#include<sstream>
#include <chrono>

namespace fs = std::filesystem;

int main() {
    using namespace std;
    Moon m;

    auto start = chrono::high_resolution_clock::now();

    m.calculate_events();

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> duration = end - start;
    cout << "lead time: " << duration.count() / 1000 << endl;
}