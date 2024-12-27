#pragma once

#include <memory>
#include <vector>
#include <stdexcept>
#include "blocks.h"

class BlockFactory {
public:
    virtual std::unique_ptr<BlockBase> createBlock(BlockType type) = 0;
    virtual std::vector<std::unique_ptr<BlockBase>> createAllBlocks() = 0;
    virtual ~BlockFactory() = default;
};

class TetrisBlockFactory : public BlockFactory {
public:
    std::unique_ptr<BlockBase> createBlock(BlockType type) override {
        switch(type) {
            case BlockType::LBlock: return std::make_unique<LBlock>();
            case BlockType::JBlock: return std::make_unique<JBlock>();
            case BlockType::IBlock: return std::make_unique<IBlock>();
            case BlockType::OBlock: return std::make_unique<OBlock>();
            case BlockType::SBlock: return std::make_unique<SBlock>();
            case BlockType::TBlock: return std::make_unique<TBlock>();
            case BlockType::ZBlock: return std::make_unique<ZBlock>();
            default: throw std::invalid_argument("Unknown block type");
        }
    }

    std::vector<std::unique_ptr<BlockBase>> createAllBlocks() override {
        std::vector<std::unique_ptr<BlockBase>> blocks;
        blocks.push_back(std::make_unique<IBlock>());
        blocks.push_back(std::make_unique<JBlock>());
        blocks.push_back(std::make_unique<LBlock>());
        blocks.push_back(std::make_unique<OBlock>());
        blocks.push_back(std::make_unique<SBlock>());
        blocks.push_back(std::make_unique<TBlock>());
        blocks.push_back(std::make_unique<ZBlock>());
        return blocks;
    }
};