#include "game.h"
#include "block.h"
#include "blocks.cpp"
#include <memory>
#include <random>
#include "position.h"
#include "grid.h"

Game::Game() {
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    level = 1;
}

std::unique_ptr<BlockBase> Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    std::unique_ptr<BlockBase> block = std::move(blocks[randomIndex]);
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<std::unique_ptr<BlockBase>> Game::GetAllBlocks() {
    std::vector<std::unique_ptr<BlockBase>> newBlocks;
    newBlocks.push_back(std::make_unique<IBlock>());
    newBlocks.push_back(std::make_unique<JBlock>());
    newBlocks.push_back(std::make_unique<LBlock>());
    newBlocks.push_back(std::make_unique<OBlock>());
    newBlocks.push_back(std::make_unique<SBlock>());
    newBlocks.push_back(std::make_unique<TBlock>());
    newBlocks.push_back(std::make_unique<ZBlock>());
    return newBlocks;
}

void Game::Draw() {
    grid.Draw();
    currentBlock->Draw(11, 11);
    switch (nextBlock->id) {
        case 3:
            nextBlock->Draw(255, 370);
            break;
        case 4:
            nextBlock->Draw(255, 360);
            break;
        default:
            nextBlock->Draw(270, 350);
            break;
    }
}

void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0) {
        gameOver = false;
        Reset();
    }
    switch (keyPressed) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            break;
        case KEY_UP:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockLeft() {
    if (!gameOver) {
        currentBlock->Move(0, -1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock->Move(0, 1);
        }
    }
}

void Game::MoveBlockRight() {
    if (!gameOver) {
        currentBlock->Move(0, 1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock->Move(0, -1);
        }
    }
}

void Game::MoveBlockDown() {
    if (!gameOver) {
        currentBlock->Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock->Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock->GetCellPosition();
    for (Position item: tiles) {
        if (grid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() {
    if (!gameOver) {
        currentBlock->Rotate();
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock->UndoRotation();
        }
    }
}

void Game::LockBlock() {
    std::vector<Position> tiles = currentBlock->GetCellPosition();
    for (const Position &item: tiles) {
        if (!grid.IsCellOutside(item.row, item.column)) {
            grid.gridPositions[item.row][item.column].state = currentBlock->id;
        }
    }

    currentBlock = std::move(nextBlock);
    nextBlock = GetRandomBlock();

    if (!BlockFits()) {
        gameOver = true;
        currentBlock->id = 10;
        currentBlock->Draw(11, 11);
    }

    UpdateScore(0, 5);
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock->GetCellPosition();
    for (Position item: tiles) {
        if (!grid.IsCellEmpty(item.row, item.column)) {
            return false;
        }
    }
    return true;
}

void Game::Reset() {
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    level = 1;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
    if (linesCleared > 0) {
        score += 10 * (linesCleared + 1) * (linesCleared + 1) * level;
    }
    level = score / 200 + 1;
    score += moveDownPoints;
}