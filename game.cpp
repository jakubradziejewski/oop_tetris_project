#include "game.h"
#include "block.h"
#include <memory>
#include "position.h"
#include "grid.h"
#include "score.h"
#include "block_types.h"

Game::Game() : blockFactory(std::make_unique<TetrisBlockFactory>()) {
    grid = Grid();
    blocks = blockFactory->createAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    scoreHandler = ScoreHandler("highscores.txt");
}

std::unique_ptr<BlockBase> Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = blockFactory->createAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    std::unique_ptr<BlockBase> block = std::move(blocks[randomIndex]);
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}



void Game::Draw() {
    grid.Draw();
    currentBlock->Draw(11, 11);
    switch (nextBlock->id) {
        case BlockType::IBlock:
            nextBlock->Draw(255, 370);
            break;
        case BlockType::OBlock:
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
        currentBlock->id = BlockType::GameOver;
        currentBlock->Draw(11, 11);
        scoreHandler.updateHighScores(scoreHandler.currentScore, scoreHandler.currentLevel);
        scoreHandler.updateScore(0, -5);
    }

    scoreHandler.updateScore(0, 5);
    int rowsCleared = grid.ClearFullRows();
    scoreHandler.updateScore(rowsCleared, 0);
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
    blocks = blockFactory->createAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    scoreHandler.resetScore();
}
