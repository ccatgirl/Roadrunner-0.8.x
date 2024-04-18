#pragma once
#include <cstdint>
#include <stdio.h>
#include <inventory/iteminstance.hpp>

namespace RoadRunner {
	namespace items{
		class Item{
			public:
				static Item* items[512];


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

				Item* setMaxDamage(int dmg){
					this->maxItemDamage = dmg;
					return this;
				}

				Item* setStackedByData(bool b){
					this->stackedByData = b;
					return this;
				}

				virtual bool useOn(RoadRunner::inventory::ItemInstance* instance, RoadRunner::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ){
					return 0;
				}

				virtual int getLevelDataForAuxValue(int meta){
					return 0;
				}

				~Item(){};
		};
	}
}
