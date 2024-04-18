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

bool WoodSlabBlockItem::useOn(
	RoadRunner::inventory::ItemInstance* instance,
	RoadRunner::Player* player,
	RoadRunner::world::World* world,
	int x, int y, int z,
	int face, float faceX, float faceY, float faceZ
){
	if(instance->count == 0) return 0;
	int id = world->get_block_id(x, y, z);
	int meta = world->get_block_meta(x, y, z);
	int v17 = (meta >> 3) & 1;

	if(face == 1){
		if(v17){
			return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
		}
	}else if(face != 0 || v17 == 0){
		return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
	}

	if(id != Block::woodSlabHalf->blockID){
		return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
	}

	if((meta ^ instance->meta) << 29){ //wat
		return 0;
	}

	//TODO v18 = Block::woodSlabHalf->getAABB(level, x, y, z);
	//TODO if(level->isUnobstructed(v18)){
	//TODO make set_block return true
	world->set_block(x, y, z, Block::woodSlab->blockID, meta | instance->meta, 3);
	if(true){
		--instance->count;
	}
	//}
	return 1;
}

bool StoneSlabBlockItem::useOn(
	RoadRunner::inventory::ItemInstance* instance,
	RoadRunner::Player* player,
	RoadRunner::world::World* world,
	int x, int y, int z,
	int face, float faceX, float faceY, float faceZ
){
	if(instance->count == 0) return 0;
	int id = world->get_block_id(x, y, z);
	int meta = world->get_block_meta(x, y, z);

	int v16 = (meta >> 3) & 1;

	if(face == 1){
		if(v16){
			return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
		}
	}else if(face != 0 || v16 == 0){
		return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
	}

	if(id != Block::stoneSlabHalf->blockID){
		return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
	}

	int metaHalf = meta & 7;

	if(metaHalf != instance->meta){
		return BlockItem::useOn(instance, player, world, x, y, z, face, faceX, faceY, faceZ);
	}
	//TODO v18 = Block::stoneSlab->getAABB(level, x, y, z);
	//TODO if(level->isUnobstructed(v18)){
	//TODO make set_block return true
	world->set_block(x, y, z, Block::stoneSlab->blockID, metaHalf, 3);
	if(true){
		--instance->count;
	}
	//}

	return 1;
}
