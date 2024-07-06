#include "pickaxeitem.hpp"
#include <inventory/iteminstance.hpp>
#include <block/block.hpp>
#include <block/material/material.hpp>

using namespace RoadRunner::items;
using namespace RoadRunner::block;
using RoadRunner::block::material::Material;
using namespace RoadRunner::inventory;

PickaxeItem::PickaxeItem(int id, Item::Tier* tier) : DiggerItem(id, tier){
	this->damageAgainstEntity = tier->entityDamage + 2;
	std::vector<Block*> vec = {
		Block::cobblestone,
		Block::stoneSlab,
		Block::stoneSlabHalf,
		Block::stone,
		Block::sandStone,
		Block::mossStone,
		Block::ironOre,
		Block::ironBlock,
		Block::coalOre,
		Block::goldBlock,
		Block::goldOre,
		Block::diamondOre,
		Block::diamondBlock,
		//TODO Block::ice,
		Block::lapisOre,
		Block::lapisBlock,
		Block::redStoneOre,
		Block::redStoneOre_lit
	};

	this->setTiles(&vec);
}

bool PickaxeItem::canDestroySpecial(RoadRunner::block::Block* block){
	if(block == Block::obsidian || block == Block::glowingObsidian){
		return this->tier->level == 3;
	}

	if(block == Block::redStoneOre || block == Block::redStoneOre_lit || block == Block::diamondBlock || block == Block::diamondOre || block == Block::goldBlock || block == Block::goldOre){
		return this->tier->level > 1;
	}

	if(block == Block::ironBlock || block == Block::ironOre || block == Block::lapisBlock || block == Block::lapisOre){
		return this->tier->level > 0;
	}

	return block->material == Material::stone || block->material == Material::metal;
}

float PickaxeItem::getDestroySpeed(RoadRunner::inventory::ItemInstance* item, RoadRunner::block::Block* block){

	if(block){
		if(block->material == Material::metal || block->material == Material::stone){
			return this->efficiencyMultiplier;
		}
	}

	return DiggerItem::getDestroySpeed(item, block);
}
