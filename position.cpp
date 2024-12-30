#include "position.h"

Position::Position(int row, int column, BlockType state) {
    this->row = row;
    this->column = column;
    this->state = state;
}
