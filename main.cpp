#include <raylib.h>
#include "game.h"
#include "draw.h"

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
        Interface(font, game, deepNight, skyDusk);
        game.Draw();
        if (game.gameOver) {
            GameOver(font);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
