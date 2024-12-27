#include "block.h"


template<typename T>
void Block<T>::Draw(int offsetX, int offsetY) {
    std::vector<Position> tiles = GetCellPosition();
    for (Position item: tiles) {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1,
                      colors[id]);
    }
}

template<typename T>
void Block<T>::Move(int rows, int columns) {
    rowOffset += rows;
    columnOffset += columns;
}

template<typename T>
std::vector<Position> Block<T>::GetCellPosition() {
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item: tiles) {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

template<typename T>
void Block<T>::Rotate() {
    rotationState++;
    if (rotationState == (int) cells.size()) {
        rotationState = 0;
    }
}

template<typename T>
void Block<T>::UndoRotation() {
    rotationState--;
    if (rotationState == -1) {
        rotationState = cells.size() - 1;
    }
}

// Template class explicit instantiation
template
class Block<class LBlock>;

template
class Block<class JBlock>;

template
class Block<class IBlock>;

template
class Block<class OBlock>;

template
class Block<class SBlock>;

template
class Block<class TBlock>;

template
class Block<class ZBlock>;