#include <cstdint>
#include <block/block.hpp>
#include <world/world.hpp>
#include <gamemode.hpp>
#include <player.hpp>

using RoadRunner::block::Block;

RoadRunner::GameMode::GameMode(RoadRunner::Player* player){
	this->player = player;
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