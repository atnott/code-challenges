#pragma once

class SudokuModel;
class SudokuView;

class SudokuController
{
    SudokuView* view;
    SudokuModel* model;
    bool isRunning;
public:
    SudokuController(SudokuModel& model, SudokuView& view)
        : view(&view), model(&model), isRunning(true) {}

    void start();
};