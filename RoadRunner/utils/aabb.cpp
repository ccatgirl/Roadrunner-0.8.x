#include <utils/aabb.hpp>

AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
	this->maxX = maxX;
	this->maxY = maxY;
	this->maxZ = maxZ;
	this->minX = minX;
	this->minY = minY;
	this->minZ = minZ;
}
