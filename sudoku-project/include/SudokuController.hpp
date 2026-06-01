#pragma once
#include "SudokuModel.hpp"
#include "SudokuView.hpp"
#include <string>

class SudokuController
{
    SudokuView view;
    SudokuModel model;
    bool isRunning;
    void parseInput(const std::string& input, int& row, int& col, int& value);
public:
    SudokuController() : isRunning(true) {}

    void start();
};