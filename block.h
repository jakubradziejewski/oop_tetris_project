#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include "block_types.h"

class BlockBase {
public:
    virtual ~BlockBase() {
        // Base class cleanup logic (if needed).
        // For example: std::cerr << "BlockBase Destructor called\n";
    }

    virtual void Draw(int offsetX, int offsetY) = 0;

    virtual std::vector<Position> GetCellPosition() = 0;

    virtual void Rotate() = 0;

    virtual void Move(int rows, int columns) = 0;

    virtual void UndoRotation() = 0;

    BlockType id{BlockType::None};
};

template<typename T>
class Block : public BlockBase {
public:
    Block();

    ~Block() override; // Explicit destructor

    void Draw(int offsetX, int offsetY) override;

    std::vector<Position> GetCellPosition() override;

    void Rotate() override;

    void Move(int rows, int columns) override;

    void UndoRotation() override;

    std::map<int, std::vector<Position>> cells;
    std::vector<Color> colors;

protected:
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;

    int *dynamicData; // Example of raw pointer
};

// Constructor initializes dynamic resource
template<typename T>
Block<T>::Block() : dynamicData(new int[100]) { // Allocate array
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColor();
    rowOffset = 0;
    columnOffset = 0;
}

// Destructor cleans up raw pointer
template<typename T>
Block<T>::~Block() {
    delete[] dynamicData; // Release memory
    dynamicData = nullptr; // Avoid dangling pointer
}
