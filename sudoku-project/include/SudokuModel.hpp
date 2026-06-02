#pragma once
#include<array>

using std::array;

/**
 * @brief Структура, представляющвя отдельную ячейку игрового поля Судоку
 */
struct Cell
{
    int value = 0; ///< Значение в ячейке (от 1 до 9, или 0, еслм ячейка пуста)
    bool isPreset = false; ///< Флаг: true, если цифра задана изначально генератором
};

/**
 * @brief Класс модели для игры в Судоку
 * @details Хранит состояние игрового поля и выполняет все основную логику игры:
 * валидацию ходов, алгоритм авторешения и генерацию игрового поля
 */
class SudokuModel
{
public:
    static const int BOARD_SIZE = 9;
private:
    array<array<Cell, SudokuModel::BOARD_SIZE>, SudokuModel::BOARD_SIZE> board; ///< Поле для игры, массив 9 на 9

    /**
     * @brief Рекурсивный подсчет количества решений для текущего состояния игры
     * @param solutionsCount - ссылка на счетчик найденных решений
     * @return Текущее количество найденных решений
     * @note Используется генератором для гарантии единственного решения
     */
    int countSolutions(int& solutionsCount);
public:

    /**
     * @brief Конструктор по умолчанию, инициализирует пустое поле
     */
    SudokuModel();

    /**
     * @brief Установка значения в ячейку пользователем
     * @param[in] row индекс строки (0-8)
     * @param[in] column индекс столбца (0-8)
     * @param[in] value устанавливаемое значение (1-9 или 0 для очистки)
     * @return true, если значение успешно установлено, иначе false
     */
    bool setCell(int row, int column, int value);

    /**
     * @brief Проверка хода на базовые правила судоку
     * @param[in] row индекс строки (0-8)
     * @param[in] column индекс столбца (0-8)
     * @param[in] value проверяемое число
     * @return true, если число не дублируется в строке, столбце и малом квадрате 3х3
     */
    bool isValidMove(int row, int column, int value) const;

    /**
     * @brief Проверка поля на состояние победы
     * @return true, если всё поле заполнено корректно без нарушений правил
     */
    bool checkWin() const;

    /**
     * @brief Поиск единственного решения
     * @return true, если решение найдено, false, если поле не имеет решений
     */
    bool solve();

    /**
     * @brief Проверка валидности индекса для матрицы
     * @return true, если индекс находится в диапазоне от 0 до 8
     */
    bool isCorrectIndex(int row, int column) const;

    /**
     * @brief Проверка валидности значения для матрицы
     * @return true, если значение от 1 до 9
     */
    bool isCorrectValue(int value) const;

    /**
     * @brief Геттер для получения значения ячейки
     * @return Значение ячейки (0-9), если индексы некорректны, возвращает 0
     */
    int getValue(int row, int column) const;

    /**
     * @brief Проверка, является ли ячейка стартовой подсказкой
     * @return true, если ячейка зафиксирована генератором
     */
    bool isCellPreset(int row, int column) const;

    /**
     * @brief Генерация новой головоломки Судоку
     * @param[in] difficulty количество удаляемых из заполненного поля цифр
     */
    void generatePuzzle(int difficulty);

    /**
     * @brief Сброс игрового поля - очистка всех значений и флагов
     */
    void clearBoard();

    void setInitialCell(int row, int column, int value);
};