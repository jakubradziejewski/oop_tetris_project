#pragma once
#include "grid.h"
#include <vector>
#include "block.h"
#include <memory>
#include "score.h"
class BlockBase;
class LBlock;
class JBlock;
class IBlock;
class OBlock;
class SBlock;
class TBlock;
class ZBlock;
class Game {
public:
    Game();

    void Draw();
    void HandleInput();
    void MoveBlockDown();

    bool gameOver;
    ScoreHandler scoreHandler;
protected:
    Grid grid;                 // Composition: The grid owned by the game
private:
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();

    std::unique_ptr<BlockBase> GetRandomBlock();
    static std::vector<std::unique_ptr<BlockBase>> GetAllBlocks();

    std::vector<std::unique_ptr<BlockBase>> blocks;
    std::unique_ptr<BlockBase> currentBlock;
    std::unique_ptr<BlockBase> nextBlock;
};
