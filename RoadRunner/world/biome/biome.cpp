#include "biome.hpp"
#include <block/block.hpp>

using namespace RoadRunner::world::biome;
using RoadRunner::block::Block;
Biome
	*Biome::rainForest,
	*Biome::swampland,
	*Biome::seasonalForest,
	*Biome::forest,
	*Biome::savanna,		
	*Biome::shrubland,
	*Biome::taiga,
	*Biome::desert,
	*Biome::plains,
	*Biome::iceDesert,
	*Biome::tundra;

Biome* Biome::biomes[4096];

Biome* Biome::getBiome(float blockTemperature, float blockRainfall) {
	int i = (int) (blockTemperature * 63);
	int j = (int) (blockRainfall * 63);
	return Biome::biomes[i + j * 64];
}

Biome* Biome::__getBiome(float temp, float rain){
	rain *= temp;
	
	if(temp < 0.1f) return Biome::tundra;

	if(rain < 0.2f){
		if(temp < 0.5f) return Biome::tundra;
		if(temp < 0.95f) return Biome::savanna;
		return Biome::desert;
	}

	if(rain > 0.5f && temp < 0.7f) return Biome::swampland;
	if(temp < 0.5f) return Biome::taiga;

	if(temp < 0.97f){
		if(rain < 0.35f) return Biome::shrubland;
		return Biome::forest;
	}

	if(rain < 0.45f) return Biome::plains;
	if(rain < 0.9f) return Biome::seasonalForest;
	return Biome::rainForest;
}

void Biome::recalc(){
	for(int i = 0; i < 64; ++i){
		for(int j = 0; j < 64; ++j){
			Biome::biomes[i + j*64] = Biome::__getBiome((float)i / 63.0f, (float)j / 63.0f);
		}
	}

	Biome::desert->topBlock = Biome::desert->fillerBlock = Block::sand->blockID;
	Biome::iceDesert->topBlock = Biome::iceDesert->fillerBlock = Block::sand->blockID;
}

void Biome::initBiomes(){
	Biome::rainForest = new Biome("Rainforest");
	Biome::swampland = new Biome("Swampland");
	Biome::seasonalForest = new Biome("Seasonal Forest");
	Biome::forest = new ForestBiome("Forest");
	Biome::savanna = new FlatBiome("Savanna");
	Biome::shrubland = new FlatBiome("Shrubland");
	Biome::taiga = new TaigaBiome("Taiga"); //Biome::setSnowCovered(taiga);
	Biome::desert = new FlatBiome("Desert");
	Biome::plains = new FlatBiome("Plains");
	Biome::iceDesert = new FlatBiome("");
	Biome::tundra = new FlatBiome("Tundra");

	Biome::recalc();
}


