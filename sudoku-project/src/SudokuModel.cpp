#include"../include/SudokuModel.hpp"

SudokuModel::SudokuModel()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j].value = 0;
            board[i][j].isPreset = false;
        }
    }
}

bool SudokuModel::isCorrectIndex(int row, int column) const
{
    if (row >= 0 && row < 9 && column >= 0 && column < 9)
        return true;
    return false;
}

bool SudokuModel::isCorrectValue(int value) const
{
    return value > 0 && value < 10;
}

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
        if (!board[row][column].isPreset)
        {
            if (isCorrectValue(value) || value == 0)
            {
                board[row][column].value = value;
                return true;
            }
        }
    }
    return false;
}

bool SudokuModel::isValidMove(int row, int column, int value) const
{
    if (isCorrectIndex(row, column) && isCorrectValue(value))
    {
        for (int i = 0; i < 9; i++)
        {
            if (i != column && board[row][i].value == value) return false;
            if (i != row && board[i][column].value == value) return false;
        }

        int startRow = (row / 3) * 3;
        int startColumn = (column / 3) * 3;

        for (int i = startRow; i < startRow + 3; i++)
        {
            for (int j = startColumn; j < startColumn + 3; j++)
            {
                if (i == row && j == column) continue;
                if (board[i][j].value == value)
                    return false;
            }
        }
    }
    return true;
}

bool SudokuModel::checkWin() const
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j].value == 0) return false;
            if (!isValidMove(i, j, board[i][j].value)) return false;
        }
    }
    return true;
}

bool SudokuModel::solve() {
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j].value == 0)
            {
                for (int num = 1; num < 10; num++)
                {
                    if (isValidMove(i, j, num)) // если ход валидный, временно присваиваем ячейке значение num
                    {
                        board[i][j].value = num;
                        if (solve()) return true;
                        else board[i][j].value = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

