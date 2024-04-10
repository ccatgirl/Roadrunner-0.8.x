#pragma once
#include <stdint.h>
#include "item.hpp"

namespace RoadRunner {
	namespace items{
		class BlockItem : public Item{
			public:
				
				int blockID;

				BlockItem(int16_t id) : Item(id){
					this->blockID = id + 256;
				}

				virtual bool useOn(RoadRunner::inventory::ItemInstance* instance, RoadRunner::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ) override;
		};
	}
}