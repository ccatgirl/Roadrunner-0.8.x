#include "diggeritem.hpp"
#include <block/block.hpp>
using namespace RoadRunner::items;
using namespace RoadRunner::block;
DiggerItem::DiggerItem(int id, Item::Tier* tier) : Item(id){
	this->tier = tier;
	this->efficiencyMultiplier = tier->efficiencyMultiplier;
	this->maxStackSize = 1;
	this->setMaxDamage(tier->durability);
	this->damageAgainstEntity = tier->entityDamage;
	this->setTiles(0);using namespace RoadRunner::items;
}

float DiggerItem::getDestroySpeed(RoadRunner::inventory::ItemInstance* item, Block* block){
	if(block && this->effectiveAgainst[block->blockID]){
		return this->efficiencyMultiplier;
	}
	return 1.0;
}

void DiggerItem::setTiles(std::vector<Block*>* tiles){
	for(int i = 0; i < 256; ++i){
		this->effectiveAgainst[i] = 0;
	}
	if(tiles){
		for(int i = 0; i < tiles->size(); ++i){
			Block* block = tiles->at(i);
			this->effectiveAgainst[block->blockID] = 1;
		}
	}

}
