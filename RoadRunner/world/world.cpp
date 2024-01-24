
#include "world/world.hpp"
#include "world/chunk.hpp"
#include <stdint.h>

RoadRunner::world::World::World(unsigned int seed){
	this->seed = seed;
	for(int32_t i = 0; i < 256; ++i){
		this->chunks[i] = new RoadRunner::world::Chunk((i & 0xf0) >> 4, i & 0xf);
	}
}

uint8_t RoadRunner::world::World::get_block_id(uint32_t x, uint32_t y, uint32_t z) {
	int chunkX = x / 16;
	int chunkZ = z / 16;
	int index = chunkX << 4 | chunkZ;
	if(index > 255) return 0; //TODO blankChunk
	RoadRunner::world::Chunk* chunk = this->chunks[index];
	if(chunk) return chunk->get_block_id(x & 0xf, y, z & 0xf);
	return 0;
}

uint8_t RoadRunner::world::World::get_block_meta(uint32_t x, uint32_t y, uint32_t z) {
	int chunkX = x / 16;
	int chunkZ = z / 16;
	int index = chunkX << 4 | chunkZ;
	if(index > 255) return 0; //TODO blankChunk
	RoadRunner::world::Chunk* chunk = this->chunks[index];
	if(chunk) return chunk->get_block_meta(x & 0xf, y, z & 0xf);
	return 0;
}

void RoadRunner::world::World::set_block(uint32_t x, uint32_t y, uint32_t z, uint8_t id, uint8_t meta, uint8_t flags){
	int chunkX = x / 16;
	int chunkZ = z / 16;
	int index = chunkX << 4 | chunkZ;
	if(index > 255) return;
	RoadRunner::world::Chunk* chunk = this->chunks[index];
	if(chunk){
		chunk->set_block_id(x & 0xf, y, z & 0xf, id);
		chunk->set_block_meta(x & 0xf, y, z & 0xf, meta);
	}else{
		//TODO should never happen, but maybe try to create a new chunk?
	}
	//TODO send to client if some flag is set?
}
