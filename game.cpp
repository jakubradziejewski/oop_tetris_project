#include "game.h"
#include "block.h"
#include <memory>
#include <chrono>
#include "position.h"
#include "grid.h"
#include "score.h"
#include "block_types.h"
#include <random>
#include <algorithm>

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, blocks.size() - 1);

    int randomIndex = dist(gen);
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
    static auto lastMoveTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();

    if (gameOver) {
        gameOver = false;
        Reset();
    }

    int delay = 150;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) delay = 75;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count() > delay) {
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            MoveBlockLeft();
            lastMoveTime = currentTime;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            MoveBlockRight();
            lastMoveTime = currentTime;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            MoveBlockDown();
            lastMoveTime = currentTime;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            RotateBlock();
            lastMoveTime = currentTime;
        }
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
    return std::any_of(tiles.begin(), tiles.end(), [this](const Position &item) {
        return grid.IsCellOutside(item.row, item.column);
    });
}


void Game::RotateBlock() {
    if (!gameOver) {
        currentBlock->Rotate();
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock->UnRotate();
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
    return std::all_of(tiles.begin(), tiles.end(), [this](const Position &item) {
        return grid.IsCellEmpty(item.row, item.column);
    });
}


void Game::Reset() {
    grid.MakeGrid();
    blocks = blockFactory->createAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    scoreHandler.resetScore();
}