#pragma once

#include <string>
#include <vector>

struct ScoreEntry {
    int score;
    int level;

    bool operator<(const ScoreEntry &other) const {
        return score < other.score;
    }

    bool operator>(const ScoreEntry &other) const {
        return score > other.score;
    }
};

class ScoreHandler {
public:
    explicit ScoreHandler(std::string filename = "highscores.txt");

    void updateHighScores(int score, int level);

    std::vector<ScoreEntry> getHighScores() const { return highScores; }

    void updateScore(int linesCleared, int moveDownPoints);

    void resetScore();

    int getScore() const { return currentScore; }

    int getLevel() const { return currentLevel; }

    int currentScore = 0;
    int currentLevel = 1;

private:
    static const int MAX_SCORES = 5;
    std::string filename;
    std::vector<ScoreEntry> highScores;

    void loadScores();

    void saveScores();
};