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
    int countSolutions(int& solutionsCount);
public:
    SudokuModel();
    bool setCell(int row, int column, int value);
    bool isValidMove(int row, int column, int value) const;
    bool checkWin() const;
    bool solve();
    bool isCorrectIndex(int row, int column) const;
    bool isCorrectValue(int value) const;

    int getValue(int row, int column) const;
    bool isCellPreset(int row, int column) const;
    void generatePuzzle(int difficulty);
    void clearBoard();
};