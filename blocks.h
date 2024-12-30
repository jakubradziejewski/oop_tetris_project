#pragma once

#include "block.h"
#include "position.h"
#include "block_types.h"

class LBlock : public Block<LBlock> {
public:
    LBlock();
};

class JBlock : public Block<JBlock> {
public:
    JBlock();
};

class IBlock : public Block<IBlock> {
public:
    IBlock();
};

class OBlock : public Block<OBlock> {
public:
    OBlock();
};

class SBlock : public Block<SBlock> {
public:
    SBlock();
};

class TBlock : public Block<TBlock> {
public:
    TBlock();
};

class ZBlock : public Block<ZBlock> {
public:
    ZBlock();
};