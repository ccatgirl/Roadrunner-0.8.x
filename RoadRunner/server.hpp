#pragma once

#include <RakPeerInterface.h>
#include <cstdint>
#include <map>
#include <entity/player.hpp>
#include <vector>
#include "world/world.hpp"

namespace RoadRunner {
	namespace entity{
		class Entity;
		class Player;
	}
	class Server {
	public:
		static Server* INSTANCE;
		bool is_running;
		RakNet::RakPeerInterface *peer;
		std::map<RakNet::RakNetGUID, RoadRunner::entity::Player *> players;
		std::map<int, RoadRunner::entity::Entity*> entities;
		int32_t entity_id;
		RoadRunner::world::World* world;

		Server(uint16_t port, uint32_t max_clients);
		void post_to_chat(std::string message);
		void send_block_data(int32_t x, int32_t y, int32_t z, uint8_t blockid, uint8_t meta);
		void addEntity(RoadRunner::entity::Entity* entity);
		void removeEntity(RoadRunner::entity::Entity* entity);
	};
}
