#pragma once
#include <cstdint>
#include "material/material.hpp"
#include <world/world.hpp>
#include <player.hpp>

using RoadRunner::block::material::Material;

namespace RoadRunner {
	namespace block{
		class Block {
		public:
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
			Block* setDestroyTime(float f){
				this->blockHardness = f;
				if(this->blockResistance < (f * 5)){
					this->blockResistance = f * 5;
				}

				return this;
			};

			virtual bool isSolidRender(){
				return true;
			}

			virtual int getPlacementDataValue(
				RoadRunner::world::World* world,
				int x, int y, int z,
				int face, float faceX, float faceY, float faceZ,
				Player* mob, //TODO Mob* mob
				float meta
			){
				return meta;
			}

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

			bool use(RoadRunner::world::World* world, int32_t x, int32_t y, int32_t z, RoadRunner::Player* player){
				return false;
			};

			virtual void onPlace(RoadRunner::world::World* world, int32_t x, int32_t y, int32_t z);
			virtual void onRemove(RoadRunner::world::World* world, int32_t x, int32_t y, int32_t z);
			void playerWillDestroy(RoadRunner::world::World* world, int32_t x, int32_t y, int32_t z, int32_t meta, RoadRunner::Player* player){}; //used only by door
		};

		class StoneBlock : public Block{
		public:
			char unknown;
			StoneBlock(uint8_t id): Block(id, Material::stone){
				this->unknown = 0;
			};
		};

		class TorchBlock : public Block{
			public:
				TorchBlock(uint8_t id) : Block(id, Material::decoration){}
		};

		class GrassBlock : public Block {
		public:
			GrassBlock(uint8_t id): Block(id, Material::dirt){};
		};

		class DirtBlock : public Block {
		public:
			DirtBlock(uint8_t id): Block(id, Material::dirt){};
		};

		class WoodBlock : public Block {
		public:
			WoodBlock(uint8_t id): Block(id, Material::wood){};
		};

		class Bush : public Block{
			public:
				Bush(uint8_t id): Bush(id, Material::plant){};
				Bush(uint8_t id, Material* mat): Block(id, mat){
					this->setTicking(true);
				};

				bool isSolidRender() override{
					return false;
				}
		};

		class LiquidBlock : public Block{
		public:
			LiquidBlock(uint8_t id, Material* material): Block(id, material){};
		};
		class LiquidBlockStatic : public LiquidBlock{
		public:
			LiquidBlockStatic(uint8_t id, Material* material): LiquidBlock(id, material){};
		};

		class HeavyBlock: public Block{
		public:
			HeavyBlock(uint8_t id): Block(id, Material::sand){};
		};

		class Sapling : public Bush{
		public:
			Sapling(uint8_t id): Bush(id){};
		};

		class OreBlock : public Block{
		public:
			OreBlock(uint8_t id): Block(id, Material::stone){};
		};

		class RotatedPillarBlock : public Block{
		public:
			RotatedPillarBlock(uint8_t id, Material* material): Block(id, material){};
		};

		class TreeBlock : public RotatedPillarBlock{
		public:
			TreeBlock(uint8_t id): RotatedPillarBlock(id, Material::wood){};
		};

		class LeafBlock : public Block{
		public:
			LeafBlock(uint8_t id): Block(id, Material::leaves){};
		};

		class GlassBlock : public Block{
		public:
			GlassBlock(uint8_t id): Block(id, Material::glass){};
		};

		class FireBlock : public Block{
		public:
			FireBlock(uint8_t id): Block(id, Material::fire){};
		};

		class Mushroom : public Block{
		public:
			Mushroom(uint8_t id): Block(id, Material::plant){}
		};

		class MetalBlock : public Block{
		public:
			MetalBlock(uint8_t id): Block(id, Material::metal){}
		};

		class TntBlock : public Block{
		public:
			TntBlock(uint8_t id): Block(id, Material::explosive){}
		};

		class WebBlock : public Block{
		public:
			WebBlock(uint8_t id): Block(id, Material::web){}
		};

		class TallGrass : public Bush{
		public:
			TallGrass(uint8_t id): Bush(id, Material::replaceable_plant){}
		};

		class DeadBush: public Bush{
		public:
			DeadBush(uint8_t id): Bush(id, Material::replaceable_plant){}
		};

		class ClothBlock: public Block{
		public:
			ClothBlock(uint8_t id): Block(id, Material::cloth){}
		};

		class FlowerBlock: public Bush{
		public:
			FlowerBlock(uint8_t id): Bush(id){}
		};

		class CropBlock : public Bush{
		public:
			CropBlock(uint8_t id): Bush(id){}
		};

		class FarmBlock : public Block{
		public:
			FarmBlock(uint8_t id): Block(id, Material::dirt){}
		};

		class ClayBlock : public Block{
		public:
			ClayBlock(uint8_t id): Block(id, Material::clay){}
		};

		class WoolCarpetBlock : public Block{
			public:
				WoolCarpetBlock(uint8_t id): Block(id, Material::cloth){
					this->setShape(0, 0, 0, 1, 0.0625f, 1);
					//this->setTicking(true); mojang moment
				}


				bool isSolidRender() override{
					return false;
				}
		};

		class LightGemBlock : public Block{
		public:
			LightGemBlock(uint8_t id, Material* material): Block(id, material){
				//field_5C = 255
			}
		};

		class RedStoneOreBlock : public Block{
		public:
			bool emitsLight;

			RedStoneOreBlock(uint8_t id, bool emitsLight) : Block(id, Material::stone){

				if(this->emitsLight) this->setTicking(true);

				this->emitsLight = emitsLight;
			}
		};

		class BookshelfBlock : public Block{
		public:
			BookshelfBlock(uint8_t id): Block(id, Material::wood){

			}
		};

		class BaseRailBlock : public Block{
			public:
				bool powered;

				BaseRailBlock(uint8_t id, bool powered): Block(id, Material::decoration){
					this->powered = powered;
					this->setShape(0.0f, 0.0f, 0.0f, 1.0f, 0.125f, 1.0f);
				}

				bool isSolidRender() override{
					return false;
				}
		};

		class PoweredRailBlock : public BaseRailBlock{
			public:
				PoweredRailBlock(uint8_t id) : BaseRailBlock(id, true){

				}
		};

		class RailBlock : public BaseRailBlock{
			 public:
				RailBlock(uint8_t id) : BaseRailBlock(id, false){

				}
		};

		class ReedBlock : public Block{
		public:
			ReedBlock(uint8_t id): Block(id, Material::plant){
				//Tile::setShape(v434, 0.125, 0.0, 0.125, 0.875, 1.0, 0.875); TODO shape
				this->setShape(0.125f, 0, 0.125f, 0.875f, 1.0f, 0.875f);
				this->setTicking(true);
			}
		};

		class CactusBlock : public Block{
			public:
				CactusBlock(uint8_t id): Block(id, Material::cactus){

					this->setTicking(true);
				}

				bool isSolidRender() override{
					return false;
				}
		};

		class BedBlock : public Block{
			 public:
				BedBlock(uint8_t id): Block(id, Material::cloth){
					this->_setShape();
				}

				void _setShape(){ //a bit useless?
					this->setShape(0.0f, 0.0f, 0.0f, 1.0f, 0.5625f, 1.0f);
				}

				bool isSolidRender() override{
					return false;
				}
		};

		class SlabBlock : public Block{
			public:
				bool isFull;

				SlabBlock(uint8_t id, Material* material, bool isFull): Block(id, material){
					this->isFull = isFull;
					//TODO call updateDefaultShape
					this->setLightBlock(255);
				}

				virtual int getPlacementDataValue(
					RoadRunner::world::World* world,
					int x, int y, int z,
					int face, float faceX, float faceY, float faceZ,
					Player* mob, //TODO Mob* mob
					float meta
				){
					if(!this->isFull && (face == 0 || (face != 1 && faceY > 0.5f))){
						return (int)meta | 8;
					}

					return (int)meta;
				}
		};

		class WoodSlabBlock : public SlabBlock{
			public:
				WoodSlabBlock(uint8_t id, bool isFull) : SlabBlock(id, Material::wood, isFull){

				}
		};

		class StoneSlabBlock : public SlabBlock{
			public:
				StoneSlabBlock(uint8_t id, bool isFull) : SlabBlock(id, Material::stone, isFull){

				}
		};

		class QuartzBlock : public Block{
			public:
				QuartzBlock(uint8_t id) : Block(id, Material::stone){

				}

		};

		class StairBlock : public Block{
			public:
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

				virtual int getPlacementDataValue(
					RoadRunner::world::World* world,
					int x, int y, int z,
					int face, float faceX, float faceY, float faceZ,
					Player* mob, //TODO Mob* mob
					float meta
				){
					int m = meta;
					if(face == 0 || (face != 1 && faceY > 0.5f)){
						m |= 4;
					}
					m &= 4;

					float fdir = ((mob->yaw * 4) / 360) + 0.5f;
					int direction = (int)fdir;
					if(fdir < (float)direction){
						--direction;
					}

					switch(direction & 3){
						case 0:
							return m | 2;
						case 1:
							return m | 1;
						case 2:
							return m | 3;
						default:
							return m;
					}
				}


				~StairBlock(){
					this->blockBase = 0;
				}
		};
	}
}
