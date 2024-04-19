#pragma once

namespace RoadRunner{
	namespace items{
		class Item;
	}
	namespace block{
		class Block;
	}

	namespace world{
		class World;
	}

	namespace entity{
		class Player;
	}

	namespace inventory{
		class ItemInstance{
	
			public:

				int meta = 0;
				int count = 0;
				RoadRunner::items::Item* item = 0;
				RoadRunner::block::Block* block = 0;
				bool isValid = 0;

				ItemInstance(RoadRunner::items::Item* item) : ItemInstance::ItemInstance(item, 1, 0){}
				ItemInstance(RoadRunner::items::Item* item, int count) : ItemInstance::ItemInstance(item, count, 0){};
				ItemInstance(RoadRunner::items::Item* item, int count, int meta);
				ItemInstance(RoadRunner::block::Block* block) : ItemInstance::ItemInstance(block, 1, 0){};
				ItemInstance(RoadRunner::block::Block* block, int count) : ItemInstance::ItemInstance(block, count, 0){};
				ItemInstance(RoadRunner::block::Block* block, int count, int meta);
				ItemInstance(int id, int count, int meta);
				void _setItem(int id);
				void init(int id, int count, int meta){
					this->meta = meta;
					this->count = count;
					this->_setItem(id);
				}

				bool useOn(RoadRunner::entity::Player* player,  RoadRunner::world::World* world, int x, int y, int z, int face, float faceX, float faceY, float faceZ);

				bool isItem();
		};
	}
}
