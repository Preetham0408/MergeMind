#include "header/ScoreManager.h"

ScoreManager::ScoreManager() : score(0) {
}

void ScoreManager::addPoints(int points) {
    if (points > 0) {
        score += points;
    }
}

int ScoreManager::getScore() const {
    return score;
}

void ScoreManager::reset() {
    score = 0;
}

bool ScoreManager::setScore(int value) {
    if (value < 0) {
        return false;
    }

    score = value;
    return true;
}