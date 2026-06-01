#pragma once
#include<string>

class SudokuModel;
class SudokuView;

class SudokuController
{
    SudokuView* view;
    SudokuModel* model;
    bool isRunning;
    void parseInput(const std::string& input, int& row, int& col, int& value);
public:
    SudokuController(SudokuModel& model, SudokuView& view)
        : view(&view), model(&model), isRunning(true) {}

    void start();
};