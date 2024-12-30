#include "score.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>

ScoreHandler::ScoreHandler(std::string fname) : filename(std::move(fname)) {
    loadScores();
}

void ScoreHandler::loadScores() {
    try {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "No existing high scores file. Creating new one." << std::endl;
            return;
        }

        ScoreEntry entry;
        while (file >> entry.score >> entry.level && highScores.size() < MAX_SCORES) {
            highScores.push_back(entry);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error loading scores: " << e.what() << std::endl;
    }
}

void ScoreHandler::saveScores() {
    try {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open file for writing: " + filename);
        }

        for (const auto &entry: highScores) {
            file << entry.score << " " << entry.level << "\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error saving scores: " << e.what() << std::endl;
    }
}

void ScoreHandler::updateHighScores(int score, int level) {
    ScoreEntry newEntry{score, level};

    if (highScores.size() < MAX_SCORES) {
        highScores.push_back(newEntry);
    } else if (newEntry > highScores.back()) {
        highScores.back() = newEntry;
    } else {
        return;
    }

    std::sort(highScores.begin(), highScores.end(), std::greater<>());
    saveScores();
}

void ScoreHandler::updateScore(int linesCleared, int moveDownPoints) {
    const int baseScores[4] = {40, 100, 300, 1200};

    if (linesCleared > 0) {
        int baseScore = baseScores[linesCleared - 1];
        int levelMultiplier = currentLevel + 1;
        currentScore += baseScore * levelMultiplier;
    }

    currentScore += moveDownPoints*(currentLevel*0.2+1);

    const int baseThreshold = 100;
    currentLevel = std::log2(currentScore / baseThreshold+1);
}
void ScoreHandler::resetScore() {
    currentScore = 0;
    currentLevel = 0;
}

// ScoreEntry ScoreHandler::getHighScore()
// {
//     loadScores();
//     auto entry = highScores[0];
//     std::cerr << entry.score << " " << entry.level << std::endl;
//     return entry;
// }