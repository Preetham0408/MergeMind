#include <iostream>
#include <random>
#include <iomanip>
#include "header/GameBoard.h"

using namespace std;

namespace {
    mt19937 rng(random_device{}());
}

GameBoard::GameBoard() {
    reset();
}

void GameBoard::reset() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = 0;
        }
    }

    addRandomTile();
    addRandomTile();
}

void GameBoard::addRandomTile() {
    int emptyRows[SIZE * SIZE];
    int emptyCols[SIZE * SIZE];
    int emptyCount = 0;

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                emptyRows[emptyCount] = row;
                emptyCols[emptyCount] = col;
                emptyCount++;
            }
        }
    }

    if (emptyCount == 0) {
        return;
    }

    uniform_int_distribution<int> position(0, emptyCount - 1);
    uniform_int_distribution<int> tileChance(1, 10);

    int selected = position(rng);
    int row = emptyRows[selected];
    int col = emptyCols[selected];

    board[row][col] = (tileChance(rng) == 1) ? 4 : 2;
}

bool GameBoard::moveLine(int index, bool isRow,
                         bool towardStart, int& points) {
    int original[SIZE];
    int tiles[SIZE];
    int merged[SIZE];

    int count = 0;
    int outputCount = 0;
    points = 0;

    for (int i = 0; i < SIZE; i++) {
        int position = towardStart ? i : SIZE - 1 - i;

        int value = isRow
            ? board[index][position]
            : board[position][index];

        original[i] = value;

        if (value != 0) {
            tiles[count++] = value;
        }
    }

    for (int i = 0; i < count; i++) {
        if (i + 1 < count && tiles[i] == tiles[i + 1]) {
            merged[outputCount] = tiles[i] * 2;
            points += merged[outputCount];
            outputCount++;
            i++;
        } else {
            merged[outputCount++] = tiles[i];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        int position = towardStart ? i : SIZE - 1 - i;

        if (isRow) {
            board[index][position] = 0;
        } else {
            board[position][index] = 0;
        }
    }

    for (int i = 0; i < outputCount; i++) {
        int position = towardStart ? i : SIZE - 1 - i;

        if (isRow) {
            board[index][position] = merged[i];
        } else {
            board[position][index] = merged[i];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        int position = towardStart ? i : SIZE - 1 - i;

        int value = isRow
            ? board[index][position]
            : board[position][index];

        if (value != original[i]) {
            return true;
        }
    }

    return false;
}

MoveResult GameBoard::moveLeft() {
    MoveResult result = {false, 0};

    for (int row = 0; row < SIZE; row++) {
        int points = 0;

        if (moveLine(row, true, true, points)) {
            result.changed = true;
        }

        result.points += points;
    }

    if (result.changed) {
        addRandomTile();
    }

    return result;
}

MoveResult GameBoard::moveRight() {
    MoveResult result = {false, 0};

    for (int row = 0; row < SIZE; row++) {
        int points = 0;

        if (moveLine(row, true, false, points)) {
            result.changed = true;
        }

        result.points += points;
    }

    if (result.changed) {
        addRandomTile();
    }

    return result;
}

MoveResult GameBoard::moveUp() {
    MoveResult result = {false, 0};

    for (int col = 0; col < SIZE; col++) {
        int points = 0;

        if (moveLine(col, false, true, points)) {
            result.changed = true;
        }

        result.points += points;
    }

    if (result.changed) {
        addRandomTile();
    }

    return result;
}

MoveResult GameBoard::moveDown() {
    MoveResult result = {false, 0};

    for (int col = 0; col < SIZE; col++) {
        int points = 0;

        if (moveLine(col, false, false, points)) {
            result.changed = true;
        }

        result.points += points;
    }

    if (result.changed) {
        addRandomTile();
    }

    return result;
}

bool GameBoard::hasWon() const {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] >= 2048) {
                return true;
            }
        }
    }

    return false;
}

bool GameBoard::isGameOver() const {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                return false;
            }
        }
    }

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE - 1; col++) {
            if (board[row][col] == board[row][col + 1]) {
                return false;
            }
        }
    }

    for (int row = 0; row < SIZE - 1; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == board[row + 1][col]) {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const GameBoard& gameBoard) {
    const int cellWidth = 6;

    out << '\n';

    for (int row = 0; row < GameBoard::SIZE; row++) {
        out << "+------+------+------+------+\n";

        for (int col = 0; col < GameBoard::SIZE; col++) {
            out << "|";

            if (gameBoard.board[row][col] == 0) {
                out << std::setw(cellWidth) << "";
            } else {
                out << std::setw(cellWidth)
                    << gameBoard.board[row][col];
            }
        }

        out << "|\n";
    }

    out << "+------+------+------+------+\n";

    return out;
}


void GameBoard::copyBoard(int destination[4][4]) const {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            destination[row][col] = board[row][col];
        }
    }
}

bool GameBoard::loadBoard(const int source[4][4]) {
    // Validate the entire board before changing anything.
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int value = source[row][col];

            if (value < 0) {
                return false;
            }

            if (value != 0 && (value < 2 || (value & (value - 1)) != 0)) {
                return false;
            }
        }
    }

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = source[row][col];
        }
    }

    return true;
}
