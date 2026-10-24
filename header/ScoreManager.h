#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

class ScoreManager {
private:
    int score;

public:
    ScoreManager();
    bool setScore(int value);
    void addPoints(int points);
    int getScore() const;
    void reset();
};

#endif
