#include "grid.h"
#include <iostream>
#include "raylib.h"
#include "block_types.h"

// Initialize grid
Grid::Grid() : numRows(20), numCols(10), cellSize(30) {
    MakeGrid();
    colors = GetCellColor();
}

// Creates grid
void Grid::MakeGrid() {
    gridPositions.resize(numRows, std::vector<Position>(numCols, Position(0, 0, BlockType::None)));
    for (int row = 0; row < numRows; ++row) {
        for (int column = 0; column < numCols; ++column) {
            gridPositions[row][column] = Position(row, column, BlockType::None);
        }
    }
}

// Draws the grid
void Grid::Draw() {
    for (const auto &row: gridPositions) {
        for (const auto &pos: row) {
            DrawRectangle(
                    pos.column * cellSize + 11,
                    pos.row * cellSize + 11,
                    cellSize - 1,
                    cellSize - 1,
                    colors[static_cast<int>(pos.state)]
            );

        }
    }
}

// Check whether a certain cell of a block is outside the grid
bool Grid::IsCellOutside(int row, int column) const {
    return row < 0 || row >= numRows || column < 0 || column >= numCols;
}

// Check whether a certain cell of a grid is available
bool Grid::IsCellEmpty(int row, int column) {
    if (IsCellOutside(row, column)) return false;
    return gridPositions[row][column].state == BlockType::None;
}

// Clear rows that are complete
int Grid::ClearFullRows() {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; --row) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        } else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

// Check whether a row is complete
bool Grid::IsRowFull(int row) {
    for (const auto &pos: gridPositions[row]) {
        if (pos.state == BlockType::None) {
            return false;
        }
    }
    return true;
}

// Clear row (any, does not check anything)
void Grid::ClearRow(int row) {
    for (auto &pos: gridPositions[row]) {
        pos.state = BlockType::None;
    }
}

// Move rows that are above completed rows down after we erase them
void Grid::MoveRowDown(int row, int numRowsDown) {
    for (int column = 0; column < numCols; ++column) {
        int targetRow = row + numRowsDown;
        if (targetRow < numRows) {
            gridPositions[targetRow][column].state = gridPositions[row][column].state;
        }
        gridPositions[row][column].state = BlockType::None;
    }
}