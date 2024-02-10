#pragma once

#include <RakPeerInterface.h>
#include <cstdint>
#include <map>
#include <player.hpp>
#include <vector>
#include "world/world.hpp"
namespace RoadRunner {
    class Player;

    class Server {
    public:
        static Server* INSTANCE;
        bool is_running;
        RakNet::RakPeerInterface *peer;
        std::map<RakNet::RakNetGUID, RoadRunner::Player *> players;
        std::vector<RoadRunner::Entity*> entities;
        int32_t entity_id;
        std::vector<int32_t> reuseable_entity_ids; //TODO 0.8.1 might have problems when readding previously removed entity
        RoadRunner::world::World* world;

        Server(uint16_t port, uint32_t max_clients);
        void post_to_chat(std::string message);
        void send_block_data(int32_t x, int32_t y, int32_t z, uint8_t blockid, uint8_t meta);
        void addEntity(RoadRunner::Entity* entity);
        void removeEntity(RoadRunner::Entity* entity);
    };
}
