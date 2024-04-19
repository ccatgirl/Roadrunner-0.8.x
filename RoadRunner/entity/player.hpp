#pragma once

#include <string>

#include <BitStream.h>
#include <config.hpp>
#include <entity/entity.hpp>
#include <server.hpp>
#include <gamemode.hpp>
namespace RoadRunner {
    class Server;
    namespace entity{
		class Player : public RoadRunner::entity::Entity { //TODO extends Mob
			public:
				RakNet::RakNetGUID guid;
				std::string username = "???";
				RoadRunner::GameMode* gamemode;
				template <typename T>
				void send_packet(T &packet);
				template <typename T>
				static void broadcast_packet(T &packet);
				template <typename T>
				void broadcast_except_packet(T &packet);
		
				void handle_packet(uint8_t packet_id, RakNet::BitStream *stream);
		
				Player(Server *server): Entity(server) {
					if(IS_CREATIVE) this->gamemode = new CreativeMode(this);
					else this->gamemode = new SurvivalMode(this);
				}
		
				~Player();
		};
    }
}
