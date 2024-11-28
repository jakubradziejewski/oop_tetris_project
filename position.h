#pragma once

class Position {
public:
    explicit Position(int row = 0, int column = 0, int state = 0);
    int row;
    int column;
    int state;
};
