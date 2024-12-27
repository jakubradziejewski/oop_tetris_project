#include "position.h"

// aggregation- Position is part of the Block class; Block doesn't own Position
// composition- Position is part of the Grid class; Grid own Position
Position::Position(int row, int column, int state) {
    this->row = row;
    this->column = column;
    this->state = state; // Initialize state during construction
}
