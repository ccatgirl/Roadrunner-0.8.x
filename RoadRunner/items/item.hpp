#pragma once
#include <cstdint>
#include <stdio.h>
#include <inventory/iteminstance.hpp>

namespace RoadRunner {
	namespace items{
		class Item{
			public:
				static Item* items[512];
				
				static Item* shovel_iron;
				static Item* pickAxe_iron;
				static Item* hatchet_iron;
				static Item* flintAndSteel;
				static Item* apple;
				static Item* bow;
				static Item* arrow;
				static Item* coal;
				static Item* emerald;
				static Item* ironIngot;
				static Item* goldIngot;
				static Item* sword_iron;
				static Item* sword_wood;
				static Item* shovel_wood;
				static Item* pickAxe_wood;
				static Item* hatchet_wood;
				static Item* sword_stone;
				static Item* shovel_stone;
				static Item* pickAxe_stone;
				static Item* hatchet_stone;
				static Item* sword_emerald;
				static Item* shovel_emerald;
				static Item* pickAxe_emerald;
				static Item* hatchet_emerald;
				static Item* stick;
				static Item* bowl;
				static Item* mushroomStew;
				static Item* sword_gold;
				static Item* shovel_gold;
				static Item* pickAxe_gold;
				static Item* hatchet_gold;
				static Item* string;
				static Item* feather;
				static Item* sulphur;
				static Item* hoe_wood;
				static Item* hoe_stone;
				static Item* hoe_iron;
				static Item* hoe_emerald;
				static Item* hoe_gold;
				static Item* seeds_wheat;
				static Item* wheat;
				static Item* bread;
				static Item* helmet_cloth;
				static Item* chestplate_cloth;
				static Item* leggings_cloth;
				static Item* boots_cloth;
				static Item* helmet_chain;
				static Item* chestplate_chain;
				static Item* leggings_chain;
				static Item* boots_chain;
				static Item* helmet_iron;
				static Item* chestplate_iron;
				static Item* leggings_iron;
				static Item* boots_iron;
				static Item* helmet_diamond;
				static Item* chestplate_diamond;
				static Item* leggings_diamond;
				static Item* boots_diamond;
				static Item* helmet_gold;
				static Item* chestplate_gold;
				static Item* leggings_gold;
				static Item* boots_gold;
				static Item* flint;
				static Item* porkChop_raw;
				static Item* porkChop_cooked;
				static Item* painting;
				static Item* sign;
				static Item* door_wood;
				static Item* bucket;
				static Item* minecart;
				static Item* saddle;
				static Item* door_iron;
				static Item* redStone;
				static Item* snowBall;
				static Item* leather;
				static Item* brick;
				static Item* clay;
				static Item* reeds;
				static Item* paper;
				static Item* book;
				static Item* slimeBall;
				static Item* egg;
				static Item* compass;
				static Item* clock;
				static Item* yellowDust;
				static Item* dye_powder;
				static Item* bone;
				static Item* sugar;
				static Item* cake;
				static Item* bed;
				static Item* shears;
				static Item* melon;
				static Item* seeds_pumpkin;
				static Item* seeds_melon;
				static Item* beef_raw;
				static Item* beef_cooked;
				static Item* chicken_raw;
				static Item* chicken_cooked;
				static Item* mobPlacer;
				static Item* carrot;
				static Item* potato;
				static Item* potatoBaked;
				static Item* pumpkinPie;
				static Item* netherbrick;
				static Item* netherQuartz;
				static Item* camera;
				static Item* beetroot;
				static Item* seeds_beetroot;
				static Item* beetrootSoup;
				

				static void initItems();

				int32_t itemID;
				int32_t maxItemDamage;
				int32_t maxStackSize;


				bool stackedByData;

				Item(int32_t id){
					this->itemID = id + 256;
					this->maxItemDamage = 0;
					this->maxStackSize = 64;
					this->stackedByData = 0;

					if(Item::items[this->itemID]){
						printf("Item conflict id @ %d! Id already used\n", this->itemID);
					}

					Item::items[this->itemID] = this;
				};
				
				virtual ~Item(){
					
				}
				
				Item* setMaxDamage(int dmg){
					this->maxItemDamage = dmg;
					return this;
				}

				Item* setStackedByData(bool b){
					this->stackedByData = b;
					return this;
				}

				virtual bool useOn(RoadRunner::inventory::ItemInstance* instance, RoadRunner::entity::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ){
					return 0;
				}

				virtual int getLevelDataForAuxValue(int meta){
					return 0;
				}
				
				class Tier{
					public:
						static Item::Tier WOOD;
						static Item::Tier STONE;
						static Item::Tier IRON;
						static Item::Tier DIAMOND; //Emerald*
						static Item::Tier GOLD;
						
						int level;
						int durability;
						float efficiencyMultiplier;
						int entityDamage;
						
						Tier(int level, int durability, float efficiencyMultiplier, int entityDamage){
							this->level = level;
							this->durability = durability;
							this->efficiencyMultiplier = efficiencyMultiplier;
							this->entityDamage = entityDamage;
						}
				};
		};
	}
}
