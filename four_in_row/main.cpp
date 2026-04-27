#include <iostream>
#include "field.hpp"

int main() {
    setlocale(LC_ALL, "Russian");
    Field field(true);
    using namespace std;

    while (!field.isOver())
    {
        field.print();
        cout << "Ходит " << (field.isRedTurnNow() ? "красный" : "желтый")
             << " игрок, введите колонку (1-" << 7 << "): ";

        int column;
        cin >> column;

        // 1. Проверка на буквы и мусор в потоке
        if (cin.fail()) {
            cin.clear(); // Сбрасываем ошибку
            cin.ignore(32767, '\n'); // Очищаем буфер до конца строки
            cout << "Ошибка! Введите целое число." << endl;
            continue;
        }


        // 2. Проверка логики хода (диапазон и заполненность колонки)
        if (!field.makeTurn(column)) {
            cout << "Неверный ход! Колонка полна или вне диапазона." << endl;
        }
    }
    field.printResult();
    return 0;
}