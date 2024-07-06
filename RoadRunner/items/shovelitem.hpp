#pragma once
#include "diggeritem.hpp"

namespace RoadRunner {
	namespace items{
		struct ShovelItem : public DiggerItem{
			public:
				ShovelItem(int id, Item::Tier* tier);
				virtual bool canDestroySpecial(RoadRunner::block::Block* block);
		};
	}
}
