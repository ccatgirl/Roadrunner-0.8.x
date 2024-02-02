#pragma once
#include <stdint.h>

namespace RoadRunner{
	namespace utils{
		class MTRandom
		{
			public:
				static uint32_t MAG[2];
				uint32_t mt[624];
				uint32_t index;

				MTRandom(uint32_t seed){
					this->setSeed(seed);
				}

				void setSeed(uint32_t seed){
					this->mt[0] = seed;

					for(this->index = 1; this->index < 624; ++this->index){
						this->mt[this->index] = (0x6c078965 * (this->mt[this->index-1] >> 30 ^ this->mt[this->index - 1]) + this->index);
					}
				}

				uint32_t genRandInt(){
					if(this->index >= 624 || this->index < 0){
						uint32_t kk;
						if(this->index >= 625 || this->index < 0) this->setSeed(4357);
						for(kk = 0; kk < 227; ++kk){
							uint32_t y = (this->mt[kk] & 0x80000000) | (this->mt[kk + 1] & 0x7fffffff);
							this->mt[kk] = this->mt[kk+397] ^ (y >> 1) ^ MTRandom::MAG[y & 0x1];
						}
			
						for(;kk < 623; ++kk){
							uint32_t y = (this->mt[kk] & 0x80000000) | (this->mt[kk + 1] & 0x7fffffff);
							this->mt[kk] = this->mt[kk-227] ^ (y >> 1) ^ MTRandom::MAG[y & 0x1];
						}
			
						uint32_t y = (this->mt[623] & 0x80000000) | (this->mt[0] & 0x7fffffff);
						this->mt[623] = this->mt[396] ^ (y >> 1) ^ MTRandom::MAG[y & 0x1];
						this->index = 0;
					}
		
					uint32_t y = this->mt[this->index++];
					y ^= (y >> 11);
					y ^= (y << 7) & 0x9d2c5680;
					y ^= (y << 15) & 0xefc60000;
					y ^= (y >> 18);
					return y;
				}

				uint32_t nextInt(){
					return this->genRandInt() >> 1;
				}
				
				uint32_t nextInt(uint32_t bound){
					return this->genRandInt() % bound;
				}

				float nextFloat(){
					return (float)this->genRandInt() / 0xffffffff;
				}
		};
	}
}