#include <cstdint>
#include <block/block.hpp>
#include <world/world.hpp>
#include <gamemode.hpp>
#include <entity/player.hpp>
#include <inventory/iteminstance.hpp>
using RoadRunner::block::Block;
using RoadRunner::inventory::ItemInstance;
using RoadRunner::world::World;
using RoadRunner::utils::Vec3;
RoadRunner::GameMode::GameMode(RoadRunner::entity::Player* player){
	this->player = player;
}
bool RoadRunner::GameMode::useItemOn(RoadRunner::entity::Player* player, World* world, ItemInstance* item, int x, int y, int z, int face, Vec3* something){
	float faceX = something->x - x;
	float faceY = something->y - y;
	float faceZ = something->z - z;

	int blockID = world->get_block_id(x, y, z);
	if(blockID == Block::invisible_bedrock->blockID) return false;

	if(blockID > 0 && Block::blocks[blockID]->use(world, x, y, z, player)){
		return true;
	}

	if(!item->isItem()) return false;

	if(!this->isCreativeType()){
		return item->useOn(player, world, x, y, z, face, faceX, faceY, faceZ);
	}

	/* TODO reset damage back
	v20 = ItemInstance::getAuxValue(selected);
	count = selected->count;
	v22 = v20;
	v19 = ItemInstance::useOn(selected, player, level, x, y, z, face, faceX, faceY, faceZ);
	ItemInstance::setAuxValue(selected, v22);
	selected->count = count;
	return v19;
    */
	return item->useOn(player, world, x, y, z, face, faceX, faceY, faceZ);

}
void RoadRunner::GameMode::destroyBlock(int x, int y, int z, int side){
	RoadRunner::world::World* world = Server::INSTANCE->world; //TODO multiworld
	uint8_t id = world->get_block_id(x, y, z);
	uint8_t meta = world->get_block_meta(x, y, z);

	Block* block = Block::blocks[id];
	

	if(!block){
		printf("%s tried to destroy invalid block %d!\n", this->player->username.c_str(), id);
		RoadRunner::Server::INSTANCE->send_block_data(x, y, z, id, meta);
		return;
	}

	//TODO adventure settings

	
	block->playerWillDestroy(world, x, y, z, meta, this->player);
	world->set_block(x, y, z, 0, 0, 3);
	//int ret = world->set_block(x, y, z, 0, 0, 3);
	//if(!ret) return
	// 
	//block->destroy(world, x, y, z, meta); TODO block->destroy
}
