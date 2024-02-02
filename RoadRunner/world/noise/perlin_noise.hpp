#pragma once
#include <stdint.h>
#include "improved_noise.hpp"
#include <utils/mtrandom.hpp>

namespace RoadRunner{
	namespace world{
		namespace noise{
			class PerlinNoise{
				public:
					int32_t octaves;
					ImprovedNoise** noises;
					PerlinNoise(MTRandom* random, int32_t octaves){
						this->noises = new ImprovedNoise*[octaves];
						this->octaves = octaves;
						for(int i = 0; i < this->octaves; ++i){
							this->noises[i] = new ImprovedNoise(random);
						}
					}

					float getValue(float x, float y){
						float noise = 0;
						float scale = 1;

						for(int i = 0; i < this->octaves; ++i){
							noise += this->noises[i]->getValue(x*scale, y*scale) / scale;
							scale /= 2;
						}
						return noise;
					}

					float* getRegion(float* noiseArray, float x, float y, float z, int width, int height, int depth, float scaleX, float scaleY, float scaleZ){
						if(!noiseArray){
							noiseArray = new float[width*height*depth];
						}

						for(int i = 0; i < width*height*depth; ++i) noiseArray[i] = 0;

						float scale = 1;
						for(int i = 0; i < this->octaves; ++i){
							this->noises[i]->add(noiseArray, x, y, z, width, height, depth, scaleX * scale, scaleY * scale, scaleZ * scale, scale);
							scale /= 2;
						}
						return noiseArray;
					}

					float* getRegion(float* ad, int i, int j, int k, int l, float d, float d1, float d2){
						return getRegion(ad, i, 10, j, k, 1, l, d, 1, d1);
					}

					~PerlinNoise(){
						for(int i = 0; i < this->octaves; ++i){
							delete noises[i];
						}

						delete noises;
					}
			};
		}
	}
}