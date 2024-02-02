#pragma once
#include <stdint.h>
#include <utils/mtrandom.hpp>
#include <world/world.hpp>
#include <world/noise/perlin_noise.hpp>
#include <world/chunk.hpp>
#include <world/biome/biome.hpp>

using RoadRunner::world::noise::PerlinNoise;
using RoadRunner::world::biome::Biome;
namespace RoadRunner{
	namespace world{
		namespace generator{
			class LevelSource{
				public:
					virtual RoadRunner::world::Chunk* getChunk(int32_t chunkX, int32_t chunkZ) = 0;
					virtual void prepareHeights(int32_t chunkX, int32_t chunkZ, uint8_t* blockIDS, Biome** biomes, float* temperatures) = 0;
					virtual float* getHeights(float* heights, int chunkX, int chunkY, int chunkZ, int scaleX, int scaleY, int scaleZ) = 0;
					virtual void buildSurfaces(int32_t chunkX, int32_t chunkZ, uint8_t* blockIDS, Biome** biomes) = 0;
					virtual void postProcess(int32_t chunkX, int32_t chunkZ) = 0;
			};

			class RandomLevelSource{
				public:
					RoadRunner::world::World* world;
					RoadRunner::utils::MTRandom* rand;
					
					PerlinNoise* upperInterpolationNoise;
					PerlinNoise* lowerInterpolationNoise;
					PerlinNoise* interpolationNoise;
					PerlinNoise* beachNoise;
					PerlinNoise* surfaceDepthNoise;
					PerlinNoise* biomeNoise;
					PerlinNoise* depthNoise;
					PerlinNoise* treeNoise;

					float* biomeNoises = 0;
					float* depthNoises = 0;
					float* interpolationNoises = 0;
					float* upperInterpolationNoises = 0;
					float* lowerInterpolationNoises = 0;
					Biome** biomes = 0;
					float* heights = 0;
					float* sandNoises = 0;
					float* gravelNoises = 0;
					float* surfaceDepthNoises = 0;

					RandomLevelSource(RoadRunner::world::World* world, int32_t seed);
					RoadRunner::world::Chunk* getChunk(int32_t chunkX, int32_t chunkZ);
					void prepareHeights(int32_t chunkX, int32_t chunkZ, uint8_t* blockIDS, Biome** biomes, float* temperatures);
					float* getHeights(float* heights, int chunkX, int chunkY, int chunkZ, int scaleX, int scaleY, int scaleZ);
					void buildSurfaces(int32_t chunkX, int32_t chunkZ, uint8_t* blockIDS, Biome** biomes);
					void postProcess(int32_t chunkX, int32_t chunkZ);
					~RandomLevelSource();
			};
		}
	}
}