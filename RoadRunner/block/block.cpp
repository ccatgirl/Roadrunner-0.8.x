#include <block/block.hpp>
#include <cstdio>

using RoadRunner::block::Block;
Block *Block::blocks[256];
int Block::lightBlock[256];
int Block::lightEmission[256];

Block 
    *Block::stone,
    *Block::grass,
    *Block::dirt,
    *Block::cobblestone,
    *Block::wood,
    *Block::sapling,
    *Block::bedrock,
    *Block::water,
    *Block::calmWater,
    *Block::lava,
    *Block::calmLava,
    *Block::sand,
    *Block::gravel,
    *Block::goldOre,
    *Block::ironOre,
    *Block::coalOre,
    *Block::treeTrunk,
    *Block::leaves,
    *Block::sponge,
    *Block::glass,
    *Block::lapisOre,
    *Block::lapisBlock,
    *Block::sandStone,
    *Block::bed,
    *Block::goldenRail,
    *Block::web,
    *Block::tallgrass,
    *Block::deadBush,
    *Block::cloth,
    *Block::flower,
    *Block::rose,
    *Block::mushroom1,
    *Block::mushroom2,
    *Block::goldBlock,
    *Block::ironBlock,
    *Block::stoneSlab,
    *Block::stoneSlabHalf,
    *Block::redBrick,
    *Block::tnt,
    *Block::bookshelf,
    *Block::mossStone,
    *Block::obsidian,
    *Block::torch,
    *Block::stairs_wood,
    *Block::chest,
    *Block::diamondOre,
    *Block::diamondBlock,
    *Block::workBench,
    *Block::crops,
    *Block::farmland,
    *Block::furnace,
    *Block::furnace_lit,
    *Block::sign,
    *Block::door_wood,
    *Block::ladder,
    *Block::rail,
    *Block::stairs_stone,
    *Block::wallSign,
    *Block::door_iron,
    *Block::redStoneOre,
    *Block::redStoneOre_lit,
    *Block::topSnow,
    *Block::ice,
    *Block::snow,
    *Block::cactus,
    *Block::clay,
    *Block::reeds,
    *Block::fence,
    *Block::pumpkin,
    *Block::netherrack,
    *Block::lightGem,
    *Block::litPumpkin,
    *Block::cake,
    *Block::invisible_bedrock,



    *Block::info_updateGame1,
    *Block::info_updateGame2;

Block::Block(uint8_t blockid) { //TODO Material
    this->blockID = blockid;
    if (Block::blocks[blockid]) {
        printf("Block %d already exists!\n", blockid); //TODO throw exception maybe?
    }
    Block::blocks[blockid] = this;
}

Block* Block::init(){
    
    return this;
}

void Block::initBlocks() {

    Block::stone = (new StoneBlock(1))->init()->setDestroyTime(1.5f)->setExplodeable(10.0f); //TODO add descriptionID?
    Block::grass = (new GrassBlock(2))->setDestroyTime(0.6f);
    Block::dirt = (new DirtBlock(3))->init()->setDestroyTime(0.5f);
    Block::cobblestone = (new Block(4))->init()->setDestroyTime(2.0f)->setExplodeable(10.0f);
    Block::wood = (new WoodBlock(5))->init()->setDestroyTime(2.0f)->setExplodeable(5.0f);
    Block::sapling = (new Sapling(6))->init()->setDestroyTime(0.0f);
    Block::bedrock = (new Block(7))->init()->setDestroyTime(-1.0f)->setExplodeable(6000000.0f);
    Block::water = (new LiquidBlock(8))->init()->setDestroyTime(100.0f)->setLightBlock(3);
    Block::calmWater = (new LiquidBlockStatic(9))->init()->setDestroyTime(100.0f)->setLightBlock(3);
    Block::lava = (new LiquidBlock(10))->init()->setDestroyTime(0.0f)->setLightEmission(1.0f)->setLightBlock(255);
    Block::calmLava = (new LiquidBlockStatic(11))->init()->setDestroyTime(0.0f)->setLightEmission(1.0f)->setLightBlock(255);
    Block::sand = (new HeavyBlock(12))->init()->setDestroyTime(0.5f);
    Block::gravel = (new HeavyBlock(13))->init()->setDestroyTime(0.6f);
    Block::goldOre = (new OreBlock(14))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::ironOre = (new OreBlock(15))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::coalOre = (new OreBlock(16))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::treeTrunk = (new TreeBlock(17))->init()->setDestroyTime(2.0f);
    Block::leaves = (new LeafBlock(18))->init()->setDestroyTime(0.2f)->setLightBlock(1);
    Block::sponge = (new Block(19))->init()->setDestroyTime(0.6f);
    Block::glass = (new GlassBlock(20))->init()->setDestroyTime(0.3f);
    Block::lapisOre = (new OreBlock(21))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::lapisBlock = (new Block(22))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    //TODO sandstone (24, destroyTime: 0.8f)
    //TODO bed (26)
    //TODO goldenRail (27)
    //TODO web (30)
    //TODO tallgrass (31)
    //TODO deadBush (32)
    //TODO cloth(wool) (0x20 + 3)
    //TODO flower(dandelion) 37
    //TODO rose(blue rose) 38
    //TODO mushroom1(brown) 39
    //TODO mushroom2(red) 40
    //TODO goldBlock (0x28 + 1)
    //TODO ironBlock (0x2A)
    //TODO stoneSlab (0x2A + 1)
    //TODO stoneSlabHalf (0x2C)
    Block::redBrick = (new Block(45))->init()->setDestroyTime(2.0f)->setExplodeable(10.0f);
    //TODO tnt (0x2E)
    //TODO bookshelf (47)
    //TODO mossStone (48)
    //TODO obsidian (0x30 + 1)
    //TODO torch (50)
    //TODO stairs_wood
    //TODO chest
    //TODO diamondOre
    //TODO diamondBlock
    //TODO workBench
    //TODO crops
    //TODO farmland
    //TODO furnace
    //TODO furnace_lit
    //TODO sign
    //TODO door_wood
    //TODO ladder
    //TODO rail
    //TODO stairs_stone
    //TODO wallSign
    //TODO door_iron
    //TODO redStoneOre
    //TODO redStoneOre_lit
    //TODO topSnow
    //TODO ice
    //TODO snow
    //TODO cactus
    //TODO clay
    //TODO reeds
    //TODO fence
    //TODO pumpkin
    //TODO netherrack
    //TODO lightGem(glowstone)
    //TODO litPumpkin
    //TODO cake
    Block::invisible_bedrock = (new Block(95))->init()->setDestroyTime(-1.0f)->setExplodeable(6000000.0f);
    //TODO trapdoor
    //TODO stoneBrickSmooth
    //TODO ironFence
    //TODO thinGlass
    //TODO melon
    //TODO pumpkinStem
    //TODO melonStem
    //TODO fenceGate
    //TODO stairs_brick
    //TODO woodStairsDark
    //TODO woodStairsBirch
    //TODO woodStairsJungle
    //TODO netherBrick
    //TODO stairs_netherBricks
    //TODO activatorRail it is CakeTile(126) for some reason
    //TODO stairs_sandStone
    //TODO cobbleWall
    //TODO carrots
    //TODO potatoes
    //TODO quartzBlock
    //TODO stairs_quartz
    //TODO woodSlab
    //TODO woodSlabHalf
    //TODO hayBlock
    //TODO woolCarpet
    //TODO coalBlock
    //TODO beetroot
    //TODO stonecutterBench
    //TODO glowingObsidian
    //TODO netherReactor

    Block::info_updateGame2 = new Block(248);
    Block::info_updateGame2 = new Block(249);
    //TODO info_reserved6
    //TODO fire

    //ItemBlocks are initialized after
}

