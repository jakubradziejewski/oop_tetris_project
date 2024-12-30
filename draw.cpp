#include "draw.h"
#include <cstdio>
#include "game.h"


// function for drawing main interface using raylib
void Interface(Font font, const Game& game, Color deepNight, Color skyDusk) {
    ClearBackground(deepNight);
    DrawTextEx(font, "Score", {360, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Level", {360, 130}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {340, 250}, 38, 2, WHITE);

    // managing score box
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, skyDusk);
    char scoreText[10];
    sprintf(scoreText, "%d", game.scoreHandler.getScore());
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

    // managing level box
    DrawRectangleRounded({320, 170, 170, 60}, 0.3, 6, skyDusk);
    char levelText[10];
    sprintf(levelText, "%d", game.scoreHandler.getLevel());
    Vector2 levelSize = MeasureTextEx(font, levelText, 38, 2);
    DrawTextEx(font, levelText, {320 + (170 - levelSize.x) / 2, 185}, 38, 2, WHITE);

    // managing next block box
    DrawRectangleRounded({320, 300, 170, 180}, 0.3, 6, skyDusk);
}

void GameOver(Font font, const Game& game) {
    BeginDrawing();
    ClearBackground(deepNight);
    DrawTextEx(font, "GAME OVER", {320, 500}, 30, 2, WHITE);
    DrawTextEx(font, "HIGH SCORE", {320, 535}, 30, 2, WHITE);
    char levelText[10];
    sprintf(levelText, "%d", game.scoreHandler.getHighScores()[0].score);
    DrawTextEx(font, levelText, {320, 570}, 30, 2, WHITE);
}
