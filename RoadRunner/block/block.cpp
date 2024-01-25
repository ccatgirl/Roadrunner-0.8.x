#include <block/block.hpp>
#include <cstdio>

using RoadRunner::block::Block;
Block *Block::blocks[256];
Block *Block::stone;
Block *Block::grass;
Block *Block::dirt;



Block::Block(uint8_t blockid) {
    if (Block::blocks[blockid]) {
        printf("Block %d already exists!\n", blockid);
    }
    Block::blocks[blockid] = this;
}

void Block::initBlocks() {

    Block::stone = new StoneBlock(1); // TODO properties such as explodeable, breakTime(1.5, 10.0)
    Block::grass = new GrassBlock(2);
    Block::dirt = new DirtBlock(3);
}

