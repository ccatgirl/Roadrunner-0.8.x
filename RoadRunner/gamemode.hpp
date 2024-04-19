#pragma once
#include <cstdint>
#include <world/world.hpp>
#include <inventory/iteminstance.hpp>
#include <utils/vec3.hpp>

using RoadRunner::utils::Vec3;
namespace RoadRunner{
	namespace entity{
		class Player;
	}
	class GameMode{
		public:
			RoadRunner::entity::Player* player;

			GameMode(RoadRunner::entity::Player* player);

			void destroyBlock(int x, int y, int z, int side);
			bool useItemOn(RoadRunner::entity::Player* player, RoadRunner::world::World* world, RoadRunner::inventory::ItemInstance* item, int x, int y, int z, int side, Vec3* something);
			void startDestroyBlock(int x, int y, int z, int side){
				//vanilla also checks for bow
				this->destroyBlock(x, y, z, side);
			}
			virtual bool isCreativeType(){
				return false;
			}

			virtual bool isSurvivalType(){
				return false;
			}
	};

	class CreativeMode : public GameMode{
		public:
			CreativeMode(RoadRunner::entity::Player* player) : GameMode(player){};

			void destroyBlock(int x, int y, int z, int side){
				//TODO Level::extinguishFire
				//this->GameMode::destroyBlock(x, y, z, side);
			}

			virtual bool isCreativeType(){
				return true;
			}
	};

	class SurvivalMode : public GameMode{
		public:
			SurvivalMode(RoadRunner::entity::Player* player) : GameMode(player){};

			virtual bool isSurvivalType(){
				return true;
			}
	};
}
