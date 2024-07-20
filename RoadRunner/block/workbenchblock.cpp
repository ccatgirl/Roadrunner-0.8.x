#include <block/block.hpp>

using namespace RoadRunner::block;
using namespace RoadRunner::world;


WorkbenchBlock::WorkbenchBlock(uint8_t id) : Block(id, Material::wood){

}
bool WorkbenchBlock::use(World* world, int32_t x, int32_t y, int32_t z, RoadRunner::entity::Player* player){
	//TODO: Player::startCrafting(player, x, y, z, 1);
	return 1;
}
