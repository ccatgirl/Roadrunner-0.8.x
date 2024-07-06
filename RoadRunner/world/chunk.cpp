#include <world/chunk.hpp>
#include <cstring>
#include <block/block.hpp>
#include <server.hpp>
using namespace RoadRunner::block;
RoadRunner::world::BlankChunk* RoadRunner::world::BlankChunk::blankChunk;

RoadRunner::world::BlankChunk::BlankChunk(): Chunk(0, 0) {
	memset(this->block_ids, 97, sizeof(this->block_ids)); //invis bedrock
	memset(this->block_metas, 0, sizeof(this->block_metas));
	memset(this->blocklight, 0, sizeof(this->blocklight));
	memset(this->skylight, 0, sizeof(this->skylight));
}

bool RoadRunner::world::BlankChunk::set_block_id(int32_t x, int32_t y, int32_t z, uint8_t block_id) {
	//do nothing
	return false;
}

bool RoadRunner::world::BlankChunk::set_block_meta(int32_t x, int32_t y, int32_t z, uint8_t block_meta) {
	// do nothing
	return false;
}

RoadRunner::world::Chunk::Chunk(int32_t x, int32_t z) {
	this->x = x;
	this->z = z;
	this->world = Server::INSTANCE->world; //TODO mutliworld support
	memset(this->block_ids, 0, sizeof(this->block_ids));
	memset(this->block_metas, 0, sizeof(this->block_metas));
	memset(this->blocklight, 0, sizeof(this->blocklight));
	memset(this->skylight, 0, sizeof(this->skylight));
}

uint8_t RoadRunner::world::Chunk::get_block_id(int32_t x, int32_t y, int32_t z) {
	return this->block_ids[COORDS_TO_INDEX(x, y, z)];
}

bool RoadRunner::world::Chunk::set_block_id(int32_t x, int32_t y, int32_t z, uint8_t block_id) {

	uint8_t oldID = this->block_ids[COORDS_TO_INDEX(x, y, z)];

	if(block_id == oldID) return false;

	int worldX = this->x*16 + x;
	int worldZ = this->z*16 + z;

	this->block_ids[COORDS_TO_INDEX(x, y, z)] = block_id;

	if(oldID){
		Block::blocks[oldID]->onRemove(this->world, worldX, y, worldZ);
	}
	NBARR_SET(COORDS_TO_INDEX(x, y, z), 0, this->block_metas);
	if(Block::lightBlock[block_id]){
		//TODO recalc height if y >= oldHeightMapValue
	}/*else if (y == oldHeightMapValue-1) recalc height*/

	//Level::updateLight sky
	//Level::updateLight block
	//LevelChunk lightGaps

	if(block_id){
		 Block::blocks[block_id]->onPlace(this->world, worldX, y, worldZ);
	}

	//this->unsaved = 1
	//change updateMap

	return true;
}

uint8_t RoadRunner::world::Chunk::get_block_meta(int32_t x, int32_t y, int32_t z) {
	return NBARR_GET(COORDS_TO_INDEX(x, y, z), this->block_metas);
}

bool RoadRunner::world::Chunk::set_block_meta(int32_t x, int32_t y, int32_t z, uint8_t block_meta) {
	//this->unsaved = 1
	if(NBARR_GET(COORDS_TO_INDEX(x, y, z), this->block_metas) == block_meta) return false;

	NBARR_SET(COORDS_TO_INDEX(x, y, z), block_meta, this->block_metas);
	return true;
}
