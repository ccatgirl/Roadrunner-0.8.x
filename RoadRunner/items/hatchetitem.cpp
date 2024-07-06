#include "hatchetitem.hpp"
#include <block/block.hpp>

using namespace RoadRunner::items;
using namespace RoadRunner::block;

HatchetItem::HatchetItem(int32_t id, Item::Tier* tier) : DiggerItem(id, tier){
	this->damageAgainstEntity = tier->entityDamage + 3;

	std::vector<Block*> vec = {
		Block::wood,
		Block::bookshelf,
		Block::treeTrunk,
		//TODO chest Block::chest,
		Block::woodSlab,
		Block::woodSlabHalf
	};
	this->setTiles(&vec);
}
float HatchetItem::getDestroySpeed(RoadRunner::inventory::ItemInstance* item, RoadRunner::block::Block* block){
	if(block && block->material == Material::wood) return this->efficiencyMultiplier;
	return DiggerItem::getDestroySpeed(item, block);
}
