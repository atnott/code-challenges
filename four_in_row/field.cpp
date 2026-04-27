#include "field.hpp"
#include <iostream>

void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i=0; i<FIELD_WIDTH; i++)
        for (int j=0; j<FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

bool Field::makeTurn(int column)
{
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;
    int i = column - 1;
    for (int j = 0; j < FIELD_HEIGHT; j++)
        if (cells[i][j]==EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner(); // Победа?
            isRedTurn = !isRedTurn;
            return true;
        }
    return false;
}

void Field::checkWinner()
{
    for (int i=0; i<FIELD_WIDTH; i++)
        for (int j=0; j<FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];
            if (start==EMPTY) continue;
            for (int dir=0; dir<DIR_NUMBER; dir++) {
                int length=0, iline = i, jline = j;
                while (++length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];
                    if (iline < 0 || iline >= FIELD_WIDTH || jline < 0 || jline >= FIELD_HEIGHT)
                        break;
                    if (cells[iline][jline]!=start) break;
                }
                if (length==WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
}

bool Field::isOver() const
{
    if (winner != EMPTY)
        return true;
    for (int i=0; i<FIELD_WIDTH; i++)
        for (int j=0; j<FIELD_HEIGHT; j++)
            // Если хоть одна ячейка свободна,
                // игра не окончена
                    if (cells[i][j]==EMPTY)
                        return false;
    // Все ячейки заняты
    return true;
}

bool Field::isRedTurnNow() const {
    return isRedTurn;
}

Cell Field::getCell(int i, int j) const {
    return cells[i][j];
}

void Field::print() const {
    using namespace std;
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < FIELD_WIDTH; i++) {
            if (cells[i][j] == EMPTY) cout << ". ";
            else if (cells[i][j] == RED) cout << "R ";
            else cout << "Y ";
        }
        cout << endl;
    }
    for (int i = 1; i <= FIELD_WIDTH; i++) cout << i << " ";
    cout << endl;
}

void Field::printResult() const {
    using namespace std;
    print();
    if (winner == RED) cout << "Победил Красный!" << endl;
    else if (winner == YELLOW) cout << "Победил Желтый!" << endl;
    else cout << "Ничья!" << endl;
}