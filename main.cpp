#include <raylib.h>
#include <cmath>
#include "game.h"
#include "draw.h"

double lastUpdateTime = 0;

bool Timer(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);
    Game game = Game();
    Font font = LoadFontEx("Font/monogram.ttf", 64, nullptr, 0);

    while (!WindowShouldClose()) {
        game.HandleInput();
        if (Timer(0.3 - pow(game.scoreHandler.getLevel(), 1 / 2) *
                        0.005)) {
            game.MoveBlockDown();
        }


        BeginDrawing();
        Interface(font, game, deepNight, skyDusk);
        game.Draw();
        if (game.gameOver) {
            EndDrawing();
            GameOver(font, game);
            while (!WindowShouldClose()) {
                EndDrawing();
                if (GetKeyPressed() != 0) {
                    game.HandleInput();
                    break;
                }
                GameOver(font, game);
            }
        }

        if (WindowShouldClose()) break;
        EndDrawing();
    }

    CloseWindow();
    return 0;
}