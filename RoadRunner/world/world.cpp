#include "server.hpp"
#include "world/world.hpp"
#include "world/chunk.hpp"
#include <stdint.h>
#include <network/packets/set_time_packet.hpp>
#include <nbt/tag_utils.hpp>
#include <nbt/tag/compound.hpp>
#include <nbt/tag/string.hpp>
#include <nbt/tag/int.hpp>
#include <nbt/tag/long.hpp>
#include <nbt/tag/byte.hpp>
#include <config.hpp>
#include <stdio.h>
#include <block/block.hpp>

using namespace RoadRunner::world;
using namespace RoadRunner::nbt;
using namespace RoadRunner::block;

World::World(unsigned int seed){
	this->seed = seed;

	this->biomeSource = new BiomeSource(this);

	for(int32_t i = 0; i < 256; ++i){
		//this->chunks[i] = new RoadRunner::world::Chunk((i & 0xf0) >> 4, i & 0xf);
		this->chunks[i] = 0;
	}
}

void World::syncTime(){
	RoadRunner::network::packets::SetTimePacket pk;
	pk.time = this->time;
	pk.started = 1;

	//TODO some broadcast packet method?
	RakNet::BitStream send_stream;
	send_stream.Write<uint8_t>(pk.packet_id);
	pk.serialize_body(&send_stream);

	auto it = Server::INSTANCE->players.begin();
	while (it != Server::INSTANCE->players.end()) {
		Server::INSTANCE->peer->Send(&send_stream, LOW_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
		++it;
	}

}
bool World::mayPlace(int blockID, int x, int y, int z, bool wat, uint8_t side){
	int idAtXYZ = this->get_block_id(x, y, z);
	Block* block = Block::blocks[blockID];
	Block* blockXYZ = Block::blocks[idAtXYZ];

	//TODO AABB checks, BLock::replaceable
	/*
	v14 = blocc->vtable->_ZN4Tile7getAABBEP5Leveliii(blocc, this, x, y, z);
	if ( (a6 || !v14 || Level::isUnobstructed(this, v14)) && (!blockXYZ || blockXYZ->base.replaceable) && blockID > 0 )
	{
		return blocc->vtable->_ZN4Tile8mayPlaceEP5Leveliiih(blocc, this, x, y, z, side);
	}
	else
	{
		return 0;
	}*/

	if((blockXYZ == 0 || /*block->replaceable*/ false) && blockID > 0){
		return block->mayPlace(this, x, y, z, side);
	}
	return 0;
}
bool World::isSolidBlockingTile(int x, int y, int z){
	Block* block = Block::blocks[this->get_block_id(x, y, z)];

	if(block && block->material->isSolidBlocking()){
		return block->isCubeShaped();
	}
	return 0;
}

void World::tick(){
	//Handle MobSpawner

	//ChunkSource + 24
	//Level::updateSkyDarken()
	
	//some boolean for time(maybe the night lock after nether reactor usage)
	//else
	{
		int timeDiff = this->setTime(this->time + 1);
		if(timeDiff > 255){
			this->syncTime();
			this->prevTimeSent = this->time;
		}

	}

	//tickPendingTiles
	//tickTiles
	
	//send entity data
}
uint8_t World::get_block_id(int32_t x, int32_t y, int32_t z) {
	int chunkX = x / 16;
	int chunkZ = z / 16;

	RoadRunner::world::Chunk *chunk = this->get_chunk(chunkX, chunkZ);
	return chunk ? chunk->get_block_id(x & 0xf, y, z & 0xf) : 0;
}

Chunk* World::get_chunk(int32_t x, int32_t z) {
	int index = x << 4 | z;
	if (index > 255 || index < 0) return RoadRunner::world::BlankChunk::blankChunk;
	return this->chunks[index];
}

uint8_t World::get_block_meta(int32_t x, int32_t y, int32_t z) {
	int chunkX = x / 16;
	int chunkZ = z / 16;

	Chunk *chunk = this->get_chunk(chunkX, chunkZ);
	return chunk ? chunk->get_block_meta(x & 0xf, y, z & 0xf) : 0;
}
#include <utils/multisystem.h>

void World::saveWorld(){

	createDirectory("worlds/");
	createDirectory(("worlds/"+this->name+"/").c_str());

	//TODO level.dat
	printf("Saving level.dat...\n");
	FILE* level = fopen(("worlds/"+this->name+"/level.dat").c_str(), "wb");
	if(level){
		tag::Compound tag;
		tag.name = "";
		tag.unsafe = true;

		tag::Int gameType;
		gameType.name = "GameType";
		gameType.value = IS_CREATIVE != 0;
		tag.value.push_back(&gameType);

		tag::Long lastPlayed;
		lastPlayed.name = "LastPlayed";
		lastPlayed.value = 0; //TODO
		tag.value.push_back(&lastPlayed);

		tag::String levelName;
		levelName.name = "LevelName";
		levelName.value = this->name;
		tag.value.push_back(&levelName);

		tag::Int platform;
		platform.name = "Platform";
		platform.value = 2; //static
		tag.value.push_back(&platform);

		//player data is also saved here in vanilla, but it will be moved

		tag::Long randomSeed;
		randomSeed.name = "RandomSeed";
		randomSeed.value = this->seed;
		tag.value.push_back(&randomSeed);

		tag::Long sizeOnDisk;
		sizeOnDisk.name = "SizeOnDisk";
		sizeOnDisk.value = 0; //TODO
		tag.value.push_back(&sizeOnDisk);

		tag::Int spawnX;
		spawnX.name = "SpawnX";
		spawnX.value = 127; //TODO;
		tag.value.push_back(&spawnX);

		tag::Int spawnY;
		spawnY.name = "SpawnY";
		spawnY.value = 127; //TODO;
		tag.value.push_back(&spawnY);

		tag::Int spawnZ;
		spawnZ.name = "SpawnZ";
		spawnZ.value = 127; //TODO;
		tag.value.push_back(&spawnZ);

		tag::Int storageVersion;
		storageVersion.name = "StorageVersion";
		storageVersion.value = 3;
		tag.value.push_back(&storageVersion);

		tag::Long time;
		time.name = "Time";
		time.value = this->time;
		tag.value.push_back(&time);

		tag::Long dayCycleStopTime;
		dayCycleStopTime.name = "dayCycleStopTime";
		dayCycleStopTime.value = -1; //TODO
		tag.value.push_back(&dayCycleStopTime);

		tag::Byte spawnMobs;
		spawnMobs.name = "SpawnMobs";
		spawnMobs.value = 1; //TODO probably 0 in creative
		tag.value.push_back(&spawnMobs);

		//print_tag(&tag);

		RakNet::BitStream stream(4); //TODO better static amount of bytes
		
		tag::Compound root;
		root.value.push_back(&tag);
		root.unsafe = true;

		root.write(&stream);
		unsigned char* data = stream.GetData();
		int length = stream.GetNumberOfBytesUsed();

		fwrite("\3\0\0\0", 4, 1, level); //type?
		fwrite(&length, 4, 1, level); //size of buffer
		fwrite(data, 1, length, level);
		fclose(level);
	}else{
		printf("NullPointerException\n");
	}


	printf("Saving chunks.dat...\n");
	FILE* chunks = fopen(("worlds/"+this->name+"/chunks.dat").c_str(), "wb");
	
	//Write locTable, TODO figure out how it works
	for(int x = 0; x < 32; ++x){
		for(int z = 0; z < 32; ++z){
			fwrite("\0\0\0\0", 4, 1, chunks);
		}
	}

	int chunkHeader = 0x04410120;

	//Write chunks
	for(int chunkX = 0; chunkX < 16; ++chunkX){
		for(int chunkZ = 0; chunkZ < 16; ++chunkZ){
			fseek(chunks, 4096+(chunkX*21*4096)+(chunkZ*21*16*4096), SEEK_SET);
			Chunk* c = this->get_chunk(chunkX, chunkZ);

			fwrite(&chunkHeader, 4, 1, chunks);
			fwrite(c->block_ids, 1, 128*16*16, chunks); //id
			fwrite(c->block_metas, 1, 64*16*16, chunks); //meta
			fwrite(c->skylight, 1, 64*16*16, chunks); //skylight
			fwrite(c->blocklight, 1, 64*16*16, chunks); //blocklight
		}
	}

	fclose(chunks);

}
bool World::loadWorld(){
	if(!hasDirectory(("worlds/"+this->name+"/").c_str())){
		return false;
	}
	FILE* chunks = fopen(("worlds/"+this->name+"/chunks.dat").c_str(), "rb");
	if(!chunks) return false;
	FILE* level = fopen(("worlds/"+this->name+"/level.dat").c_str(), "rb");
	if(!level) return false;

	int type, rest;
	fread(&type, 4, 1, level);
	if(type != 3){
		printf("Level.dat type is not 3, got %d\n", type);
	}
	fread(&rest, 4, 1, level);
	unsigned char* buf = (unsigned char*) malloc(rest);
	fread(buf, 1, rest, level);

	RakNet::BitStream stream(buf, rest, false);
	tag::Compound* root = (tag::Compound*) create_tag(RoadRunner::nbt::TagIdentifiers::COMPOUND);
	root->read(&stream);
	//print_tag(root);
	tag::Compound* real = (tag::Compound*) root->value[0];

	tag::Long* time = (tag::Long*) real->find("Time");
	if(time) this->time = time->value;

	tag::Long* seed = (tag::Long*) real->find("RandomSeed");
	if(seed) this->seed = seed->value;

	delete root;
	free(buf);



	int header;
	//TODO loctable
	for(int chunkX = 0; chunkX < 16; ++chunkX){
		for(int chunkZ = 0; chunkZ < 16; ++chunkZ){
			fseek(chunks, 4096+(chunkX*21*4096)+(chunkZ*21*16*4096), SEEK_SET);
			Chunk* c = this->chunks[chunkX<<4|chunkZ] = new Chunk(chunkX, chunkZ);

			
			fread(&header, 4, 1, chunks);
			fread(c->block_ids, 1, 128*16*16, chunks);
			fread(c->block_metas, 1, 64*16*16, chunks);
			fread(c->skylight, 1, 64*16*16, chunks);
			fread(c->blocklight, 1, 64*16*16, chunks);

		}
	}

	return true;
}

void World::neighborChanged(int x , int y, int z, int neighborX, int neighborY, int neighborZ, int oldid){
	Block* block = Block::blocks[this->get_block_id(x, y, z)];

	if(block){
		block->neighborChanged(this, x, y, z, neighborX, neighborY, neighborZ, oldid);
	}
}
void World::updateNeighborsAt(int x, int y, int z, int oldid){
	this->neighborChanged(x - 1, y, z, x, y, z, oldid);
	this->neighborChanged(x + 1, y, z, x, y, z, oldid);
	this->neighborChanged(x, y - 1, z, x, y, z, oldid);
	this->neighborChanged(x, y + 1, z, x, y, z, oldid);
	this->neighborChanged(x, y, z - 1, x, y, z, oldid);
	this->neighborChanged(x, y, z + 1, x, y, z, oldid);

}

void World::tileUpdated(int x, int y, int z, int oldid){
	this->updateNeighborsAt(x, y, z, oldid);
}

void RoadRunner::world::World::set_block(int32_t x, int32_t y, int32_t z, uint8_t id, uint8_t meta, uint8_t flags) { //TODO return success/failure
	int chunkX = x / 16;
	int chunkZ = z / 16;
	int index = chunkX << 4 | chunkZ;
	int oldid = 0;

	RoadRunner::world::Chunk *chunk = this->get_chunk(chunkX, chunkZ);
	if(chunk){

		if(flags & 1) oldid = chunk->get_block_id(x & 0xf, y, z & 0xf);

		chunk->set_block_id(x & 0xf, y, z & 0xf, id);
		chunk->set_block_meta(x & 0xf, y, z & 0xf, meta);

		if (flags & 0x1){
			this->tileUpdated(x, y, z, oldid);
		}
		if (flags & 0x2) {
			RoadRunner::Server::INSTANCE->send_block_data(x, y, z, id, meta);
		}

	}else{
		//TODO should never happen, but maybe try to create a new chunk?
	}
}
