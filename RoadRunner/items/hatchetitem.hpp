#pragma once
#include "diggeritem.hpp"
namespace RoadRunner{
	namespace block{
		class Block;
	}

	namespace inventory{
		class ItemInstance;
	}

	namespace items{
		struct HatchetItem : public DiggerItem{
			public:
				HatchetItem(int32_t id, Item::Tier* tier);
				virtual float getDestroySpeed(RoadRunner::inventory::ItemInstance* item, RoadRunner::block::Block* block);
		};
	}
}


