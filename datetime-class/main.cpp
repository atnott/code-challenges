#include <iostream>
#include "datetime.hpp"

int main() {
    using namespace std;

    date_time test1("2024-02-28T00:00:00");
    test1.print(); // проверка корректности вывода даты и ее хранения

    date_time test2("2023-02-29T01:19:40");
    test2.print(); // проверка метода is_valid и хранения по умолчанию

    date_time test3("2024-02-29T01:19:40");
    cout << (test3 > test1) << endl; // проверка перегрузки операторов сравнения
    cout << (test3 == test1) << endl;

    date_time result1 = test3 + 365; // проверка перегрузки операторов + и -
    result1.print();

    date_time result2 = test3 - 29;
    result2.print();

    date_time result3 = test3 + 0.5; // добавление половины дня (12 часов)
    result3.print();

    date_time result4 = test3 + (1 / 24.0); // добавление одного часа
    result4.print();

    double result5 = (test3 - test1);
    cout << result5 << endl; // разница в количестве дней между двумя датами

    return 0;
}