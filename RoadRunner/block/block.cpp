#include <block/block.hpp>
#include <block/material/material.hpp>
#include <cstdio>
#include <items/item.hpp>
#include <items/blockitem.hpp>

using RoadRunner::block::material::Material;
using RoadRunner::block::Block;
using namespace RoadRunner::items;

Block *Block::blocks[256];
int Block::lightBlock[256];
int Block::lightEmission[256];
bool Block::shouldTick[256];
bool Block::solid[256];
bool Block::translucent[256];

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
    *Block::leaves,
    *Block::sponge,
    *Block::glass,
    *Block::goldOre,
    *Block::ironOre,
    *Block::coalOre,
    *Block::treeTrunk,
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
    *Block::trapdoor,
    *Block::stoneBrickSmooth,
    *Block::ironFence,
    *Block::thinGlass,
    *Block::melon,
    *Block::pumpkinStem,
    *Block::melonStem,
    *Block::fenceGate,
    *Block::stairs_brick,
    *Block::woodStairsDark,
    *Block::woodStairsBirch,
    *Block::woodStairsJungle,
    *Block::netherBrick,
    *Block::stairs_netherBricks,
    *Block::activatorRail,
    *Block::stairs_sandStone,
    *Block::cobbleWall,
    *Block::carrots,
    *Block::potatoes,
    *Block::quartzBlock,
    *Block::stairs_quartz,
    *Block::woodSlab,
    *Block::woodSlabHalf,
    *Block::hayBlock,
    *Block::woolCarpet,
    *Block::coalBlock,
    *Block::beetroot,
    *Block::stonecutterBench,
    *Block::glowingObsidian,
    *Block::netherReactor,
    *Block::info_updateGame1,
    *Block::info_updateGame2,
    *Block::info_reserved6,
    *Block::fire;

void Block::onPlace(RoadRunner::world::World*, int32_t x, int32_t y, int32_t z){
    /* TODO all those classes
        BaseRailTile::onPlace(Level *,int,int,int)
        EntityTile::onPlace(Level *,int,int,int)
        FireTile::onPlace(Level *,int,int,int)
        HeavyTile::onPlace(Level *,int,int,int)
        LiquidTile::onPlace(Level *,int,int,int)
        LiquidTileDynamic::onPlace(Level *,int,int,int)
        PumpkinTile::onPlace(Level *,int,int,int)
        StairTile::onPlace(Level *,int,int,int)
        TorchTile::onPlace(Level *,int,int,int)
    */
}

void Block::onRemove(RoadRunner::world::World* world, int32_t x, int32_t y, int32_t z){
    /* TODO all those classes
        BaseRailTile::onRemove(Level *,int,int,int)
        ChestTile::onRemove(Level *,int,int,int)
        EntityTile::onRemove(Level *,int,int,int)
        FurnaceTile::onRemove(Level *,int,int,int)
        LeafTile::onRemove(Level *,int,int,int)
        StairTile::onRemove(Level *,int,int,int)
        TreeTile::onRemove(Level *,int,int,int)
    */
}
Block::Block(uint8_t blockid, Material* material) { //TODO Material

    this->blockID = blockid;
    this->material = material;
    //printf("Registering block %d %p\n", blockid, material);
    if (Block::blocks[blockid]) {
        printf("Block %d already exists!\n", blockid); //TODO throw exception maybe?
    }
   
}

Block* Block::init(){
    Block::blocks[this->blockID] = this;
    this->setShape(this->minX, this->minY, this->minZ, this->maxX, this->maxY, this->maxZ);
    bool solid = this->isSolidRender();

    Block::solid[this->blockID] = solid;
    
    Block::lightBlock[this->blockID] = solid ? 255 : 0;
    Block::translucent[this->blockID] = this->material->blocksLight();
    return this;
}

void Block::initBlocks() {

    for(int i = 0; i < 256; ++i){
        Block::blocks[i] = 0;
        Block::solid[i] = 0;
        Block::translucent[i] = 0;
        Block::lightEmission[i] = 0;
        Block::lightBlock[i] = 0;
        Block::shouldTick[i] = 0;
    }
    
    Block::stone = (new StoneBlock(1))->init()->setDestroyTime(1.5f)->setExplodeable(10.0f); //TODO add descriptionID?
    Block::grass = (new GrassBlock(2))->setDestroyTime(0.6f);
    Block::dirt = (new DirtBlock(3))->init()->setDestroyTime(0.5f);
    Block::cobblestone = (new Block(4, Material::stone))->init()->setDestroyTime(2.0f)->setExplodeable(10.0f);
    Block::wood = (new WoodBlock(5))->init()->setDestroyTime(2.0f)->setExplodeable(5.0f);
    Block::sapling = (new Sapling(6))->init()->setDestroyTime(0.0f);
    Block::bedrock = (new Block(7, Material::stone))->init()->setDestroyTime(-1.0f)->setExplodeable(6000000.0f);
    Block::water = (new LiquidBlock(8, Material::water))->init()->setDestroyTime(100.0f)->setLightBlock(3);
    Block::calmWater = (new LiquidBlockStatic(9, Material::water))->init()->setDestroyTime(100.0f)->setLightBlock(3);
    Block::lava = (new LiquidBlock(10, Material::lava))->init()->setDestroyTime(0.0f)->setLightEmission(1.0f)->setLightBlock(255);
    Block::calmLava = (new LiquidBlockStatic(11, Material::lava))->init()->setDestroyTime(0.0f)->setLightEmission(1.0f)->setLightBlock(255);
    Block::sand = (new HeavyBlock(12))->init()->setDestroyTime(0.5f);
    Block::gravel = (new HeavyBlock(13))->init()->setDestroyTime(0.6f);
    Block::goldOre = (new OreBlock(14))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::ironOre = (new OreBlock(15))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::coalOre = (new OreBlock(16))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::treeTrunk = (new TreeBlock(17))->init()->setDestroyTime(2.0f);
    Block::leaves = (new LeafBlock(18))->init()->setDestroyTime(0.2f)->setLightBlock(1);
    Block::sponge = (new Block(19, Material::sponge))->init()->setDestroyTime(0.6f);
    Block::glass = (new GlassBlock(20))->init()->setDestroyTime(0.3f);
    Block::lapisOre = (new OreBlock(21))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::lapisBlock = (new Block(22, Material::stone))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::sandStone = (new Block(24, Material::stone))->init()->setDestroyTime(0.8f); //in 0.8.1 it has its own class that extends MultiTextureTile, server doesnt really need it i think
    Block::bed = (new BedBlock(26))->init()->setDestroyTime(0.2f);
    Block::goldenRail = (new PoweredRailBlock(27))->init()->setDestroyTime(0.7f);
    Block::web = (new WebBlock(30))->init()->setLightBlock(1)->setDestroyTime(4.0f);
    Block::tallgrass = (new TallGrass(31))->init()->setDestroyTime(0.0f);
    Block::deadBush = (new DeadBush(32))->init()->setDestroyTime(0.0f);
    Block::cloth = (new ClothBlock(35))->init()->setDestroyTime(0.8f);
    Block::flower = (new FlowerBlock(37))->init()->setDestroyTime(0.0f);
    Block::rose = (new FlowerBlock(38))->init()->setDestroyTime(0.0f);
    Block::mushroom1 = (new Mushroom(39))->init()->setDestroyTime(0.0f);
    Block::mushroom2 = (new Mushroom(40))->init()->setDestroyTime(0.0f);
    Block::goldBlock = (new MetalBlock(41))->init()->setDestroyTime(3.0f)->setExplodeable(10.0f);
    Block::ironBlock = (new MetalBlock(42))->init()->setDestroyTime(5.0f)->setExplodeable(10.0f);
    //TODO stoneSlab (43)
    //TODO stoneSlabHalf (0x2C)
    Block::redBrick = (new Block(45, Material::stone))->init()->setDestroyTime(2.0f)->setExplodeable(10.0f);
    Block::tnt = (new TntBlock(46))->init()->setDestroyTime(0.0f);
    Block::bookshelf = (new BookshelfBlock(47))->init()->setDestroyTime(1.5f);
    Block::mossStone = (new Block(48, Material::stone))->init()->setDestroyTime(2.0f)->setExplodeable(10.0f);
    Block::obsidian = (new StoneBlock(49))->init()->setDestroyTime(10.0f)->setExplodeable(2000.0f);
    Block::torch = (new TorchBlock(50))->init()->setDestroyTime(0.0f)->setLightEmission(0.9375f);
    //TODO stairs_wood
    //TODO chest
    Block::diamondOre = (new OreBlock(56))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::diamondBlock = (new MetalBlock(57))->init()->setDestroyTime(5.0f)->setExplodeable(10.0f);
    //TODO workBench
    Block::crops = (new CropBlock(59))->init()->setDestroyTime(0.0f);
    Block::farmland = (new FarmBlock(60))->init()->setDestroyTime(0.6f);
    //TODO furnace
    //TODO furnace_lit
    //TODO sign
    //TODO door_wood
    //TODO ladder
    Block::rail = (new RailBlock(66))->init()->setDestroyTime(0.7f);
    //TODO stairs_stone
    //TODO wallSign
    //TODO door_iron
    Block::redStoneOre = (new RedStoneOreBlock(73, 0))->init()->setDestroyTime(3.0f)->setExplodeable(5.0f);
    Block::redStoneOre_lit = (new RedStoneOreBlock(74, 1))->init()->setDestroyTime(3.0f)->setLightEmission(0.625f)->setExplodeable(5.0f);
    //TODO topSnow
    //TODO ice
    //TODO snow
    Block::cactus = (new CactusBlock(81))->init()->setDestroyTime(0.4f);
    Block::clay = (new ClayBlock(82))->init()->setDestroyTime(0.6f);
    Block::reeds = (new ReedBlock(83))->init()->setDestroyTime(0.0f);
    //TODO fence
    //TODO pumpkin
    Block::netherrack = (new Block(87, Material::stone))->init()->setDestroyTime(0.4f);
    Block::lightGem = (new LightGemBlock(89, Material::glass))->init()->setDestroyTime(0.3f)->setLightEmission(1.0f);
    //TODO litPumpkin  Material::vegetable, extends Tile, 91
    //TODO cake 92
    Block::invisible_bedrock = (new Block(95, Material::stone))->init()->setDestroyTime(-1.0f)->setExplodeable(6000000.0f);
    //TODO trapdoor 96
    Block::stoneBrickSmooth = (new Block(98, Material::stone))->init()->setDestroyTime(1.5f)->setExplodeable(10.0f); //this thing is actually MultiTextureBlock
    //TODO ironFence ThinFenceTile 101
    //TODO thinGlass ThinFenceTile 102
    //TODO melon 103
    //TODO pumpkinStem
    //TODO melonStem
    //TODO fenceGate
    //TODO stairs_brick
    //TODO woodStairsDark
    //TODO woodStairsBirch
    //TODO woodStairsJungle
    Block::netherBrick = (new Block(112, Material::stone))->init()->setDestroyTime(2.0f)->setExplodeable(10.0f);
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
    Block::woolCarpet = (new WoolCarpetBlock(171))->init()->setDestroyTime(0.1f)->setLightBlock(0.0f);
    Block::coalBlock = (new MetalBlock(173))->init()->setDestroyTime(5.0f)->setExplodeable(10.0f);
    //TODO beetroot
    //TODO stonecutterBench
    //TODO glowingObsidian
    //TODO netherReactor
    Block::info_updateGame2 = (new Block(248, Material::dirt))->init()->setDestroyTime(1.0f);
    Block::info_updateGame2 = (new Block(249, Material::dirt))->init()->setDestroyTime(1.0f);
    Block::info_reserved6 = (new Block(255, Material::dirt))->init();
    Block::fire = (new FireBlock(51))->init()->setDestroyTime(0)->setLightEmission(1.0f);

    //certain specific blocks that use custom item classes manually register them



    int actualItemID = -256;
    int blockID = 0;

    
    do{
        if(Block::blocks[blockID]){
            if(!Item::items[blockID]){
                Item::items[blockID] = new BlockItem(actualItemID);
            }
        }
        ++blockID;
        ++actualItemID;
    }while(blockID < 256);

}

