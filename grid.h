#pragma once

#include <vector>
#include "position.h"
#include "colors.h"
#include "block_types.h"

class Grid {
public:
    Grid();

    void MakeGrid();

    bool IsCellOutside(int row, int column) const;

    bool IsCellEmpty(int row, int column);

    void Draw();

    int ClearFullRows();

    std::vector<std::vector<Position>> gridPositions;

private:
    bool IsRowFull(int row);

    void ClearRow(int row);

    void MoveRowDown(int row, int numRows);

    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};