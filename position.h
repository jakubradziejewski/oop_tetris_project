#pragma once
#include "block_types.h"

class Position {
public:
    explicit Position(int row = 0, int column = 0, BlockType state = BlockType::None);
    int row;
    int column;
    BlockType state;
};
