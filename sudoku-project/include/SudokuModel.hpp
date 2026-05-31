#pragma once
#include<array>

using std::array;

struct Cell
{
    int value = 0;
    bool isPreset = false;
};

class SudokuModel
{
    array<array<Cell, 9>, 9> board;
public:
    bool setCell(int row, int column, int value);
    bool isValidMove(int row, int column, int value) const;
    bool checkWin() const;
    bool solve();

    int getValue(int row, int column) const;
    bool isCellPresent(int row, int column) const;
};