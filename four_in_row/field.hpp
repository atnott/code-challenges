#pragma once

enum Cell {
    EMPTY,
    RED,
    YELLOW
};

class Field {
private:
    static const int FIELD_WIDTH = 7;
    static const int FIELD_HEIGHT = 6;

    Cell cells[FIELD_WIDTH][FIELD_HEIGHT]; // Двумерный массив для хранения игрового поля
    bool isRedTurn; // Очередь хода
    Cell winner; // Кто на данный момент выиграл

    const int DIR_NUMBER = 4;
    const int di[4]{ 1, 0, 1, 1 };
    const int dj[4]{ 0, 1, -1, 1 };
    const int WIN_LENGTH = 4;

    void checkWinner();
public:

    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const; // Получение состояния конкретной ячейки
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;
};