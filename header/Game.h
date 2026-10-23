
#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"
#include "ScoreManager.h"
#include "SaveManager.h"

class Game {
private:
    GameBoard gameBoard;
    ScoreManager scoreManager;
    SaveManager saveManager;
    bool wonMessageShown;

    void displayMenu() const;
    bool handleInput(char choice);
    void startNewGame();

public:
    Game();
    void run();
};

#endif
