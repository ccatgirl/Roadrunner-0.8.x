#include "shovelitem.hpp"
#include <block/block.hpp>
using namespace RoadRunner::block;
using namespace RoadRunner::items;

ShovelItem::ShovelItem(int id, Item::Tier* tier) : DiggerItem(id, tier){
	this->damageAgainstEntity = tier->entityDamage + 1;
	std::vector<Block*> blocks = {
		Block::grass,
		Block::dirt,
		Block::sand,
		Block::gravel,
		//TODO Block::topSnow,
		//TODO Block::snow,
		Block::clay,
		Block::farmland
	};
	this->setTiles(&blocks);
}

bool ShovelItem::canDestroySpecial(RoadRunner::block::Block* block){
	return block == block->snow || block == block->topSnow;
}
