#include <iostream>
#include <iomanip>
#include "header/Game.h"

using namespace std;

namespace {
    const string SAVE_FILE = "mergemind_save.txt";
}

Game::Game()
    : gameBoard(), scoreManager(), saveManager(),
      wonMessageShown(false) {
}

void Game::startNewGame() {
    gameBoard.reset();
    scoreManager.reset();
    wonMessageShown = false;

    cout << "\nNew game started!\n";
}

void Game::displayMenu() const {
    cout << "\nControls\n";
    cout << "-------------------------\n";
    cout << "W - Move Up        S - Move Down\n";
    cout << "A - Move Left      D - Move Right\n";
    cout << "P - Save Game      L - Load Game\n";
    cout << "N - New Game       Q - Quit\n";
    cout << "\n";
    cout << "Choice: ";
}

bool Game::handleInput(char choice) {
    MoveResult result = {false, 0};

    switch (choice) {
        case 'W':
        case 'w':
            result = gameBoard.moveUp();
            break;

        case 'A':
        case 'a':
            result = gameBoard.moveLeft();
            break;

        case 'S':
        case 's':
            result = gameBoard.moveDown();
            break;

        case 'D':
        case 'd':
            result = gameBoard.moveRight();
            break;

        case 'N':
        case 'n':
            startNewGame();
            return true;

        case 'P':
        case 'p':
            if (saveManager.save(
                    gameBoard, scoreManager, SAVE_FILE)) {
                cout << "Game saved successfully.\n";
            } else {
                cout << "Could not save the game.\n";
            }
            return true;

        case 'L':
        case 'l':
            if (saveManager.load(
                    gameBoard, scoreManager, SAVE_FILE)) {
                wonMessageShown = false;
                cout << "Game loaded successfully.\n";
            } else {
                cout << "Could not load the save file.\n";
            }
            return true;

        case 'Q':
        case 'q':
            return false;

        default:
            cout << "Invalid choice.\n";
            return true;
    }

    if (result.changed) {
        scoreManager.addPoints(result.points);
    } else {
        cout << "The board did not change.\n";
    }

    return true;
}

void Game::run() {
    cout << "============================\n";
    cout << "         MERGEMIND          \n";
    cout << "     2048 Number Puzzle     \n";
    cout << "============================\n";

    while (true) {
        cout << "\n========== GAME BOARD ==========\n";
        cout << gameBoard;
        cout << "\nScore: " << scoreManager.getScore() << '\n';

        if (gameBoard.hasWon() && !wonMessageShown) {
            cout << "\nCongratulations! You reached 2048!\n";
            wonMessageShown = true;
        }

        if (gameBoard.isGameOver()) {
            cout << "\n========== GAME OVER ==========\n";
            cout << "Final score: "
                 << scoreManager.getScore() << '\n';
            cout << "N - Start a new game\n";
            cout << "Q - Quit\n";
            cout << "Choice: ";

            char choice;

            if (!(cin >> choice)) {
                break;
            }

            if (choice == 'N' || choice == 'n') {
                startNewGame();
                continue;
            }

            if (choice == 'Q' || choice == 'q') {
                break;
            }

            cout << "Please enter N or Q.\n";
            continue;
        }

        displayMenu();

        char choice;

        if (!(cin >> choice)) {
            break;
        }

        if (!handleInput(choice)) {
            break;
        }
    }

    cout << "\n============================\n";
    cout << "Final score: " << scoreManager.getScore() << '\n';
    cout << "Thanks for playing MergeMind!\n";
}
