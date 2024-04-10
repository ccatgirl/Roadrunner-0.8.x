#include "iteminstance.hpp"
#include <items/item.hpp>
#include <block/block.hpp>

using namespace RoadRunner::inventory;

ItemInstance::ItemInstance(RoadRunner::items::Item* item, int count, int meta){
	this->init(item->itemID, count, meta);
}
ItemInstance::ItemInstance(RoadRunner::block::Block* block, int count, int meta){
	this->init(block->blockID, count, meta);
}

ItemInstance::ItemInstance(int id, int count, int meta){
	this->init(id, count, meta);
}

bool ItemInstance::isItem(){
	return this->item != 0;
}
void ItemInstance::_setItem(int id){
	bool valid;
	this->item = id < 512 ? RoadRunner::items::Item::items[id] : 0;
	valid = this->item || id == 0;
	this->isValid = valid;

	if(valid){
		this->block = id < 256 ? RoadRunner::block::Block::blocks[id] : 0;
	}else{
		this->item = 0;
		this->block = 0;
		this->meta = this->count = -1;
	}
}

bool ItemInstance::useOn(
	RoadRunner::Player* player, 
	RoadRunner::world::World* world, 
	int x, int y, int z, 
	int face, float faceX, float faceY, float faceZ
){
	return this->item->useOn(this, player, world, x, y, z, face, faceX, faceY, faceZ);
}