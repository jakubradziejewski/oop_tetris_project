#include "grid.h"
#include <iostream>
#include "raylib.h"

Grid::Grid() : numRows(20), numCols(10), cellSize(30) {
    Initialize();
    colors = GetCellColor(); // Aggregated colors
}

void Grid::Initialize() {
    gridPositions.resize(numRows, std::vector<Position>(numCols, Position(0, 0, 0)));
    for (int row = 0; row < numRows; ++row) {
        for (int column = 0; column < numCols; ++column) {
            gridPositions[row][column] = Position(row, column, 0); // Initialize state to 0
        }
    }
}

void Grid::Print() {
    for (const auto& row : gridPositions) {
        for (const auto& pos : row) {
            std::cout << pos.state << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() {
    for (const auto& row : gridPositions) { // Iterating through each row
        for (const auto& pos : row) {        // Iterating through each position in the row
            // Only draw if the cell is not empty (state is non-zero)
                DrawRectangle(
                        pos.column * cellSize + 11, // X position based on column
                        pos.row * cellSize + 11,    // Y position based on row
                        cellSize - 1,               // Cell width
                        cellSize - 1,               // Cell height
                        colors[pos.state]           // Color based on state (block type)
                );

        }
    }
}


bool Grid::IsCellOutside(int row, int column) const {
    return row < 0 || row >= numRows || column < 0 || column >= numCols;
}

bool Grid::IsCellEmpty(int row, int column) {
    if (IsCellOutside(row, column)) return false; // Outside cells are not empty
    return gridPositions[row][column].state == 0;
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
    for (const auto& pos : gridPositions[row]) {
        if (pos.state == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (auto& pos : gridPositions[row]) {
        pos.state = 0; // Clear each cell in the row
    }
}

void Grid::MoveRowDown(int row, int numRowsDown) {
    for (int column = 0; column < numCols; ++column) {
        int targetRow = row + numRowsDown;
        if (targetRow < numRows) {
            gridPositions[targetRow][column].state = gridPositions[row][column].state;
        }
        gridPositions[row][column].state = 0;
    }
}
