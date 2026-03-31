#include <iostream>
#include "datetime.hpp"

int main() {
    using namespace std;
    date_time d(2024, 1, 30);
    date_time d2(2024, 1, 1);
    cout << (d - d2) << endl; // проверка перегрузки оператора "-"

    date_time test(2023, 2, 29); // проверка функции is_valid
    cout << d << d2 << endl; // проверка перегрузи оператора вывода

    date_time test2("2020-11-02");
    cout << test2 << endl;

    return 0;
}