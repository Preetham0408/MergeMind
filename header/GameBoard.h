#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>

struct MoveResult {
    bool changed;
    int points;
};

class GameBoard {
private:
    static const int SIZE = 4;
    int board[SIZE][SIZE];

    void addRandomTile();
    bool moveLine(int index, bool isRow, bool towardStart, int& points);

public:
    GameBoard();
    
    MoveResult moveLeft();
    MoveResult moveRight();
    MoveResult moveUp();
    MoveResult moveDown();

    bool hasWon() const;
    bool isGameOver() const;

    void copyBoard(int destination[4][4]) const;
    bool loadBoard(const int source[4][4]);

    void reset();

    friend std::ostream& operator<<(std::ostream& out, const GameBoard& board);
};

#endif