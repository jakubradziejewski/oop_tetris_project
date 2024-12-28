#include "gtest/gtest.h"
#include "../block.h"
#include "../blocks.h"



// Test for LBlock
TEST(BlockTest, LBlockInitialization) {
    LBlock block;
    EXPECT_EQ(block.id, BlockType::LBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // LBlock has 4 tiles
}

// Test for JBlock
TEST(BlockTest, JBlockInitialization) {
    JBlock block;
    EXPECT_EQ(block.id, BlockType::JBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // JBlock has 4 tiles
}

// Test for IBlock
TEST(BlockTest, IBlockInitialization) {
    IBlock block;
    EXPECT_EQ(block.id, BlockType::IBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // IBlock has 4 tiles
}

// Test for OBlock
TEST(BlockTest, OBlockInitialization) {
    OBlock block;
    EXPECT_EQ(block.id, BlockType::OBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // OBlock has 4 tiles
}

// Test for SBlock
TEST(BlockTest, SBlockInitialization) {
    SBlock block;
    EXPECT_EQ(block.id, BlockType::SBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // SBlock has 4 tiles
}

// Test for TBlock
TEST(BlockTest, TBlockInitialization) {
    TBlock block;
    EXPECT_EQ(block.id, BlockType::TBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // TBlock has 4 tiles
}

// Test for ZBlock
TEST(BlockTest, ZBlockInitialization) {
    ZBlock block;
    EXPECT_EQ(block.id, BlockType::ZBlock);
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // ZBlock has 4 tiles
}

// Test for GameOver state
TEST(BlockTest, GameOverState) {
    Block<LBlock> block;
    block.id = BlockType::GameOver;
    EXPECT_EQ(block.id, BlockType::GameOver);
}
TEST(BlockTest, MoveBlockDown) {
    LBlock block;
    block.Move(1, 0); // Move down by 1 row
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 1); // Initial row + 1
    EXPECT_EQ(positions[0].column, 5); // Initial column (2 + 3) remains the same
}

TEST(BlockTest, MoveBlockRight) {
    LBlock block;
    block.Move(0, 1); // Move right by 1 column
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 0); // Initial row remains the same
    EXPECT_EQ(positions[0].column, 6); // Initial column (2 + 3) + 1
}
TEST(BlockTest, RotateBlock) {
    LBlock block;
    block.Rotate(); // Rotate the block
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 0); // Row after rotation
    EXPECT_EQ(positions[0].column, 4); // Column after rotation (1 + 3)
}

TEST(BlockTest, UndoRotation) {
    LBlock block;
    block.Rotate(); // Rotate the block
    block.UndoRotation(); // Undo the rotation
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 0); // Row after undoing rotation
    EXPECT_EQ(positions[0].column, 5); // Column after undoing rotation (2 + 3)
}
TEST(BlockTest, GetCellPosition) {
    LBlock block;
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 0); // First tile row
    EXPECT_EQ(positions[0].column, 5); // First tile column (2 + 3)
    EXPECT_EQ(positions[1].row, 1); // Second tile row
    EXPECT_EQ(positions[1].column, 3); // Second tile column (0 + 3)
    EXPECT_EQ(positions[2].row, 1); // Third tile row
    EXPECT_EQ(positions[2].column, 4); // Third tile column (1 + 3)
    EXPECT_EQ(positions[3].row, 1); // Fourth tile row
    EXPECT_EQ(positions[3].column, 5); // Fourth tile column (2 + 3)
}
TEST(BlockTest, RotateStateCycling) {
    LBlock block;
    // Rotate the block multiple times to cycle through all states
    for (int i = 0; i < 4; ++i) {
        block.Rotate();
    }
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 0); // Row after cycling
    EXPECT_EQ(positions[0].column, 5); // Column after cycling (2 + 3)

    // Undo the rotation multiple times to cycle back
    for (int i = 0; i < 4; ++i) {
        block.UndoRotation();
    }
    positions = block.GetCellPosition();
    EXPECT_EQ(positions[0].row, 0); // Row after cycling back
    EXPECT_EQ(positions[0].column, 5); // Column after cycling back (2 + 3)
}

TEST(BlockTest, IBlockCellCount) {
    IBlock block;
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // IBlock has 4 tiles
}

TEST(BlockTest, OBlockCellCount) {
    OBlock block;
    auto positions = block.GetCellPosition();
    EXPECT_EQ(positions.size(), 4); // OBlock has 4 tiles
}