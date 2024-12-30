#pragma once

#include <string>
#include <vector>

// struct for easier comparison of scores and storing them
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

//class used for handling scores - loading, saving, getting high scores etc
class ScoreHandler {
public:
    explicit ScoreHandler(std::string filename = "src/highscores.txt");

    void updateHighScores(int score, int level);

    inline std::vector<ScoreEntry> getHighScores() const { return highScores; }

    void updateScore(int linesCleared, int moveDownPoints);

    void resetScore();

    inline int getScore() const { return currentScore; }

    inline int getLevel() const { return currentLevel; }

    inline int getMaxScores() const {return MAX_SCORES; }

    int currentScore = 0;
    int currentLevel = 0;

private:
    static const int MAX_SCORES = 10;
    std::string filename;
    std::vector<ScoreEntry> highScores;

    void loadScores();

    void saveScores();
};