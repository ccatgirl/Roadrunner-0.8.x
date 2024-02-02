#pragma once
#include <stdint.h>
#include <utils/mtrandom.hpp>

#define FADE(x) (x*x*x*(x*(x*6.0f-15.0f) + 10.0f))

using RoadRunner::utils::MTRandom;
namespace RoadRunner{
	namespace world{
		namespace noise{
			class ImprovedNoise{
				public:
					static float grad(int hash, float x, float y, float z){
						int h = hash & 0xf;
						float u = h < 8 ? x : y;
						float v = h < 4 ? y : (h == 12 || h == 14) ? x : z;
						return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
					}

					static float grad2(int i, float d, float d1){
						int j = i & 0xf;

						float d2 = (1 - ((j & 8) >> 3)) * d;
						float d3 = j >= 4 ? (j != 12 && j != 14 ? d1 : d) : 0;
						return ((j & 1) ? -d2 : d2) + ((j & 2) ? -d3 : d3);
					}

					static float lerp(float t, float a, float b){
						return a + t * (b - a);
					}

					int permutations[512];
					float xCoord, yCoord, zCoord;
					
					ImprovedNoise(MTRandom* random){
						this->xCoord = random->nextFloat() * 256;
						this->yCoord = random->nextFloat() * 256;
						this->zCoord = random->nextFloat() * 256;
					
						for(int i = 0; i < 256; ++i){
							this->permutations[i] = i;
						}

						for(int i = 0; i < 256; ++i){
							int k = random->nextInt(256 - i) + i;
							int prev = this->permutations[i];
							this->permutations[i] = this->permutations[k];
							this->permutations[k] = prev;
							this->permutations[i + 256] = this->permutations[i];
						}
					}

					~ImprovedNoise(){
						//TODO delete this->permutations;
					}

					float getValue(float x, float y){
						return this->getValue(x, y, 0);
					}

					float getValue(float x, float y, float z){
						float xPos = x + this->xCoord;
						float yPos = y + this->yCoord;
						float zPos = z + this->zCoord;
						int xFloor = (int) xPos;
						if(xPos < xFloor) --xFloor;
						int yFloor = (int) yPos;
						if(yPos < yFloor) --yFloor;
						int zFloor = (int) zPos;
						if(zPos < zFloor) --zFloor;

						int x255 = xFloor & 0xff;
						int y255 = yFloor & 0xff;
						int z255 = zFloor & 0xff;

						xPos -= xFloor;
						yPos -= yFloor;
						zPos -= zFloor;

						float xFade = FADE(xPos);
						float yFade = FADE(yPos);
						float zFade = FADE(zPos);

						int k1 = this->permutations[x255] + y255;
						int l1 = this->permutations[k1] + z255;
						int i2 = this->permutations[k1 + 1] + z255;
					
						int j2 = this->permutations[x255 + 1] + y255;
						int k2 = this->permutations[j2] + z255;
						int l2 = this->permutations[j2 + 1] + z255;

						return ImprovedNoise::lerp(zFade,
							ImprovedNoise::lerp(yFade,
								ImprovedNoise::lerp(xFade, ImprovedNoise::grad(this->permutations[l1], xPos, yPos, zPos), ImprovedNoise::grad(this->permutations[k2], xPos - 1, yPos, zPos)),
								ImprovedNoise::lerp(xFade, ImprovedNoise::grad(this->permutations[i2], xPos, yPos - 1, zPos), ImprovedNoise::grad(this->permutations[l2], xPos - 1, yPos - 1, zPos))
							),
							ImprovedNoise::lerp(yFade,
								ImprovedNoise::lerp(xFade, ImprovedNoise::grad(this->permutations[l1 + 1], xPos, yPos, zPos - 1), ImprovedNoise::grad(this->permutations[k2 + 1], xPos - 1, yPos, zPos - 1)),
								ImprovedNoise::lerp(xFade, ImprovedNoise::grad(this->permutations[i2 + 1], xPos, yPos - 1, zPos - 1), ImprovedNoise::grad(this->permutations[l2 + 1], xPos - 1, yPos - 1, zPos - 1))
							)
						);
					}

					void add(float* noises, float x, float y, float z, int width, int height, int depth, float scaleX, float scaleY, float scaleZ, float scale)
					{
						if(height == 1)
						{
							int j3 = 0;
							float d12 = 1 / scale;
							for(int w = 0; w < width; ++w)
							{
								float xFull = (x + (float)w) * scaleX + xCoord;
								int floorXFull = (int)xFull;
								if(xFull < floorXFull) --floorXFull;
								int k4 = floorXFull & 0xff;
								xFull -= floorXFull;
								float xFullFade = FADE(xFull);
								for(int d = 0; d < depth; ++d)
								{
									float zFull = (z + (float)d) * scaleZ + zCoord;
									int zFloor = (int)zFull;
									if(zFull < zFloor) zFloor--;

									int l5 = zFloor & 0xff;
									zFull -= zFloor;
									float zFullFade = FADE(zFull);
									int l = this->permutations[k4] + 0;
									int j1 = this->permutations[l] + l5;
									int k1 = this->permutations[k4 + 1] + 0;
									int l1 = this->permutations[k1] + l5;
									float d9 = lerp(xFullFade, grad2(this->permutations[j1], xFull, zFull), grad(this->permutations[l1], xFull - 1, 0, zFull));
									float d11 = lerp(xFullFade, grad(this->permutations[j1 + 1], xFull, 0, zFull - 1), grad(this->permutations[l1 + 1], xFull - 1, 0, zFull - 1));
									float d23 = lerp(zFullFade, d9, d11);
									noises[j3] += d23 * d12;
									++j3;
								}

							}
							return;
						}
						int i1 = 0;
						float d7 = 1 / scale;
						int i2 = -1;
						float d13 = 0;
						float d15 = 0;
						float d16 = 0;
						float d18 = 0;
						for(int i5 = 0; i5 < width; i5++)
						{
							float d20 = (x + (float)i5) * scaleX + xCoord;
							int k5 = (int) d20;
							if(d20 < k5) --k5;
							int i6 = k5 & 0xff;
							d20 -= k5;
							float d22 = FADE(d20);
							for(int j6 = 0; j6 < depth; j6++)
							{
								float d24 = (z + (float)j6) * scaleZ + zCoord;
								int k6 = (int)d24;
								if(d24 < k6) --k6;
								int l6 = k6 & 0xff;
								d24 -= k6;
								float d25 = FADE(d24);
								for(int i7 = 0; i7 < height; i7++)
								{
									float d26 = (y + (float)i7) * scaleY + yCoord;
									int j7 = (int)d26;
									if(d26 < j7) --j7;
									int k7 = j7 & 0xff;
									d26 -= j7;
									float d27 = FADE(d26);
									if(i7 == 0 || k7 != i2)
									{
										i2 = k7;
										int j2 = this->permutations[i6] + k7;
										int k2 = this->permutations[j2] + l6;
										int l2 = this->permutations[j2 + 1] + l6;
										int i3 = this->permutations[i6 + 1] + k7;
										int k3 = this->permutations[i3] + l6;
										int l3 = this->permutations[i3 + 1] + l6;
										d13 = lerp(d22, grad(this->permutations[k2], d20, d26, d24), grad(this->permutations[k3], d20 - 1, d26, d24));
										d15 = lerp(d22, grad(this->permutations[l2], d20, d26 - 1, d24), grad(this->permutations[l3], d20 - 1, d26 - 1, d24));
										d16 = lerp(d22, grad(this->permutations[k2 + 1], d20, d26, d24 - 1), grad(this->permutations[k3 + 1], d20 - 1, d26, d24 - 1));
										d18 = lerp(d22, grad(this->permutations[l2 + 1], d20, d26 - 1, d24 - 1), grad(this->permutations[l3 + 1], d20 - 1, d26 - 1, d24 - 1));
									}
									float d28 = lerp(d27, d13, d15);
									float d29 = lerp(d27, d16, d18);
									float d30 = lerp(d25, d28, d29);
									noises[i1] += d30 * d7;
									++i1;
								}
							}
						}
					}
			};
		}
	}
}