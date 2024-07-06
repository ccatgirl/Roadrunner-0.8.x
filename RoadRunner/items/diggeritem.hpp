#pragma once
#include "item.hpp"
#include <stdint.h>
#include <vector>
namespace RoadRunner {

	namespace block{
		class Block;
	}

	namespace inventory{
		class ItemInstance;
	}

	namespace items{
		struct DiggerItem : public Item{
			public:
				Item::Tier* tier;
				float efficiencyMultiplier;
				int damageAgainstEntity;
				bool effectiveAgainst[256];

				DiggerItem(int id, Item::Tier* tier);

				void setTiles(std::vector<block::Block *> *tiles);

				virtual float getDestroySpeed(RoadRunner::inventory::ItemInstance*, RoadRunner::block::Block*);

				/*TODO:
					DiggerItem::getAttackDamage(Entity *)
					DiggerItem::isHandEquipped(void)
					DiggerItem::mineBlock(ItemInstance *,int,int,int,int,Mob *)
					DiggerItem::hurtEnemy(ItemInstance *,Mob *,Mob *)
				*/
		};
	}
}
