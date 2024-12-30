#include "draw.h"
#include <cstdio>
#include "game.h"

void Interface(Font font, const Game& game, Color deepNight, Color skyDusk) {
    ClearBackground(deepNight);
    DrawTextEx(font, "Score", {360, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Level", {360, 130}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {340, 250}, 38, 2, WHITE);

    // Score Box
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, skyDusk);
    char scoreText[10];
    sprintf(scoreText, "%d", game.scoreHandler.getScore());
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

    // Level Box
    DrawRectangleRounded({320, 170, 170, 60}, 0.3, 6, skyDusk);
    char levelText[10];
    sprintf(levelText, "%d", game.scoreHandler.getLevel());
    Vector2 levelSize = MeasureTextEx(font, levelText, 38, 2);
    DrawTextEx(font, levelText, {320 + (170 - levelSize.x) / 2, 185}, 38, 2, WHITE);

    // Next Block Box
    DrawRectangleRounded({320, 300, 170, 180}, 0.3, 6, skyDusk);
}

void GameOver(Font font) {
    DrawTextEx(font, "GAME OVER", {320, 520}, 30, 2, WHITE);
}
