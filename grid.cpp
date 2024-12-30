#include "grid.h"
#include <iostream>
#include "raylib.h"
#include "block_types.h"

Grid::Grid() : numRows(20), numCols(10), cellSize(30) {
    MakeGrid();
    colors = GetCellColor();
}

void Grid::MakeGrid() {
    gridPositions.resize(numRows, std::vector<Position>(numCols, Position(0, 0, BlockType::None)));
    for (int row = 0; row < numRows; ++row) {
        for (int column = 0; column < numCols; ++column) {
            gridPositions[row][column] = Position(row, column, BlockType::None);
        }
    }
}

void Grid::PrintGrid() {
    for (const auto &row: gridPositions) {
        for (const auto &pos: row) {
            std::cout << static_cast<int>(pos.state) << " ";
        }
        std::cout << std::endl;
    }
}

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


bool Grid::IsCellOutside(int row, int column) const {
    return row < 0 || row >= numRows || column < 0 || column >= numCols;
}

bool Grid::IsCellEmpty(int row, int column) {
    if (IsCellOutside(row, column)) return false;
    return gridPositions[row][column].state == BlockType::None;
}

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

bool Grid::IsRowFull(int row) {
    for (const auto &pos: gridPositions[row]) {
        if (pos.state == BlockType::None) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (auto &pos: gridPositions[row]) {
        pos.state = BlockType::None;
    }
}

void Grid::MoveRowDown(int row, int numRowsDown) {
    for (int column = 0; column < numCols; ++column) {
        int targetRow = row + numRowsDown;
        if (targetRow < numRows) {
            gridPositions[targetRow][column].state = gridPositions[row][column].state;
        }
        gridPositions[row][column].state = BlockType::None;
    }
}
