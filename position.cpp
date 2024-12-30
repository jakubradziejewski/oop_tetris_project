#include "position.h"

// aggregation- Position is part of the Block class; Block doesn't own Position
// composition- Position is part of the Grid class; Grid owns Position
Position::Position(int row, int column, BlockType state) {
    this->row = row;
    this->column = column;
    this->state = state; // Initialize state during construction
}
