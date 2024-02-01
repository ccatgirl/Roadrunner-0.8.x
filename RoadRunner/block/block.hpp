#pragma once
#include <cstdint>

namespace RoadRunner {
    namespace block{
        class Block {
        public:
            static Block
                *stone,
                *grass,
                *dirt,
                *cobblestone,
                *wood,
                *sapling,
                *bedrock,
                *water,
                *calmWater,
                *lava,
                *calmLava,
                *sand,
                *gravel,
                *goldOre,
                *ironOre,
                *coalOre,
                *treeTrunk,
                *leaves,
                *sponge,
                *glass,
                *lapisOre,
                *lapisBlock,
                *sandStone,
                *bed,
                *goldenRail,
                *web,
                *tallgrass,
                *deadBush,
                *cloth,
                *flower,
                *rose,
                *mushroom1,
                *mushroom2,
                *goldBlock,
                *ironBlock,
                *stoneSlab,
                *stoneSlabHalf,
                *redBrick,
                *tnt,
                *bookshelf,
                *mossStone,
                *obsidian,
                *torch,
                *stairs_wood,
                *chest,
                *diamondOre,
                *diamondBlock,
                *workBench,
                *crops,
                *farmland,
                *furnace,
                *furnace_lit,
                *sign,
                *door_wood,
                *ladder,
                *rail,
                *stairs_stone,
                *wallSign,
                *door_iron,
                *redStoneOre,
                *redStoneOre_lit,
                *topSnow,
                *ice,
                *snow,
                *cactus,
                *clay,
                *reeds,
                *fence,
                *pumpkin,
                *netherrack,
                *lightGem,
                *litPumpkin,
                *cake,
                *invisible_bedrock,

                *info_updateGame1,
                *info_updateGame2;
            static Block *blocks[256];
            static int lightBlock[256];
            static int lightEmission[256];
            static void initBlocks();


            uint8_t blockID;
            float blockHardness = 0; //TODO check
            float blockResistance = 0; //TODO check
            float slipperiness = 0.6;

            Block(uint8_t id);
            Block* init();
            Block* setDestroyTime(float f){
                this->blockHardness = f;
                if(this->blockResistance < (f * 5)){
                    this->blockResistance = f * 5;
                }

                return this;
            };
            Block* setExplodeable(float f){
                this->blockResistance = f * 3;
                return this;
            }
            Block* setLightBlock(int i){
                Block::lightBlock[this->blockID] = i;
                return this;
            }
            Block* setLightEmission(float f){
                Block::lightEmission[this->blockID] = (int)(f * 15);
                return this;
            }
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

        class WoodBlock : public Block {
        public:
            WoodBlock(uint8_t id): Block(id){};
        };

        class Bush : public Block{
        public:
            Bush(uint8_t id): Block(id){};
        };

        class LiquidBlock : public Block{
        public:
            LiquidBlock(uint8_t id): Block(id){};
        };
        class LiquidBlockStatic : public LiquidBlock{
        public:
            LiquidBlockStatic(uint8_t id): LiquidBlock(id){};
        };

        class HeavyBlock: public Block{
        public:
            HeavyBlock(uint8_t id): Block(id){};
        };

        class Sapling : public Bush{
        public:
            Sapling(uint8_t id): Bush(id){};
        };

        class OreBlock : public Block{
        public:
            OreBlock(uint8_t id): Block(id){};
        };

        class RotatedPillarBlock : public Block{
        public:
            RotatedPillarBlock(uint8_t id): Block(id){};
        };

        class TreeBlock : public RotatedPillarBlock{
        public:
            TreeBlock(uint8_t id): RotatedPillarBlock(id){};
        };

        class LeafBlock : public Block{
        public:
            LeafBlock(uint8_t id): Block(id){};
        };

        class GlassBlock : public Block{
        public:
            GlassBlock(uint8_t id): Block(id){};
        };
    }
}