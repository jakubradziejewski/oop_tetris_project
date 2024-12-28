#include "gtest/gtest.h"
#include "../score.h"
// Score update tests
TEST(ScoreTest, UpdateScoreMultipleLines) {
    ScoreHandler scoreHandler;
    scoreHandler.updateScore(3, 0);
    EXPECT_GT(scoreHandler.getScore(), 0);
}

// Level update tests
TEST(ScoreTest, UpdateLevel) {
    ScoreHandler scoreHandler;
    scoreHandler.updateScore(0, 1000);
    EXPECT_GT(scoreHandler.getLevel(), 0);
}

// High score tests
TEST(ScoreTest, UpdateHighScores) {
    ScoreHandler scoreHandler;
    scoreHandler.updateHighScores(1000, 1);
    auto highScores = scoreHandler.getHighScores();
    EXPECT_FALSE(highScores.empty());
    EXPECT_GE(highScores[0].score, 1000);
}