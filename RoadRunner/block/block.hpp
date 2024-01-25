#pragma once
#include <cstdint>

namespace RoadRunner {
    namespace block{
        class Block {
        public:
            static Block *Block::stone;
            static Block *Block::grass;
            static Block *Block::dirt;

            static Block *blocks[256];
            static void initBlocks();

            uint8_t blockID;
            Block(uint8_t id);
        };

        class StoneBlock : public Block{
        public:
            StoneBlock(uint8_t id): Block(id){};
        };

        class GrassBlock : public Block {
        public:
            GrassBlock(uint8_t id): Block(id){};
        };

        class DirtBlock : public Block {
        public:
            DirtBlock(uint8_t id): Block(id){};
        };

        
    }
}