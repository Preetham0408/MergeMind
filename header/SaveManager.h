
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include "GameBoard.h"
#include "ScoreManager.h"

class SaveManager {
public:
    bool save(const GameBoard& gameBoard,
              const ScoreManager& scoreManager,
              const std::string& filename) const;

    bool load(GameBoard& gameBoard,
              ScoreManager& scoreManager,
              const std::string& filename) const;
};

#endif
