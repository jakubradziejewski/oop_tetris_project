#include <raylib.h>
#include <math.h>
#include "game.h"
#include "draw.h"

double lastUpdateTime = 0;

bool RowFull(double interval) {
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
        if (RowFull(0.3 - pow(game.scoreHandler.getLevel(), 1/2) * 0.005)) { //this line "decides" how fast will the blocks go down 
            game.MoveBlockDown();
        }

        BeginDrawing();
        Interface(font, game, deepNight, skyDusk);
        game.Draw();
        if (game.gameOver) {
            EndDrawing();
            GameOver(font, game);
             while (true) {
                EndDrawing();
                if (GetKeyPressed() != 0) { 
                    game.HandleInput(); //this will call reset function, which is private
                    break;
                }
                GameOver(font, game);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
