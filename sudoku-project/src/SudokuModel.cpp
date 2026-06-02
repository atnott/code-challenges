#include"../include/SudokuModel.hpp"
#include<vector>
#include<algorithm>
#include<random>

SudokuModel::SudokuModel()
{
    clearBoard();
}

/**
 * @details Безопасная проверка границ массива, защищает от Segmentation Fault
 */
bool SudokuModel::isCorrectIndex(int row, int column) const
{
    if (row >= 0 && row < SudokuModel::BOARD_SIZE && column >= 0 && column < SudokuModel::BOARD_SIZE)
        return true;
    return false;
}

bool SudokuModel::isCorrectValue(int value) const
{
    return value > 0 && value < SudokuModel::BOARD_SIZE + 1;
}

/**
 * @details Реализует инкапсуляцию данных. Внешний код не имеет прямого
 * доступа к матрице `board`, работа с ней идет только через этот безопасный метод
 */
int SudokuModel::getValue(int row, int column) const
{
    if (isCorrectIndex(row, column))
        return board[row][column].value;
    return 0;
}

bool SudokuModel::isCellPreset(int row, int column) const
{
    if (isCorrectIndex(row, column))
        return board[row][column].isPreset;
    return false;
}

bool SudokuModel::setCell(int row, int column, int value)
{
    if (isCorrectIndex(row, column))
    {
        if (!board[row][column].isPreset) // Защита начальных подсказок
        {
            if (isCorrectValue(value) || value == 0)
            {
                board[row][column].value = value;
                return true;
            }
        }
    }
    return false; // Отказ в совершении хода
}

bool SudokuModel::isValidMove(int row, int column, int value) const
{
    if (isCorrectIndex(row, column) && isCorrectValue(value))
    {
        for (int i = 0; i < SudokuModel::BOARD_SIZE; i++)
        {
            if (i != column && board[row][i].value == value) return false;
            if (i != row && board[i][column].value == value) return false;
        }

        int step = sqrt(SudokuModel::BOARD_SIZE); // шаг для нашей матрицы
        int startRow = (row / step) * step;
        int startColumn = (column / step) * step;

        for (int i = startRow; i < startRow + step; i++)
        {
            for (int j = startColumn; j < startColumn + step; j++)
            {
                if (i == row && j == column) continue;
                if (board[i][j].value == value)
                    return false;
            }
        }
    }
    return true; // Ошибок не найдено, ход допустим
}

bool SudokuModel::checkWin() const
{
    for (int i = 0; i < SudokuModel::BOARD_SIZE; i++)
    {
        for (int j = 0; j < SudokuModel::BOARD_SIZE; j++)
        {
            // Если осталась пустая ячейка или нарушено правило — победа не засчитывается
            if (board[i][j].value == 0) return false;
            if (!isValidMove(i, j, board[i][j].value)) return false;
        }
    }
    return true;
}

bool SudokuModel::solve() {
    for (int i = 0; i < SudokuModel::BOARD_SIZE; i++)
    {
        for (int j = 0; j < SudokuModel::BOARD_SIZE; j++)
        {
            if (board[i][j].value == 0)
            {
                for (int num = 1; num < SudokuModel::BOARD_SIZE + 1; num++)
                {
                    if (isValidMove(i, j, num)) // если ход валидный, временно присваиваем ячейке значение num
                    {
                        board[i][j].value = num;
                        if (solve()) return true;
                        else board[i][j].value = 0;
                    }
                }
                return false; // Нет подходящих чисел — тупик
            }
        }
    }
    return true; // Вся матрица успешно заполнена
}

int SudokuModel::countSolutions(int& solutionsCount)
{
    if (solutionsCount > 1) return solutionsCount;
    for (int i = 0; i < SudokuModel::BOARD_SIZE; i++)
    {
        for (int j = 0; j < SudokuModel::BOARD_SIZE; j++)
        {
            if (board[i][j].value == 0)
            {
                for (int num = 1; num < SudokuModel::BOARD_SIZE + 1; num++)
                {
                    if (isValidMove(i, j, num))
                    {
                        board[i][j].value = num;
                        countSolutions(solutionsCount);
                        board[i][j].value = 0;
                    }
                }
                return solutionsCount;
            }
        }
    }
    solutionsCount++;
    return solutionsCount;
}

void SudokuModel::clearBoard()
{
    for (int i = 0; i < SudokuModel::BOARD_SIZE; i++)
    {
        for (int j = 0; j < SudokuModel::BOARD_SIZE; j++)
        {
            board[i][j].value = 0;
            board[i][j].isPreset = false;
        }
    }
}

void SudokuModel::generatePuzzle(int difficulty)
{
    clearBoard();

    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<int> dist(0, 8);

    std::vector<int> nums;
    for (int i = 1; i < SudokuModel::BOARD_SIZE + 1; i++) nums.push_back(i);
    int indexes[3] = {0, 3, 6};

    // Фаза 1: Случайное заполнение трех диагональных квадратов 3х3
    for (int index : indexes)
    {
        std::shuffle(nums.begin(), nums.end(), g);

        int count = 0;
        for (int i = index; i < index + sqrt(SudokuModel::BOARD_SIZE); i++)
        {
            for (int j = index; j < index + sqrt(SudokuModel::BOARD_SIZE); j++)
            {
                board[i][j].value = nums[count++];
            }
        }
    }

    // Фаза 2: Получение полностью заполненного валидного поля
    solve();

    // Фаза 3: Удаление случайных ячеек с проверкой на единственность решения
    int cnt = 0;
    int attempts = 0;

    while (cnt != difficulty && attempts < 1000)
    {
        attempts++;
        int row, column;
        do
        {
            row = dist(g);
            column = dist(g);
        } while (board[row][column].value == 0);

        int backup = board[row][column].value;
        board[row][column].value = 0;

        int score = 0;
        countSolutions(score);

        if (score != 1) // Решений стало 0 или больше 1
        {
            board[row][column].value = backup; // Возвращаем назад, если решение перестало быть единственным
        }
        else cnt++; // Успешно удалили ячейку
    }

    // Фиксация оставшихся подсказок
    for (int i = 0; i < SudokuModel::BOARD_SIZE; i++)
    {
        for (int j = 0; j < SudokuModel::BOARD_SIZE; j++)
        {
            if (board[i][j].value != 0) board[i][j].isPreset = true;
        }
    }
}

void SudokuModel::setInitialCell(int row, int column, int value)
{
    // 1. Проверяем, что индексы не выходят за пределы поля (0-8)
    // 2. Проверяем, что значение валидно (1-9) или это пустая клетка (0)
    if (isCorrectIndex(row, column) && (isCorrectValue(value) || value == 0))
    {
        board[row][column].value = value;

        // Переводим в булево значение: если value != 0, то true, иначе false
        board[row][column].isPreset = (value != 0);
    }
}