#include "score.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <utility>

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
    if (linesCleared > 0) {
        currentScore += 10 * (linesCleared + 1) * (linesCleared + 1) * currentLevel;
    }
    currentLevel = currentScore / 200 + 1;
    currentScore += moveDownPoints;
}

void ScoreHandler::resetScore() {
    currentScore = 0;
    currentLevel = 1;
}