#pragma once

#include "chunk.hpp"
#include <stdint.h>
#include <stdlib.h>

namespace RoadRunner {
	namespace world {
		
		class World{
			public:
				Chunk* chunks[256];
				unsigned int seed = 0; //TODO use long?
				
				World(unsigned int seed);
				~World(){
					for(int i = 0; i < 256; ++i){
						if(chunks[i]) free(chunks[i]);
					}
				}

                Chunk *get_chunk(int32_t x, int32_t z);
				uint8_t get_block_id(int32_t x, int32_t y, int32_t z);
				uint8_t get_block_meta(int32_t x, int32_t y, int32_t z);
				void set_block(int32_t x, int32_t y, int32_t z, uint8_t id, uint8_t meta, uint8_t flags);
		};
	}
}
