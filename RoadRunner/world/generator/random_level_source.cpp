#include "level_source.hpp"
#include <stdint.h>
#include <world/world.hpp>
#include <block/block.hpp>
using namespace RoadRunner::world::generator;
using RoadRunner::block::Block;
RandomLevelSource::RandomLevelSource(RoadRunner::world::World* world, int32_t seed){
	this->world = world;
	this->rand = new MTRandom(seed);
	this->upperInterpolationNoise = new PerlinNoise(this->rand, 16);
	this->lowerInterpolationNoise = new PerlinNoise(this->rand, 16);
	this->interpolationNoise = new PerlinNoise(this->rand, 8);
	this->beachNoise = new PerlinNoise(this->rand, 4);
	this->surfaceDepthNoise = new PerlinNoise(this->rand, 4);
	this->biomeNoise = new PerlinNoise(this->rand, 10);
	this->depthNoise = new PerlinNoise(this->rand, 16);
	this->treeNoise = new PerlinNoise(this->rand, 8);
}
RoadRunner::world::Chunk* RandomLevelSource::getChunk(int32_t chunkX, int32_t chunkZ){
	this->rand->setSeed((int)(341872712 * chunkX + 132899541 * chunkZ));
	uint8_t* bArr = new uint8_t[32768];
	this->biomes = this->world->biomeSource->getBiomeBlock(chunkX * 16, chunkZ * 16, 16, 16);

	this->prepareHeights(chunkX, chunkZ, bArr, this->biomes, this->world->biomeSource->temperatureNoises);
	//TODO this.buildSurfaces(chunkX, chunkZ, bArr, this.biomes);
	this->buildSurfaces(chunkX, chunkZ, bArr, this->biomes);
	Chunk* c = new Chunk(chunkX, chunkZ);
	for(int i = 0; i < 32768; ++i){
		c->block_ids[i] = bArr[i]; //TODO better way maybe?
	}

	//TODO c.generateHeightMap();
	return c;
}
void RandomLevelSource::buildSurfaces(int32_t chunkX, int32_t chunkZ, uint8_t* blockIDS, Biome** biomes){
	this->sandNoises = this->beachNoise->getRegion(this->sandNoises, chunkX * 16, chunkZ * 16, 0.0f, 16, 16, 1, 0.03125f, 0.03125f, 1);
	this->gravelNoises = this->beachNoise->getRegion(this->gravelNoises, chunkX * 16, 109.01f, chunkZ * 16, 16, 1, 16, 0.03125f, 1, 0.03125f);
	this->surfaceDepthNoises = this->surfaceDepthNoise->getRegion(this->surfaceDepthNoises, chunkX * 16, chunkZ * 16, 0, 16, 16, 1, 0.0625f, 0.0625f, 0.0625f);
	for (int blockX = 0; blockX < 16; blockX++) {
		for (int blockZ = 0; blockZ < 16; blockZ++) {
			Biome* biome = biomes[blockX + (blockZ * 16)];
			bool z = this->sandNoises[blockX + (blockZ * 16)] + (this->rand->nextFloat() * 0.2f) > 0.0f;
			bool z2 = this->gravelNoises[blockX + (blockZ * 16)] + (this->rand->nextFloat() * 0.2f) > 3.0f;
			int nextFloat = (int) ((this->surfaceDepthNoises[blockX + (blockZ * 16)] / 3.0f) + 3.0f + (this->rand->nextFloat() * 0.25f));
			int i = -1;
			uint8_t b = biome->topBlock;
			uint8_t b2 = biome->fillerBlock;
			for (int blockY = 127; blockY >= 0; --blockY) {
				int index = (blockZ * 16 + blockX) * 128 + blockY;
				if (this->rand->nextInt(5) >= blockY) {
					blockIDS[index] = Block::bedrock->blockID;
				}else {
					uint8_t b3 = blockIDS[index];
					if (b3 == 0) {
						i = -1;
					} else if (b3 == Block::stone->blockID) {
						if (i == -1) {
							if (nextFloat > 0) {
								if (blockY >= 64 - 4 && blockY <= 64 + 1) {
									b = biome->topBlock;
									b2 = biome->fillerBlock;
									if (z2) {
										b = 0;
										b2 = Block::gravel->blockID;
									}
									if (z) {
										b = Block::sand->blockID;
										b2 = Block::sand->blockID;
									}
									}
							} else {
								b = 0;
								b2 = Block::stone->blockID;
							}
							
							if (blockY < 64 && b == 0) {
								b = Block::calmWater->blockID;
							}
							i = nextFloat;
							if (blockY >= 64 - 1) {
								blockIDS[index] = b;
							} else {
								blockIDS[index] = b2;
							}
						} else if (i > 0) {
							i--;
							blockIDS[index] = b2;
							if (i == 0 && b2 == Block::sand->blockID) {
								i = this->rand->nextInt(4);
								b2 = Block::sandStone->blockID;
							}
						}
					}
				}
			}
		}
	}
}
void RandomLevelSource::prepareHeights(int32_t chunkX, int32_t chunkZ, uint8_t* blockIDS, Biome** biomes, float* temperatures){
	this->heights = getHeights(this->heights, chunkX * 4, 0, chunkZ * 4, 5, 17, 5);

	for (int unkX = 0; unkX < 4; unkX++) {
			for (int unkZ = 0; unkZ < 4; unkZ++) {
				for (int unkY = 0; unkY < 16; unkY++) {
					float f = this->heights[((((unkX + 0) * 5) + unkZ + 0) * 17) + unkY + 0];
					float f2 = this->heights[((((unkX + 0) * 5) + unkZ + 1) * 17) + unkY + 0];
					float f3 = this->heights[((((unkX + 1) * 5) + unkZ + 0) * 17) + unkY + 0];
					float f4 = this->heights[((((unkX + 1) * 5) + unkZ + 1) * 17) + unkY + 0];
					float f5 = (this->heights[((((unkX + 0) * 5) + (unkZ + 0)) * 17) + (unkY + 1)] - f) * 0.125f;
					float f6 = (this->heights[((((unkX + 0) * 5) + (unkZ + 1)) * 17) + (unkY + 1)] - f2) * 0.125f;
					float f7 = (this->heights[((((unkX + 1) * 5) + (unkZ + 0)) * 17) + (unkY + 1)] - f3) * 0.125f;
					float f8 = (this->heights[((((unkX + 1) * 5) + (unkZ + 1)) * 17) + (unkY + 1)] - f4) * 0.125f;
					
					for (int unkYY = 0; unkYY < 8; unkYY++) {
						float f9 = f;
						float f10 = f2;
						float f11 = (f3 - f) * 0.25f;
						float f12 = (f4 - f2) * 0.25f;
						for (int unkXX = 0; unkXX < 4; unkXX++) {
							int index = (unkXX + (unkX * 4)) << 11 | unkZ*4 << 7 | unkY*8+unkYY;
							float f13 = f9;
							float f14 = (f10 - f9) * 0.25f;
							for (int unkZZ = 0; unkZZ < 4; unkZZ++) {
								float d15 = temperatures[(((unkX * 4) + unkXX) * 16) + (unkZ * 4) + unkZZ];
								int i3 = 0;
								if ((unkY * 8) + unkYY < 64) {
									if (d15 < 0.5f && (unkY * 8) + unkYY >= 63) {
										i3 = 79;//TODO Block.ice.blockID;
									} else {
										i3 = Block::calmWater->blockID;
									}
								}
								if (f13 > 0.0f) {
									i3 = Block::stone->blockID;
								}
								blockIDS[index] = (uint8_t) i3;
								index += 128;
								f13 += f14;
							}
							f9 += f11;
							f10 += f12;
						}
						f += f5;
						f2 += f6;
						f3 += f7;
						f4 += f8;
					}
				}
			}
		}
}

float* RandomLevelSource::getHeights(float* heights, int chunkX, int chunkY, int chunkZ, int scaleX, int scaleY, int scaleZ){
	
	if(!heights) heights = new float[scaleX*scaleY*scaleZ];
	for(int i = 0; i < scaleX*scaleY*scaleZ; ++i) heights[i] = 0;
	float* rainNoises = this->world->biomeSource->rainfallNoises;
	float* tempNoises = this->world->biomeSource->temperatureNoises;

	this->biomeNoises = this->biomeNoise->getRegion(this->biomeNoises, chunkX, chunkZ, scaleX, scaleZ, 1.121f, 1.121f, 0.5f);
	this->depthNoises = this->depthNoise->getRegion(this->depthNoises, chunkX, chunkZ, scaleX, scaleZ, 200.0f, 200.0f, 0.5f);
	this->interpolationNoises = this->interpolationNoise->getRegion(this->interpolationNoises, chunkX, chunkY, chunkZ, scaleX, scaleY, scaleZ, 684.41f / 80.0f, 684.41f / 160.0f, 684.41f / 80.0f);
	this->upperInterpolationNoises = this->upperInterpolationNoise->getRegion(this->upperInterpolationNoises, chunkX, chunkY, chunkZ, scaleX, scaleY, scaleZ, 684.41f, 684.41f, 684.41f);
	this->lowerInterpolationNoises = this->lowerInterpolationNoise->getRegion(this->lowerInterpolationNoises, chunkX, chunkY, chunkZ, scaleX, scaleY, scaleZ, 684.41f, 684.41f, 684.41f);
	
	int k1 = 0;
	int l1 = 0;
	int i2 = 16 / scaleX;

	for(int x = 0; x < scaleX; x++)
	{
		int xNoiseIndex = x * i2 + i2 / 2;
		for(int z = 0; z < scaleZ; z++)
		{
			int zNoiseIndex = z * i2 + i2 / 2;
			float tempValue = tempNoises[xNoiseIndex * 16 + zNoiseIndex];
			float rainValue = rainNoises[xNoiseIndex * 16 + zNoiseIndex] * tempValue;
			float d4 = 1.0F - rainValue;
			d4 *= d4;
			d4 *= d4;
			d4 = 1.0F - d4;
			float f5 = (this->biomeNoises[l1] + 256.0F) / 512.0F;
			f5 *= d4;
			if(f5 > 1.0F)
			{
				f5 = 1.0F;
			}
			float f6 = this->depthNoises[l1] / 8000.0F;
			if(f6 < 0.0F)
			{
				f6 = f6 * -0.3f;
			}
			f6 = f6 * 3.0F - 2.0F;
			if(f6 < 0.0F)
			{
				f6 /= 2.0f;
				if(f6 < -1.0f) f6 = -1.0F;
				f6 /= 1.4f;
				f6 /= 2.0f;
				f5 = 0.0F;
			} else
			{
				if(f6 > 1.0F)
				{
					f6 = 1.0F;
				}
				f6 /= 8.0f;
			}
			if(f5 < 0.0F) f5 = 0.0F;
			f5 += 0.5F;
			f6 = (f6 * (float)scaleY) / 16.0F;
			float d7 = (float)scaleY / 2.0F + f6 * 4.0F;
			l1++;
			for(int y = 0; y < scaleY; y++)
			{
				float d8 = 0.0F;
				float d9 = (((float)y - d7) * 12.0F) / f5;
				if(d9 < 0.0F) d9 *= 4.0f;
				float d10 = this->upperInterpolationNoises[k1] / 512.0F;
				float d11 = this->lowerInterpolationNoises[k1] / 512.0F;
				float d12 = (this->interpolationNoises[k1] / 10.0f + 1.0F) / 2.0f;
				if(d12 < 0.0F)
				{
					d8 = d10;
				} else
				if(d12 > 1.0F)
				{
					d8 = d11;
				} else
				{
					d8 = d10 + (d11 - d10) * d12;
				}
				d8 -= d9;
				if(y > scaleY - 4)
				{
					float d13 = (float)(y - (scaleY - 4)) / 3.0f;
					d8 = d8 * (1.0F - d13) + -10.0f * d13;
				}
				heights[k1] = (float) d8;
				k1++;
			}
		}

	}

	return heights;
}

RandomLevelSource::~RandomLevelSource(){
	delete this->rand;
	delete this->upperInterpolationNoise;
	delete this->lowerInterpolationNoise;
	delete this->interpolationNoise;
	delete this->beachNoise;
	delete this->surfaceDepthNoise;
	delete this->biomeNoise;
	delete this->depthNoise;
	delete this->treeNoise;

	//TODO remove arrays?
}