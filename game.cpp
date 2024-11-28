#include "game.h"
#include "block.h"
#include "blocks.cpp"
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

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    // uses Block class - dependency
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

}

void Game::Draw() {
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id) {
        case 3:
            nextBlock.Draw(255, 370);
            break;
        case 4:
            nextBlock.Draw(255, 360);
            break;
        default:
            nextBlock.Draw(270, 350);
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
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight() {
    if (!gameOver) {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown() {
    if (!gameOver) {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles) {
        if (grid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() {
    if (!gameOver) {

        currentBlock.Rotate();
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.UndoRotation();
        }
    }
}

void Game::LockBlock() {
    // Get the positions of the current block's tiles
    std::vector<Position> tiles = currentBlock.GetCellPosition();

    // Lock the block's positions into the grid by setting their state
    for (const Position &item: tiles) {
        if (!grid.IsCellOutside(item.row, item.column)) { // Ensure the cell is inside the grid
            grid.gridPositions[item.row][item.column].state = currentBlock.id; // Set state to block ID
        }
    }

    // Transition to the next block
    currentBlock = nextBlock;

    // Check if the new block fits; if not, the game is over
    if (!BlockFits()) {
        gameOver = true;
        currentBlock.id = 10; // Mark current block as "frozen" (or other appropriate logic)
        currentBlock.Draw(11, 11); // Draw the block in the "frozen" state
    }

    // Update the score for placing a block
    UpdateScore(0, 5);

    // Get a new random block
    nextBlock = GetRandomBlock();

    // Clear any full rows and update the score accordingly
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock.GetCellPosition();
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