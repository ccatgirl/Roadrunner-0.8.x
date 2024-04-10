#include "blockitem.hpp"
#include <world/world.hpp>
#include <block/block.hpp>

using namespace RoadRunner::items;
using RoadRunner::block::Block;

bool BlockItem::useOn(
	RoadRunner::inventory::ItemInstance* instance, 
	RoadRunner::Player* player,  
	RoadRunner::world::World* world, 
	int x, int y, int z, 
	int face, float faceX, float faceY, float faceZ
){
	//check adventure flag allowInteract

	int blockID = world->get_block_id(x, y, z);
	//TODO if(blockID && blockID->field_78) face = 1;
	/*else*/{
		
		switch(face){
			case 0:
				--y;
				break;
			case 1:
				++y;
				break;
			case 2:
				--z;
				break;
			case 3:
				++z;
				break;
			case 4:
				--x;
				break;
			case 5:
				++x;
				break;
		}
	}

	if(instance->count == 0 || /*TODO !world->mayPlace*/false){
		return 0;
	}

	Block* block = Block::blocks[this->blockID];
	int meta = this->getLevelDataForAuxValue(instance->meta);

	meta = block->getPlacementDataValue(world, x, y, z, face, faceX, faceY, faceZ, player, meta);

	world->set_block(x, y, z, this->blockID, meta, 3);

	return true;
}