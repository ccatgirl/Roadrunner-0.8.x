#include <block/block.hpp>
#include <entity/mob.hpp>
using namespace RoadRunner::block;
using namespace RoadRunner::entity;

int StairBlock::getPlacementDataValue(
	RoadRunner::world::World* world,
	int x, int y, int z,
	int face, float faceX, float faceY, float faceZ,
	Mob* mob,
	int meta
){
	int m = meta;
	if(face == 0 || (face != 1 && faceY > 0.5f)){
		m |= 4;
	}
	m &= 4;

	float fdir = ((mob->yaw * 4) / 360) + 0.5f;
	int direction = (int)fdir;
	if(fdir < (float)direction){
		--direction;
	}

	switch(direction & 3){
		case 0:
			return m | 2;
		case 1:
			return m | 1;
		case 2:
			return m | 3;
		default:
			return m;
	}
}
