#include "draw.h"
#include <cstdio>
#include "game.h"


// function for drawing main interface using raylib
void Interface(Font font, const Game &game, Color deepNight, Color skyDusk) {
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

//function for displaying "game over" text and leaderboard
void GameOver(Font font, const Game &game) {
    BeginDrawing();
    ClearBackground(deepNight);
    DrawTextEx(font, "GAME OVER", {120, 50}, 50, 2, WHITE);
    DrawTextEx(font, "HIGH SCORES", {150, 105}, 30, 2, WHITE);
    auto HighScores = game.scoreHandler.getHighScores();
    int breakpoint = static_cast<int>(HighScores.size()) < game.scoreHandler.getMaxScores()
                     ? static_cast<int>(HighScores.size())
                     : game.scoreHandler.getMaxScores();

    // loop displaying leaderboard
    for (int i = 0; i < breakpoint; i++) {
        char levelText[100];
        sprintf(levelText, "%d.", i + 1);
        DrawTextEx(font, levelText, {50, float(110 + (i + 1) * 30)}, 25, 2, WHITE);

        sprintf(levelText, "Score: %d", HighScores[i].score);
        DrawTextEx(font, levelText, {90, float(110 + (i + 1) * 30)}, 25, 2, WHITE);

        sprintf(levelText, "Level: %d", HighScores[i].level);
        DrawTextEx(font, levelText, {350, float(110 + (i + 1) * 30)}, 25, 2, WHITE);
    }

}