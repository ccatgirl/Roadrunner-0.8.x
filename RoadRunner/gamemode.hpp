#pragma once
#include <cstdint>
#include <player.hpp>
#include <world/world.hpp>


namespace RoadRunner{
	
	class Player;
	class GameMode{
		public:
			RoadRunner::Player* player;

			GameMode(RoadRunner::Player* player);

			void destroyBlock(int x, int y, int z, int side);

			void startDestroyBlock(int x, int y, int z, int side){
				//vanilla also checks for bow
				this->destroyBlock(x, y, z, side);
			}
	};

	class CreativeMode : public GameMode{
		public:
			CreativeMode(RoadRunner::Player* player) : GameMode(player){};

			void destroyBlock(int x, int y, int z, int side){
				//TODO Level::extinguishFire
				//this->GameMode::destroyBlock(x, y, z, side);
			}
	};

	class SurvivalMode : public GameMode{
		public:
			SurvivalMode(RoadRunner::Player* player) : GameMode(player){};
	};
}