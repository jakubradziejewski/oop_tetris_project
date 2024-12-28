#include "gtest/gtest.h"
#include "../grid.h"
#include "gtest/gtest.h"


// Initialization tests
TEST(GridTest, GridInitialization) {
    Grid grid;
    for (int row = 0; row < grid.gridPositions.size(); ++row) {
        for (int col = 0; col < grid.gridPositions[row].size(); ++col) {
            EXPECT_EQ(grid.gridPositions[row][col].state, BlockType::None);
        }
    }
}

// Row clearing tests
TEST(GridTest, ClearMultipleFullRows) {
    Grid grid;
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < grid.gridPositions[row].size(); ++col) {
            grid.gridPositions[row][col].state = BlockType::LBlock;
        }
    }
    int cleared = grid.ClearFullRows();
    EXPECT_EQ(cleared, 2);
}

// Row movement tests
TEST(GridTest, MoveRowDown) {
    Grid grid;
    for (int col = 0; col < grid.gridPositions[0].size(); ++col) {
        grid.gridPositions[0][col].state = BlockType::LBlock;
    }
    grid.ClearFullRows();
    for (int col = 0; col < grid.gridPositions[1].size(); ++col) {
        EXPECT_EQ(grid.gridPositions[1][col].state, BlockType::None);
    }
}