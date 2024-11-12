#pragma once
#include "grid.h"
#include <vector>
#include "blocks.cpp"
class Game{
public:
    Game();

    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();

    bool gameOver;
    int score;
    int level;
private:
    Grid grid;
    Block GetRandomBlock();
    static std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};