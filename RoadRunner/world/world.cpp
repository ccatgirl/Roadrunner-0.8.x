#include "server.hpp"
#include "world/world.hpp"
#include "world/chunk.hpp"
#include <stdint.h>
#include <network/packets/set_time_packet.hpp>

using namespace RoadRunner::world;

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

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fwrite(c->block_ids + index, 1, 128, chunks); //id
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fwrite(c->block_metas + (index >> 1), 1, 64, chunks); //meta
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fwrite(c->skylight + (index >> 1), 1, 64, chunks); //skylight
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fwrite(c->blocklight + (index >> 1), 1, 64, chunks); //blocklight
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					fwrite("\xff", 1, 1, chunks); //update map
				}
			}
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
	//TODO level.dat ??

	
	int header;
	//TODO loctable
	for(int chunkX = 0; chunkX < 16; ++chunkX){
		for(int chunkZ = 0; chunkZ < 16; ++chunkZ){
			fseek(chunks, 4096+(chunkX*21*4096)+(chunkZ*21*16*4096), SEEK_SET);
			Chunk* c = this->chunks[chunkX<<4|chunkZ] = new Chunk(chunkX, chunkZ);

			
			fread(&header, 4, 1, chunks);

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fread(c->block_ids + index, 1, 128, chunks);
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fread(c->block_metas + (index >> 1), 1, 64, chunks);
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fread(c->skylight + (index >> 1), 1, 64, chunks);
				}
			}

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){
					int index = x << 11 | z << 7;
					fread(c->blocklight + (index >> 1), 1, 64, chunks);
				}
			}
		}
	}

	return true;
}

void RoadRunner::world::World::set_block(int32_t x, int32_t y, int32_t z, uint8_t id, uint8_t meta, uint8_t flags) { //TODO return success/failure
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
