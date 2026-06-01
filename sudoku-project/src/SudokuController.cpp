#include"../include/SudokuController.hpp"
#include<iostream>
#include<sstream>

using std::string;
using std::cout;
using std::endl;
using std::cin;

void SudokuController::start()
{
    int difficulty = 0;
    string difficultyInput;
    cout << "Введите уровень сложности игры, где: \n1 - Easy(30 лунок) \n2 - Medium(40 лунок) \n3 - Hard(50 лунок)\n";
    cin >> difficultyInput;
    cin.ignore(); // Очистка буфера от символа '\n'

    char choice = difficultyInput[0];
    if (choice == '1') difficulty = 30;
    else if (choice == '2') difficulty = 40;
    else if (choice == '3') difficulty = 50;
    else {
        cout << "Неверный выбор! Автоматически выбран легкий уровень (30)" << endl;
        difficulty = 30;
    }

    model.generatePuzzle(difficulty);
    while (isRunning)
    {
        if (!cin) {
            cout << "Критическая ошибка ввода! Завершение игры!" << endl;
            break;
        }

        cout << "\033[2J\033[1;1H";
        view.printBoard(model);
        if (model.checkWin())
        {
            cout << "Поздравляю! Ты победил!" << endl;
            break;
        }
        cout << "Введите ваш ход вида \'A5 9\' \nДоступные команды: \'exit\' - выйти из игры / \'solve\' - показать единственное решение" << endl;
        string input;
        std::getline(cin, input);

        if (input == "exit")
            break;
        else if (input == "solve")
        {
            // Очистка всех пользовательских ходов перед авторешением
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (!model.isCellPreset(i, j)) {
                        model.setCell(i, j, 0);
                    }
                }
            }
            model.solve();
            cout << "\033[2J\033[1;1H";
            view.printBoard(model);
            cout << "Игра завершена авторешением!" << endl;
            break;
        }
        else
        {
            int row, col, value;
            parseInput(input, row, col, value);

            if (model.isCorrectIndex(row, col))
            {
                if (!model.setCell(row, col, value))
                {
                    cout << "Нельзя менять стартовые ячейки! Нажмите Enter для продолжения..." << endl;
                    cin.get();
                }
            }
            else
            {
                cout << "Неверный формат команды! Нажмите Enter для продолжения..." << endl;
                cin.get();
            }
        }
    }
}

void SudokuController::parseInput(const std::string& input, int& row, int& col, int& value)
{
    // Сразу ставим дефолтные некорректные значения на случай сбоя
    row = -1;
    col = -1;
    value = -1;

    std::stringstream ss(input);
    string rowAndCol;
    if (ss >> rowAndCol >> value)
    {
        col = std::toupper(rowAndCol[0]) - 'A';
        row = rowAndCol[1] - '1';
    }
}