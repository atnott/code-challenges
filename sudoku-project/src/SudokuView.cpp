#include"../include/SudokuView.hpp"
#include"../include/SudokuModel.hpp"
#include<iostream>

using std::cout;
using std::endl;

void SudokuView::printBoard(const SudokuModel& model) const
{
    cout << "    A B C   D E F   G H I" << endl;
    cout << "  +-------+-------+-------+" << endl;

    for (int row = 0; row < 9; row++)
    {
        cout << row + 1 << " | ";
        for (int col = 0; col < 9; col++)
        {
            int val = model.getValue(row, col);
            if (val == 0) cout << ". ";
            else cout << val << " ";

            if ((col + 1) % 3 == 0) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((row + 1) % 3 == 0)
        {
            cout << "  +-------+-------+-------+" << endl;
        }
    }
}


