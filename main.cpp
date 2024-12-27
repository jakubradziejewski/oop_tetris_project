#include <cstdio>
#include <raylib.h>
#include "game.h"


double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    // 800x450 is 16:9
    InitWindow(500, 620, "Ray lib Tetris");
    SetTargetFPS(60);
    Game game = Game();
    Font font = LoadFontEx("Font/monogram.ttf", 64, nullptr, 0);

    while (!WindowShouldClose()) {
        game.HandleInput();
        if (EventTriggered(0.3 - game.scoreHandler.currentLevel * 0.015)) {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(deepNight);
        DrawTextEx(font, "Score", {360, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Level", {360, 130}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {340, 250}, 38, 2, WHITE);

        if (game.gameOver) {
            DrawTextEx(font, "GAME OVER", {320, 520}, 30, 2, WHITE);
        }

        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, skyDusk);
        char scoreText[10];
        sprintf(scoreText, "%d", game.scoreHandler.getScore());
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

        DrawRectangleRounded({320, 170, 170, 60}, 0.3, 6, skyDusk);
        char levelText[10];
        sprintf(levelText, "%d", game.scoreHandler.getLevel());
        Vector2 levelSize = MeasureTextEx(font, levelText, 38, 2);
        DrawTextEx(font, levelText, {320 + (170 - levelSize.x) / 2, 185}, 38, 2, WHITE);

        DrawRectangleRounded({320, 300, 170, 180}, 0.3, 6, skyDusk);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}