#pragma once
#include <stdint.h>
#include "item.hpp"

namespace RoadRunner {
	namespace block{
		class Block;
	}
	namespace items{
		class BlockItem : public Item{
			public:
				
				int blockID;

				BlockItem(int16_t id) : Item(id){
					this->blockID = id + 256;
				}
				virtual ~BlockItem(){}

				virtual bool useOn(RoadRunner::inventory::ItemInstance* instance, RoadRunner::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ) override;
		};

		class AuxDataBlockItem : public BlockItem{
			public:

				RoadRunner::block::Block* block;

				AuxDataBlockItem(int16_t id, RoadRunner::block::Block* block) : BlockItem(id){
					this->block = block;
					this->setMaxDamage(0);
					this->setStackedByData(1);
				}

				virtual int getLevelDataForAuxValue(int meta) override{
					return meta;
				}
		};

		class SaplingBlockItem : public BlockItem{
			public:
				SaplingBlockItem(int16_t id) : BlockItem(id){
					this->setMaxDamage(0);
					this->setStackedByData(1);
				}

				virtual int getLevelDataForAuxValue(int meta) override{
					return meta;
				}
		};
		class LeafBlockItem : public BlockItem{
			public:
				LeafBlockItem(int16_t id) : BlockItem(id){
					this->setMaxDamage(0);
					this->setStackedByData(1);
				}

				virtual int getLevelDataForAuxValue(int meta) override{
					return meta;
				}
		};
		class ClothBlockItem : public BlockItem{
			public:
				ClothBlockItem(int16_t id) : BlockItem(id){
					this->setMaxDamage(0);
					this->setStackedByData(1);
				}


				virtual int getLevelDataForAuxValue(int meta) override{
					return meta;
				}
		};

		class WoodSlabBlockItem : public AuxDataBlockItem{ //magik of StoneTileItem... *wait this one is called WoodSlabBlock::Item*... mojang moment(QuartzBlockTile moment)
			public:
				WoodSlabBlockItem(int16_t id, RoadRunner::block::Block* block) : AuxDataBlockItem(id, block){

				}

				virtual bool useOn(RoadRunner::inventory::ItemInstance* instance, RoadRunner::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ) override;
		};

		class StoneSlabBlockItem : public BlockItem{
			public:
				StoneSlabBlockItem(int16_t id) : BlockItem(id){
					this->setMaxDamage(0);
					this->setStackedByData(1);
				}

				virtual int getLevelDataForAuxValue(int meta) override{
					return meta;
				}

				virtual bool useOn(RoadRunner::inventory::ItemInstance* instance, RoadRunner::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ) override;
		};
	}
}
