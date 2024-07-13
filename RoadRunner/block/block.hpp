#pragma once
#include <cstdint>
#include "material/material.hpp"
#include <world/world.hpp>
#include <entity/player.hpp>

using RoadRunner::block::material::Material;
using RoadRunner::entity::Player;
using namespace RoadRunner::world;
using namespace RoadRunner::entity;
namespace RoadRunner {
	namespace entity{
		struct Mob;
	}
	namespace block{
		struct Block {
			static Block
				*stone,
				*grass,
				*dirt,
				*cobblestone, //stoneBrick
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
				*trapdoor,
				*stoneBrickSmooth,
				*ironFence,
				*thinGlass,
				*melon,
				*pumpkinStem,
				*melonStem,
				*fenceGate,
				*stairs_brick,
				*woodStairsDark,
				*woodStairsBirch,
				*woodStairsJungle,
				*stairs_stoneBrickSmooth,
				*netherBrick,
				*stairs_netherBricks,
				*activatorRail,
				*stairs_sandStone,
				*cobbleWall,
				*carrots,
				*potatoes,
				*quartzBlock,
				*stairs_quartz,
				*woodSlab,
				*woodSlabHalf,
				*hayBlock,
				*woolCarpet,
				*coalBlock,
				*beetroot,
				*stonecutterBench,
				*glowingObsidian,
				*netherReactor,
				*info_updateGame1,
				*info_updateGame2,
				*info_reserved6,
				*fire;
			static Block *blocks[256];
			static int lightBlock[256];
			static int lightEmission[256];

			static bool shouldTick[256];
			static bool solid[256];
			static bool translucent[256];

			static void initBlocks();


			uint8_t blockID;
			float blockHardness = 0; //TODO check
			float blockResistance = 0; //TODO check
			float slipperiness = 0.6f;

			float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

			material::Material* material;

			Block(uint8_t id, material::Material* material);
			Block* init();
			Block* setDestroyTime(float f);

			virtual bool isSolidRender();

			virtual int getPlacementDataValue(
				World* world,
				int x, int y, int z,
				int face, float faceX, float faceY, float faceZ,
				Mob* mob,
				int meta
			){
				return meta;
			}

			virtual bool mayPlace(World* world, int x, int y, int z);
			virtual bool mayPlace(World* world, int x, int y, int z, int side);

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);

			virtual bool isCubeShaped();

			void setShape(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
				this->minX = minX;
				this->minY = minY;
				this->minZ = minZ;
				this->maxX = maxX;
				this->maxY = maxY;
				this->maxZ = maxZ;
			}

			Block* setTicking(bool ticking){
				Block::shouldTick[this->blockID] = ticking;
				return this;
			}

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

			bool use(World* world, int32_t x, int32_t y, int32_t z, RoadRunner::entity::Player* player){
				return false;
			};

			virtual void onPlace(World* world, int32_t x, int32_t y, int32_t z);
			virtual void onRemove(World* world, int32_t x, int32_t y, int32_t z);
			void playerWillDestroy(World* world, int32_t x, int32_t y, int32_t z, int32_t meta, RoadRunner::entity::Player* player){}; //used only by door
		};

		struct StoneBlock : public Block{
			StoneBlock(uint8_t id): Block(id, Material::stone){};
		};

		struct ObsidianBlock : public StoneBlock{
			bool glowing;

			ObsidianBlock(uint8_t id) : StoneBlock(id){
				//field_5C = 255 TODO 5c
				this->glowing = 0;
			}
		};

		struct TorchBlock : public Block{
			TorchBlock(uint8_t id) : Block(id, Material::decoration){}

			virtual bool isCubeShaped(){
				return 0;
			}

			bool isConnection(World* world, int x, int y, int z);
			bool mayPlace(World* world, int x, int y, int z);
			bool checkCanSurvive(World* world, int x, int y, int z);
			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
			virtual int getPlacementDataValue(
				World* world,
				int x, int y, int z,
				int face, float faceX, float faceY, float faceZ,
				Mob* mob,
				int meta
			);

			virtual void onPlace(World* world, int32_t x, int32_t y, int32_t z);
			//TODO more
		};

		struct GrassBlock : public Block {
			GrassBlock(uint8_t id): Block(id, Material::dirt){}
		};

		struct DirtBlock : public Block {
			DirtBlock(uint8_t id): Block(id, Material::dirt){}
		};

		struct WoodBlock : public Block {
			WoodBlock(uint8_t id): Block(id, Material::wood){}
		};

		struct Bush : public Block{
			Bush(uint8_t id): Bush(id, Material::plant){}
			Bush(uint8_t id, Material* mat): Block(id, mat){
				this->setTicking(true);
			};
			virtual bool isCubeShaped(){
				return false;
			}
			virtual bool isSolidRender(){
				return false;
			}
			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct LiquidBlock : public Block{
			LiquidBlock(uint8_t id, Material* material): Block(id, material){}

			virtual bool isCubeShaped(){
				return false;
			}

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};
		struct LiquidBlockStatic : public LiquidBlock{
			LiquidBlockStatic(uint8_t id, Material* material): LiquidBlock(id, material){};

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct HeavyBlock: public Block{
			HeavyBlock(uint8_t id): Block(id, Material::sand){};

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct Sapling : public Bush{
			Sapling(uint8_t id): Bush(id){};
		};

		struct OreBlock : public Block{
			OreBlock(uint8_t id): Block(id, Material::stone){};
		};

		struct RotatedPillarBlock : public Block{
			RotatedPillarBlock(uint8_t id, Material* material): Block(id, material){};
			static uint8_t rotationArray[4];
			virtual int getPlacementDataValue(
				World* world,
				int x, int y, int z,
				int face, float faceX, float faceY, float faceZ,
				Mob* mob,
				int meta
				){
				int v11;
				if(face < 2){
					v11 = 0;
				}else{
					v11 = RotatedPillarBlock::rotationArray[face - 2];
				}
				return ((int)meta & 3) | v11;
			}
		};

		struct TreeBlock : public RotatedPillarBlock{
			TreeBlock(uint8_t id): RotatedPillarBlock(id, Material::wood){};
		};

		struct HayBlock : public RotatedPillarBlock{
			HayBlock(uint8_t id): RotatedPillarBlock(id, Material::dirt){

			}
		};

		struct LeafBlock : public Block{
			LeafBlock(uint8_t id): Block(id, Material::leaves){};
		};

		struct GlassBlock : public Block{
			GlassBlock(uint8_t id): Block(id, Material::glass){};
		};

		struct FireBlock : public Block{
			FireBlock(uint8_t id): Block(id, Material::fire){};

			virtual bool isCubeShaped(){
				return false;
			}

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct Mushroom : public Block{
			Mushroom(uint8_t id): Block(id, Material::plant){}
		};

		struct MetalBlock : public Block{
			MetalBlock(uint8_t id): Block(id, Material::metal){}
		};

		struct TntBlock : public Block{
			TntBlock(uint8_t id): Block(id, Material::explosive){}

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct WebBlock : public Block{
			WebBlock(uint8_t id): Block(id, Material::web){}

			virtual bool isCubeShaped(){
				return 0;
			}
		};

		struct TallGrass : public Bush{
			TallGrass(uint8_t id): Bush(id, Material::replaceable_plant){}
		};

		struct DeadBush: public Bush{
			DeadBush(uint8_t id): Bush(id, Material::replaceable_plant){}
		};

		struct ClothBlock: public Block{
			ClothBlock(uint8_t id): Block(id, Material::cloth){}
		};

		struct FlowerBlock: public Bush{
			FlowerBlock(uint8_t id): Bush(id){}
		};

		struct CropBlock : public Bush{
			CropBlock(uint8_t id): Bush(id){}
		};

		struct FarmBlock : public Block{
			FarmBlock(uint8_t id): Block(id, Material::dirt){}

			virtual bool isCubeShaped(){
				return false;
			}

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct ClayBlock : public Block{
			ClayBlock(uint8_t id): Block(id, Material::clay){}
		};

		struct WoolCarpetBlock : public Block{
			WoolCarpetBlock(uint8_t id): Block(id, Material::cloth){
				this->setShape(0, 0, 0, 1, 0.0625f, 1);
				//this->setTicking(true); mojang moment
			}

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);

			virtual bool isCubeShaped(){
				return 0;
			}

			virtual bool isSolidRender(){
				return false;
			}


		};

		struct LightGemBlock : public Block{
			LightGemBlock(uint8_t id, Material* material): Block(id, material){
				//field_5C = 255
			}
		};

		struct RedStoneOreBlock : public Block{
			bool emitsLight;

			RedStoneOreBlock(uint8_t id, bool emitsLight) : Block(id, Material::stone){

				if(emitsLight) this->setTicking(true);

				this->emitsLight = emitsLight;
			}
		};

		struct BookshelfBlock : public Block{
			BookshelfBlock(uint8_t id): Block(id, Material::wood){

			}
		};

		struct BaseRailBlock : public Block{
			bool powered;

			BaseRailBlock(uint8_t id, bool powered): Block(id, Material::decoration){
				this->powered = powered;
				this->setShape(0.0f, 0.0f, 0.0f, 1.0f, 0.125f, 1.0f);
			}
			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
			virtual bool isCubeShaped(){
				return false;
			}

			virtual bool isSolidRender(){
				return false;
			}
		};

		struct PoweredRailBlock : public BaseRailBlock{
			PoweredRailBlock(uint8_t id) : BaseRailBlock(id, true){

			}
		};

		struct RailBlock : public BaseRailBlock{
			RailBlock(uint8_t id) : BaseRailBlock(id, false){

			}
		};

		struct ReedBlock : public Block{
			ReedBlock(uint8_t id): Block(id, Material::plant){
				this->setShape(0.125f, 0, 0.125f, 0.875f, 1.0f, 0.875f);
				this->setTicking(true);
			}

			virtual bool isCubeShaped(){
				return false;
			}

			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct CactusBlock : public Block{
			CactusBlock(uint8_t id): Block(id, Material::cactus){
				this->setTicking(true);
			}
			virtual bool isCubeShaped(){
				return false;
			}
			virtual bool isSolidRender(){
				return false;
			}
			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
		};

		struct BedBlock : public Block{
			BedBlock(uint8_t id): Block(id, Material::cloth){
				this->_setShape();
			}

			void _setShape(){ //a bit useless?
				this->setShape(0.0f, 0.0f, 0.0f, 1.0f, 0.5625f, 1.0f);
			}
			virtual void neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid);
			virtual bool isSolidRender(){
				return false;
			}
		};

		struct SlabBlock : public Block{
			bool isFull;

			SlabBlock(uint8_t id, Material* material, bool isFull): Block(id, material){
				this->isFull = isFull;
				//TODO call updateDefaultShape
				this->setLightBlock(255);
			}

			virtual int getPlacementDataValue(
				World* world,
				int x, int y, int z,
				int face, float faceX, float faceY, float faceZ,
				Mob* mob,
				int meta
			){
				if(!this->isFull && (face == 0 || (face != 1 && faceY > 0.5f))){
						return (int)meta | 8;
				}

				return (int)meta;
			}

			virtual bool isCubeShaped(){
				return this->isFull;
			}
		};

		struct WoodSlabBlock : public SlabBlock{
			WoodSlabBlock(uint8_t id, bool isFull) : SlabBlock(id, Material::wood, isFull){}
		};

		struct StoneSlabBlock : public SlabBlock{
			StoneSlabBlock(uint8_t id, bool isFull) : SlabBlock(id, Material::stone, isFull){}
		};

		struct QuartzBlock : public Block{
			QuartzBlock(uint8_t id) : Block(id, Material::stone){}

		};

		struct StairBlock : public Block{
				Block* blockBase;
				int blockMeta;

				StairBlock(uint8_t id, Block* block, int blockMeta) : Block(id, block->material){\
					this->blockBase = block;
					this->blockMeta = blockMeta;

					this->setDestroyTime(block->blockHardness);
					this->setExplodeable(block->blockResistance / 3.0f);
					this->setLightBlock(255);
					//TODO this->field_5C = block->field_5C;
				}

				virtual bool isCubeShaped(){
					return 0;
				}

				int getPlacementDataValue(
					World* world,
					int x, int y, int z,
					int face, float faceX, float faceY, float faceZ,
					Mob* mob,
					int meta
				);


				~StairBlock(){
					this->blockBase = 0;
				}
		};
	}
}
