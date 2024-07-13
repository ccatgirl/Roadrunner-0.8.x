#include <block/block.hpp>
#include <entity/mob.hpp>

using namespace RoadRunner::world;
using namespace RoadRunner::block;
using namespace RoadRunner::entity;
void TorchBlock::onPlace(World* world, int32_t x, int32_t y, int32_t z){
	if(world->get_block_meta(x, y, z) == 0){
		int meta = 0;
		if(world->isSolidBlockingTile(x - 1, y, z)) meta = 1;
		else if(world->isSolidBlockingTile(x + 1, y, z)) meta = 2;
		else if(world->isSolidBlockingTile(x, y, z - 1)) meta = 3;
		else if(world->isSolidBlockingTile(x, y, z + 1)) meta = 4;
		else if(this->isConnection(world, x, y - 1, z)) meta = 5;

		world->set_block(x, y, z, this->blockID, meta, 2);
	}
	//TODO checkCanSurvive here
}

bool TorchBlock::isConnection(World* world, int x, int y, int z){
	if(world->isSolidBlockingTile(x, y, z)) return 1;

	int id = world->get_block_id(x, y, z);
	return id == Block::glass->blockID;
	//TODO: return id == Block.fence->blockID || id == Block.glass->blockID || id == Block.cobbleWall->blockID;;
}

bool TorchBlock::checkCanSurvive(World* world, int x, int y, int z){
	if(this->mayPlace(world, x, y, z)) return 1;

	if(world->get_block_id(x, y, z) == this->blockID){
		/* TODO @realfreehij when item entities
		 * ZN4Tile14spawnResourcesEP5Leveliiii = this->super.vtable->_ZN4Tile14spawnResourcesEP5Leveliiii;
		v10 = a2->vtable->_ZN5Level7getDataEiii(a2, a3, a4, a5);
		ZN4Tile14spawnResourcesEP5Leveliiii(&this->super, a2, a3, a4, a5, v10);*/

		world->set_block(x, y, z, 0, 0, 3);
	}
	return 0;
}
void TorchBlock::neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid){
	//TODO: static liquid: neighborChanged
	bool cansurvive = this->checkCanSurvive(world, x, y, z);
	bool v14 = 0;
	if(cansurvive){
		int data = world->get_block_meta(x, y, z);

		if(world->isSolidBlockingTile(x - 1, y, z)) v14 = 0;
		else v14 = data == 1;

		if(!world->isSolidBlockingTile(x + 1, y, z) && data == 2) v14 = 1;
		if(!world->isSolidBlockingTile(x, y, z - 1) && data == 3) v14 = 1;
		if(!world->isSolidBlockingTile(x, y, z + 1) && data == 4) v14 = 1;

		if(!this->isConnection(world, x, y-1, z) && data == 5 || v14){
			/* TODO spawn drop
			 * ZN4Tile14spawnResourcesEP5Leveliiii = this->super.vtable->_ZN4Tile14spawnResourcesEP5Leveliiii;
			v16 = world->vtable->_ZN5Level7getDataEiii(world, x, y, z);
			ZN4Tile14spawnResourcesEP5Leveliiii(&this->super, world, x, y, z, v16);*/

			world->set_block(x, y, z, 0, 0, 3);
		}
	}
}

bool TorchBlock::mayPlace(World* world, int x, int y, int z){
	if(world->isSolidBlockingTile(x - 1, y, z)) return 1;
	if(world->isSolidBlockingTile(x + 1, y, z)) return 1;
	if(world->isSolidBlockingTile(x, y, z - 1)) return 1;
	if(world->isSolidBlockingTile(x, y, z + 1)) return 1;
	if(this->isConnection(world, x, y - 1, z)) return 1;
	return 0;
}
int TorchBlock::getPlacementDataValue(
	World* world,
	int x, int y, int z,
	int face, float faceX, float faceY, float faceZ,
	Mob* mob,
	int meta
){
	switch(face){
		case 1:
			if(TorchBlock::isConnection(world, x, y - 1, z)){
				return 5;
			}
			break;
		case 2:
			if(world->isSolidBlockingTile(x, y, z + 1)){
				return 4;
			}
			break;
		case 3:
			if(world->isSolidBlockingTile(x, y, z - 1)){
				return 3;
			}
			break;
		case 4:
			if(world->isSolidBlockingTile(x + 1, y, z)){
				return 2;
			}
			break;
		case 5:
			if(world->isSolidBlockingTile(x - 1, y, z)){
				return 1;
			}
			break;
	}


	return meta;
}
