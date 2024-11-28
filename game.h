#pragma once
#include "grid.h"
#include <vector>
#include "block.h"

class Game {
public:
    Game();

    void Draw();
    void HandleInput();
    void MoveBlockDown();

    bool gameOver;
    int score;
    int level;
protected:
    Grid grid;                 // Composition: The grid owned by the game
private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    static std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);

    std::vector<Block> blocks; // Collection of all block types
    Block currentBlock;        // The block currently being moved
    Block nextBlock;           // The next block to spawn
};
