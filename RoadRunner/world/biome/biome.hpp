#pragma once
#include <stdint.h>

namespace RoadRunner{
	namespace world{
		namespace biome{
			class Biome{
				public:
					static Biome
						*rainForest,
						*swampland,
						*seasonalForest,
						*forest,
						*savanna,
						*shrubland,
						*taiga,
						*desert,
						*plains,
						*iceDesert,
						*tundra;
					static Biome* biomes[4096];

					static Biome* __getBiome(float temp, float rain);
					static void recalc();
					static void initBiomes();
					static Biome* getBiome(float blockTemperature, float blockRainfall);
					//TODO Feature* getTreeFeature(MTRandom* random){
					// random->nextInt();
					// return new TreeFeature();
					//}
					char* name;
					uint8_t topBlock = 2;
					uint8_t fillerBlock = 3;
					Biome(char* name){
						this->name = name;
					};
			};

			class ForestBiome : public Biome{
			public:
				ForestBiome(char* name) : Biome(name){}
			};

			class TaigaBiome : public Biome{
			public:
				TaigaBiome(char* name) : Biome(name){}
			};

			class FlatBiome : public Biome{
			public:
				FlatBiome(char* name) : Biome(name){}
			};
		}
	}
}