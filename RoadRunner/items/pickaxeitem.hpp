#pragma once
#include "diggeritem.hpp"

namespace RoadRunner{
	namespace items{
		struct PickaxeItem : public DiggerItem{
			public:
				PickaxeItem(int id, Item::Tier* tier);
				virtual bool canDestroySpecial(RoadRunner::block::Block* block);
				virtual float getDestroySpeed(RoadRunner::inventory::ItemInstance* item, RoadRunner::block::Block* block);
		};
	}
}
