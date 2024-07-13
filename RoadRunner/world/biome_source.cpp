#include "world.hpp"
#include "biome_source.hpp"



RoadRunner::world::BiomeSource::BiomeSource(RoadRunner::world::World* world){
	MTRandom rand1(world->seed * 9871);
	MTRandom rand2(world->seed * 39811);
	MTRandom rand3(world->seed * 543321);

	this->temperatureNoise = new PerlinNoise(&rand1, 4);
	this->rainfallNoise = new PerlinNoise(&rand2, 4);
	this->detailNoise = new PerlinNoise(&rand3, 2);
}
