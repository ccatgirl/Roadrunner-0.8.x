#include "server.hpp"
#include "world/world.hpp"
#include "world/chunk.hpp"
#include <stdint.h>
#include <network/packets/set_time_packet.hpp>

RoadRunner::world::World::World(unsigned int seed){
	this->seed = seed;

	this->biomeSource = new RoadRunner::world::BiomeSource(this);

	for(int32_t i = 0; i < 256; ++i){
		//this->chunks[i] = new RoadRunner::world::Chunk((i & 0xf0) >> 4, i & 0xf);
		this->chunks[i] = 0;
	}
}
void RoadRunner::world::World::syncTime(){
	RoadRunner::network::packets::SetTimePacket pk;
	pk.time = this->time;
	pk.started = 1;

	//TODO some broadcast packet method?
	RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(pk.packet_id);
    pk.serialize_body(&send_stream);

    std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = Server::INSTANCE->players.begin();
    while (it != Server::INSTANCE->players.end()) {
        Server::INSTANCE->peer->Send(&send_stream, LOW_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }

}
void RoadRunner::world::World::tick(){
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
	
	//entities next probably?
}
uint8_t RoadRunner::world::World::get_block_id(int32_t x, int32_t y, int32_t z) {
	int chunkX = x / 16;
	int chunkZ = z / 16;

    RoadRunner::world::Chunk *chunk = this->get_chunk(chunkX, chunkZ);
	return chunk ? chunk->get_block_id(x & 0xf, y, z & 0xf) : 0;
}

RoadRunner::world::Chunk* RoadRunner::world::World::get_chunk(int32_t x, int32_t z) {
    int index = x << 4 | z;
    if (index > 255 || index < 0) return &RoadRunner::world::BlankChunk::blankChunk;
    return this->chunks[index];
}

uint8_t RoadRunner::world::World::get_block_meta(int32_t x, int32_t y, int32_t z) {
	int chunkX = x / 16;
	int chunkZ = z / 16;

    RoadRunner::world::Chunk *chunk = this->get_chunk(chunkX, chunkZ);
	return chunk ? chunk->get_block_meta(x & 0xf, y, z & 0xf) : 0;
}

void RoadRunner::world::World::set_block(int32_t x, int32_t y, int32_t z, uint8_t id, uint8_t meta, uint8_t flags) {
	int chunkX = x / 16;
	int chunkZ = z / 16;
	int index = chunkX << 4 | chunkZ;
    RoadRunner::world::Chunk *chunk = this->get_chunk(chunkX, chunkZ);
	if(chunk){
		chunk->set_block_id(x & 0xf, y, z & 0xf, id);
		chunk->set_block_meta(x & 0xf, y, z & 0xf, meta);

		if (flags & 0x1)
            ; // TODO update
        if (flags & 0x2) {
            RoadRunner::Server::INSTANCE->send_block_data(x, y, z, id, meta);
        }

	}else{
		//TODO should never happen, but maybe try to create a new chunk?
	}
}
