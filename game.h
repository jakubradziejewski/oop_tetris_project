#pragma once

#include "grid.h"
#include <vector>
#include "block.h"
#include <memory>
#include "score.h"
#include "blocks_factory.h"
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
    Grid grid;                 
private:
    void MoveBlockLeft();

    void MoveBlockRight();

    bool IsBlockOutside();

    void RotateBlock();

    void LockBlock();

    bool BlockFits();

    void Reset();

    std::unique_ptr<BlockBase> GetRandomBlock();


    std::vector<std::unique_ptr<BlockBase>> blocks;
    std::unique_ptr<BlockBase> currentBlock;
    std::unique_ptr<BlockBase> nextBlock;
    std::unique_ptr<BlockFactory> blockFactory;
};
