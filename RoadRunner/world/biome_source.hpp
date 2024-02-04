#pragma once
#include <stdint.h>
#include <world/biome/biome.hpp>
#include <world/noise/perlin_noise.hpp>
#include <utils/mtrandom.hpp>

using RoadRunner::utils::MTRandom;
using RoadRunner::world::noise::PerlinNoise;
using RoadRunner::world::biome::Biome;

namespace RoadRunner{
	namespace world{

		class World;

		class BiomeSource{
		public:
			PerlinNoise* temperatureNoise;
			PerlinNoise* rainfallNoise;
			PerlinNoise* detailNoise;

			float* temperatureNoises = 0;
			float* rainfallNoises = 0;
			float* detailNoises = 0;

			BiomeSource(RoadRunner::world::World* world);

			Biome* getBiome(int32_t x, int32_t z){
				Biome** arr = getBiomeBlock(x, z, 1, 1);
				Biome* ret = arr[0];
				delete[] arr;
				return ret;
			}

			//TODO public float[] getTemperatureBlock(int x, int z, int xSize, int zSize) { for postProcess
			Biome** getBiomeBlock(int32_t x, int32_t z, int32_t xSize, int32_t zSize){
				this->temperatureNoises = this->temperatureNoise->getRegion(this->temperatureNoises, x, z, xSize, zSize, 0.025f, 0.025f, 0.25f);
				this->rainfallNoises = this->rainfallNoise->getRegion(this->rainfallNoises, x, z, xSize, zSize, 0.05f, 0.05f, 0.3333f);
				this->detailNoises = this->detailNoise->getRegion(this->detailNoises, x, z, xSize, zSize, 0.25f, 0.25f, 0.588f);

				Biome** localBiomeArray = new Biome*[xSize * zSize];
				int index = 0;
				for(int blockX = 0; blockX < xSize; ++blockX) {
					for(int blockZ = 0; blockZ < zSize; ++blockZ) {
						float v14 = (this->detailNoises[index] * 1.1f) + 0.5f;
						float v12 = (((this->temperatureNoises[index] * 0.15f) + 0.7f) * (1.0f - 0.01f)) + (v14 * 0.01f);
						float blockRainfall = (((this->rainfallNoises[index] * 0.15f) + 0.5f) * (1.0f - 0.002f)) + ((v14 * 0.002f));
						float blockTemperature = 1.0f - ((1.0f - v12) * (1.0f - v12));
				
						if(blockTemperature < 0) {
							blockTemperature = 0;
						}else if(blockTemperature > 1) {
							blockTemperature = 1;
						}
				
						if(blockRainfall < 0) {
							blockRainfall = 0;
						}else if(blockRainfall > 1) {
							blockRainfall = 1;
						}
				
				
						this->temperatureNoises[index] = blockTemperature;
						this->rainfallNoises[index] = blockRainfall;
				
						localBiomeArray[index] = Biome::getBiome(blockTemperature, blockRainfall);
						++index;
					
					}
				}

				return localBiomeArray;
			}

			~BiomeSource(){
				
				delete this->temperatureNoise;
				delete this->rainfallNoise;
				delete this->detailNoise;

				//TODO remove arrays?
				if(this->temperatureNoises) delete[] this->temperatureNoises;
				if(this->rainfallNoises) delete[] this->rainfallNoises;
				if(this->detailNoises) delete[] this->detailNoises;
			}
		};	
	}
}