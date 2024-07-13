#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <PacketPriority.h>
#include <RakNetTypes.h>
#include <network/packets/chat_packet.hpp>
#include <network/packets/update_block_packet.hpp>
#include <server.hpp>
#include "block/block.hpp"
#include <chrono>
#include <thread>
#include <items/item.hpp>
#include "block/material/material.hpp"
#include <utils/properties.hpp>
#include <config.hpp>
#include <utils/mtrandom.hpp>
#include <world/noise/perlin_noise.hpp>
#include <world/biome/biome.hpp>
#include <world/generator/level_source.hpp>
#include <entity/entity.hpp>
#include <utils/multisystem.h>

#ifndef _WIN32
#include <signal.h>
#endif

using RoadRunner::block::Block;
using RoadRunner::block::material::Material;
using RoadRunner::Server;
using RoadRunner::network::packets::ChatPacket;using RoadRunner::network::packets::UpdateBlockPacket;
using RoadRunner::world::biome::Biome;
using namespace RoadRunner::utils;

void Server::post_to_chat(std::string message) {
	ChatPacket msg;
	msg.message = message.c_str();
	RakNet::BitStream send_stream;
	send_stream.Write<uint8_t>(msg.packet_id);
	msg.serialize_body(&send_stream);
	auto it = this->players.begin();
	while (it != this->players.end()) {
		this->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
		++it;
	}
}
void Server::addEntity(RoadRunner::entity::Entity* entity){
	this->entities[entity->entity_id] = entity;
}

void Server::removeEntity(RoadRunner::entity::Entity* entity){
	this->entities.erase(entity->entity_id);
}

void Server::send_block_data(int32_t x, int32_t y, int32_t z, uint8_t blockid, uint8_t meta) {
	UpdateBlockPacket pk;
	pk.x = x;
	pk.y = y & 0xff;
	pk.z = z;
	pk.block = blockid;
	pk.meta = meta;

	//TODO some broadcast packet method?
	RakNet::BitStream send_stream;
	send_stream.Write<uint8_t>(pk.packet_id);
	pk.serialize_body(&send_stream);

	auto it = this->players.begin();
	while (it != this->players.end()) {
		this->peer->Send(&send_stream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
		++it;
	}

}

uint64_t getTimeMS() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Server* Server::INSTANCE;
void handleSignal(
#ifdef _WIN32
	_In_ DWORD
#else
	int
#endif

signal
){
#ifdef _WIN32
	if (signal == CTRL_C_EVENT)
#endif
		Server::INSTANCE->is_running = false;
}
Server::Server(uint16_t port, uint32_t max_clients) {

	#ifdef _WIN32
		SetConsoleCtrlHandler((PHANDLER_ROUTINE) &handleSignal, true);
	#else
		signal(SIGINT, &handleSignal);
	#endif

	Server::INSTANCE = this;
	RoadRunner::world::BlankChunk::blankChunk = new RoadRunner::world::BlankChunk();
	bool enableTPSFix = false;
	uint64_t nextTPSMeasure = 0;
	double tpsTotal = 0;
	Property* properties[] = {
		new ShortProperty("server-port", &port),
		new UnsignedIntegerProperty("max-clients", &max_clients),
		new StringProperty("world-seed", &SEEDPROP),
		new BooleanProperty("is-creative", &IS_CREATIVE)
	};
	size_t sizeProperties = sizeof(properties) / sizeof(properties[0]);
	Properties props("server.properties", sizeProperties, properties);
	while(sizeProperties--){
		delete properties[sizeProperties];
	}

	int attempt = atoi(SEEDPROP.c_str()); //std::stoi is way too safe
	if(attempt){ //seed is numeric, use it(except 0)
		SEED = attempt;
	}else if(SEEDPROP[0] == '0' && SEEDPROP.length() == 1){ //seed is 0, use time since epoch in seconds as seed(vanilla)
		std::time_t result = std::time(0);
		SEED = result;
	}else{
		//TODO move to Utils::hashCode?
		SEED = 0;
		for(int j = 0; j < SEEDPROP.length(); ++j){
			SEED = SEED * 31 + SEEDPROP[j];
		}
	}

	Material::initMaterials();
	Block::initBlocks();
	RoadRunner::items::Item::initItems();

	Biome::initBiomes();

	this->entity_id = 1;
	this->peer = RakNet::RakPeerInterface::GetInstance();
	this->is_running = true;
	this->world = new RoadRunner::world::World(SEED);
	
	//TODO better gen, move out of here

	RoadRunner::world::generator::RandomLevelSource* levelSource = new RoadRunner::world::generator::RandomLevelSource(this->world, SEED);
	if(!this->world->loadWorld()){
		printf("Failed to load a world. Generating a new one(Seed: %d)\n", SEED);
		for(int index = 0; index < 256; ++index){
			this->world->chunks[index] = levelSource->getChunk((index & 0xf0) >> 4, index & 0xf);
		}
	}else{
		printf("World loaded\n");
	}

	double nextUpdate = 0.0;
	RakNet::Packet *packet;

	printf("Starting the server on port %d...\n", port);

	RakNet::SocketDescriptor sd(port, 0);
	RakNet::StartupResult result = peer->Startup(max_clients, &sd, 1);
	switch (result) {
		case RakNet::RAKNET_STARTED:
			printf("Started successfully\n");
			break;
		case RakNet::SOCKET_PORT_ALREADY_IN_USE:
			printf("Failed: The port is already in use.\n");
			goto forceend;
		default:
			printf("Failed: %d\n", result);
			goto forceend;
	}
   

	peer->SetMaximumIncomingConnections(max_clients);
	

	while (this->is_running) {
		RakNet::RakString data = "MCCPP;MINECON;Test";
		RakNet::BitStream stream;
		data.Serialize(&stream);
		peer->SetOfflinePingResponse((const char *)stream.GetData(), stream.GetNumberOfBytesUsed());

		unsigned long long int timeMS = getTimeMS();
		if(nextUpdate > timeMS){
			uint64_t skip = (uint64_t) (nextUpdate - timeMS);
			//printf("TIME: %u(%u) skipping %ul\n", (int)timeMS/1000, timeMS, skip);
			sleepmicro((int)skip * 1000);
			continue;
		}
		nextUpdate = (double)timeMS+50;
		if(nextTPSMeasure < timeMS){

			printf("Average TPS(5 sec): %f\n", tpsTotal/(double)((timeMS-(nextTPSMeasure-5000))/1000));
			tpsTotal = 0;
			nextTPSMeasure = timeMS+5000;
		}

		++tpsTotal;


		//tick entities in world
		this->world->tick();

		while((packet = peer->Receive())){
			if (packet->bitSize != 0) {
				RakNet::BitStream receive_stream(packet->data, BITS_TO_BYTES(packet->bitSize), false);

				uint8_t packet_id;
				receive_stream.Read<uint8_t>(packet_id);

				switch (packet_id) {
				case ID_NEW_INCOMING_CONNECTION:
					printf("A new connection is incoming.\n");
					if (this->players.count(packet->guid) == 0) {
						RoadRunner::entity::Player *player = new RoadRunner::entity::Player(this); //TODO not freed
						player->guid = packet->guid;
						this->players[packet->guid] = player;
					}
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					printf("The server is full.\n");
					break;
				case ID_DISCONNECTION_NOTIFICATION:
				case ID_CONNECTION_LOST:
					printf("A client lost the connection.\n");
					if (this->players.count(packet->guid) != 0) {
						delete this->players[packet->guid];
						this->players.erase(packet->guid);
					}
					break;
				default:
					if (this->players.count(packet->guid) != 0) {
						this->players[packet->guid]->handle_packet(packet_id, &receive_stream);
					}
					break;
				}
			}
			peer->DeallocatePacket(packet);
		}
	}

	forceend:
	RakNet::RakPeerInterface::DestroyInstance(peer);

	this->world->saveWorld();
	delete levelSource;
	delete this->world;
	delete RoadRunner::world::BlankChunk::blankChunk;
}
