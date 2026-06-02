#include"../include/SudokuController.hpp"
#include<iostream>
#include<sstream>
#include <thread>
#include <chrono>
#include <fstream>

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
        cout << "Введите ваш ход вида \'A5 9\' \nДоступные команды: \'exit\' - выйти из игры / \'solve\' - показать единственное решение / \'demo\' - показать постепенное решение / \'load\' - загрузить судоку из файла" << endl;
        string input;
        std::getline(cin, input);

        if (input == "exit")
            break;
        else if (input == "solve")
        {
            // Очистка всех пользовательских ходов перед авторешением
            for (int i = 0; i < SudokuModel::BOARD_SIZE; i++) {
                for (int j = 0; j < SudokuModel::BOARD_SIZE; j++) {
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
        else if (input == "demo")
            runDemo();
        else if (input == "load")
        {
            cout << "Введите имя файла (например filename.txt)" << endl;
            string filename;
            cin >> filename;
            cin.ignore();

            if (loadAndSolveFromFile(filename))
            {
                break;
            }
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

void SudokuController::runDemo()
{
    SudokuModel demoCopy = model;
    demoCopy.solve();

    for (int row = 0; row < SudokuModel::BOARD_SIZE; row++)
    {
        for (int col = 0; col < SudokuModel::BOARD_SIZE; col++)
        {
            if (model.getValue(row, col) == 0)
            {
                int correctValue = demoCopy.getValue(row, col);
                model.setCell(row, col, correctValue);
                cout << "\033[2J\033[1;1H";
                view.printBoard(model);
                string symbols = "ABCDEFGHI";
                cout << "[DEMO] Компьютер заполнил ячейку " << symbols[col] << row + 1 << " цифрой " << correctValue << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }
    cout << "DEMO Режим закончен! Нажмите Enter для продолжения..." << endl;
    cin.ignore(10000, '\n');
    cin.get();
}

bool SudokuController::loadAndSolveFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Ошибка: Не удалось открыть файл '" << filename << "'!" << endl;
        cout << "Нажмите Enter, чтобы вернуться в игру..." << endl;
        cin.get();
        return false;
    }

    model.clearBoard();

    for (int row = 0; row < SudokuModel::BOARD_SIZE; row++)
    {
        for (int col = 0; col < SudokuModel::BOARD_SIZE; col++)
        {
            int val;
            if (!(file >> val))
            {
                cout << "Ошибка: Файл поврежден или содержит недостаточно данных!" << endl;
                cout << "Нажмите Enter, чтобы продолжить..." << endl;
                model.clearBoard();
                file.close();
                cin.get();
                return false;
            }
            model.setInitialCell(row, col, val);
        }
    }
    file.close();
    model.solve();

    cout << "\033[2J\033[1;1H";
    view.printBoard(model);
    cout << "Судоку из файла '" << filename << "' успешно загружено и РЕШЕНО!" << endl;
    cout << "Нажмите Enter для выхода..." << endl;

    cin.get();
    return true;
}