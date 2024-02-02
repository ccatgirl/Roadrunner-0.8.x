#include "world.hpp"
#include "biome_source.hpp"



RoadRunner::world::BiomeSource::BiomeSource(RoadRunner::world::World* world){
	this->temperatureNoise = new PerlinNoise(new MTRandom(world->seed * 9871), 4);
	this->rainfallNoise = new PerlinNoise(new MTRandom(world->seed * 39811), 4);
	this->detailNoise = new PerlinNoise(new MTRandom(world->seed * 543321), 2);
}