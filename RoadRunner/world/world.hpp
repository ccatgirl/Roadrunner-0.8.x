#pragma once

#include "chunk.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <world/biome_source.hpp>

namespace RoadRunner {
	namespace world {
		
		class World{
			public:
				Chunk* chunks[256];
				unsigned int seed = 0; //TODO use long?
				RoadRunner::world::BiomeSource* biomeSource;
				long time = 0;
				long prevTimeSent = 0;
				std::string name = "world";

				World(unsigned int seed);
				~World(){
					for(int i = 0; i < 256; ++i){
						if(chunks[i]) delete chunks[i];
					}
					delete this->biomeSource;
				}

				Chunk *get_chunk(int32_t x, int32_t z);
				uint8_t get_block_id(int32_t x, int32_t y, int32_t z);
				uint8_t get_block_meta(int32_t x, int32_t y, int32_t z);
				void set_block(int32_t x, int32_t y, int32_t z, uint8_t id, uint8_t meta, uint8_t flags);
				void tick();
				long getTime(){ //TODO maybe make a LevelData?
					return this->time;
				}
				long setTime(long newTime){
					int v3;

					v3 = newTime % 153600;
					this->time = v3;
					if(this->prevTimeSent <= v3) return v3 - this->prevTimeSent;

					return 153600 - this->prevTimeSent + v3;
				}

				bool isSolidBlockingTile(int x, int y, int z);
				void neighborChanged(int x , int y, int z, int neighborX, int neighborY, int neighborZ, int oldid);
				void updateNeighborsAt(int x, int y, int z, int oldid);
				void tileUpdated(int x, int y, int z, int oldid);
				void syncTime();
				void saveWorld();
				bool loadWorld();
				bool mayPlace(int blockID, int x, int y, int z, bool wat, uint8_t side);
		};
	}
}
