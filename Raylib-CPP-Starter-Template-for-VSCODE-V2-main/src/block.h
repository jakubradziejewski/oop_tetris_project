#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block {
public:
    Block();

    void Draw(int offsetX, int offsetY);

    std::vector<Position> GetCellPosition();

    void Rotate();

    void Move(int rows, int columns);

    void UndoRotation();

    int id{};
    std::map<int, std::vector<Position>> cells;
    std::vector<Color> colors;
protected:
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;
};
