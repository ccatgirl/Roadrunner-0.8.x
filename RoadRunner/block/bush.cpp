#include <block/block.hpp>
using namespace RoadRunner::world;
using namespace RoadRunner::block;

void Bush::neighborChanged(World* world, int x, int y, int z, int nX, int nY, int nZ, int oldid){
	Block::neighborChanged(world, x, y, z, nX, nY, nZ, oldid);
	//TODO: this->checkAlive(world, x, y, z);
}
