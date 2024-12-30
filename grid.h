#pragma once

#include <vector>
#include "position.h"
#include "colors.h"
#include "block_types.h"

class Grid {
public:
    Grid();

    void MakeGrid();

    void PrintGrid();

    bool IsCellOutside(int row, int column) const;

    bool IsCellEmpty(int row, int column);

    void Draw();

    int ClearFullRows();

    // Composition: Grid owns all Positions
    std::vector<std::vector<Position>> gridPositions;

private:
    bool IsRowFull(int row);

    void ClearRow(int row);

    void MoveRowDown(int row, int numRows);

    //void DrawGridLines();

    int numRows;                                 // Number of rows in the grid
    int numCols;                                 // Number of columns in the grid
    int cellSize;                                // Size of each cell for rendering

    std::vector<Color> colors;                  // Colors for visualization
};
