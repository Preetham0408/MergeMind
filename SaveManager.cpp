#include <fstream>
#include "header/SaveManager.h"

using namespace std;

bool SaveManager::save(
    const GameBoard& gameBoard,
    const ScoreManager& scoreManager,
    const string& filename
) const {
    ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    int board[4][4];
    gameBoard.copyBoard(board);

    file << "MERGEMIND_SAVE_V1\n";
    file << scoreManager.getScore() << '\n';

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            file << board[row][col] << ' ';
        }
        file << '\n';
    }

    file.close();
    return !file.fail();
}

bool SaveManager::load(
    GameBoard& gameBoard,
    ScoreManager& scoreManager,
    const string& filename
) const {
    ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    string header;
    int savedScore;
    int board[4][4];

    if (!(file >> header) || header != "MERGEMIND_SAVE_V1") {
        return false;
    }

    if (!(file >> savedScore) || savedScore < 0) {
        return false;
    }

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (!(file >> board[row][col])) {
                return false;
            }
        }
    }

    // Validate before changing the current game.
    if (!gameBoard.loadBoard(board)) {
        return false;
    }

    scoreManager.setScore(savedScore);
    return true;
}
