#include <config.hpp>
#include <network/packets/send_inventory_packet.hpp>
#include <network/packets/use_item_packet.hpp>
#include <network/packets/remove_block_packet.hpp>
#include <network/packets/add_player_packet.hpp>
#include <network/packets/animate_packet.hpp>
#include <network/packets/chat_packet.hpp>
#include <network/packets/chunk_data_packet.hpp>
#include <network/packets/login_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/message_packet.hpp>
#include <network/packets/move_player_packet.hpp>
#include <network/packets/player_equipment_packet.hpp>
#include <network/packets/ready_packet.hpp>
#include <network/packets/remove_player_packet.hpp>
#include <network/packets/request_chunk_packet.hpp>
#include <network/packets/start_game_packet.hpp>
#include <network/enums/ready_status_enum.hpp>
#include <network/enums/login_status_enum.hpp>
#include <player.hpp>
#include <world/perlin.hpp>
#include <block/block.hpp>
using RoadRunner::network::packets::SendInventoryPacket;
using RoadRunner::network::packets::UseItemPacket;
using RoadRunner::network::packets::RemoveBlockPacket;
using RoadRunner::network::packets::AddPlayerPacket;
using RoadRunner::network::packets::AnimatePacket;
using RoadRunner::network::packets::ChatPacket;
using RoadRunner::network::packets::ChunkDataPacket;
using RoadRunner::network::packets::LoginPacket;
using RoadRunner::network::packets::LoginStatusPacket;
using RoadRunner::network::packets::MessagePacket;
using RoadRunner::network::packets::MovePlayerPacket;
using RoadRunner::network::packets::PlayerEquipmentPacket;
using RoadRunner::network::packets::ReadyPacket;
using RoadRunner::network::packets::RemovePlayerPacket;
using RoadRunner::network::packets::RequestChunkPacket;
using RoadRunner::network::packets::StartGamePacket;
using RoadRunner::network::enums::ReadyStatusEnum;
using RoadRunner::network::enums::LoginStatusEnum;
using RoadRunner::world::Perlin;
using RoadRunner::inventory::ItemInstance;
using RoadRunner::block::Block;
template <typename T>
void RoadRunner::Player::send_packet(T &packet) {
    // Send a packet to the player
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, this->guid, false);
}

template <typename T>
void RoadRunner::Player::broadcast_packet(T &packet) {
    // Send a packet to all players
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    auto it = Server::INSTANCE->players.begin();
    while (it != Server::INSTANCE->players.end()) {
        Server::INSTANCE->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }
}

float fsignbit(float f){
	if(f > 0){
		return 1;
	}else if(f < 0) return -1;
	return 0;
}

template <typename T>
void RoadRunner::Player::broadcast_except_packet(T &packet) {
    // Send a packet to all players except the one sending it
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    auto it = this->server->players.begin();
    while (it != this->server->players.end()) {
        if (it->first == this->guid) {
            ++it;
            continue;
        }
        this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }
}

void RoadRunner::Player::handle_packet(uint8_t packet_id, RakNet::BitStream *stream) {
    if (packet_id == LoginPacket::packet_id) { //TODO switch
        LoginPacket login;
        login.deserialize_body(stream);
        this->username = login.username.C_String();
        this->x = SPAWN_X;
        this->y = SPAWN_Y;
        this->z = SPAWN_Z;

        // Continue the login sequence
        LoginStatusPacket login_status;

        if (login.protocol_1 < PROTOCOL) {
            login_status.status = (int32_t)LoginStatusEnum::outdated_client;
        } else if (login.protocol_1 > PROTOCOL) {
            login_status.status = (int32_t)LoginStatusEnum::outdated_server;
        }else {
            login_status.status = (int32_t)LoginStatusEnum::success;
        }
        this->send_packet(login_status);

        if(login_status.status != (int32_t)LoginStatusEnum::success){
            return;
        }

        printf("%s started a session(EID: %d)\n", this->username.c_str(), this->entity_id);
        StartGamePacket start_game;
        start_game.seed = SEED;
        start_game.generator = 0;
        start_game.gamemode = IS_CREATIVE;
        start_game.entity_id = this->entity_id;
        start_game.x = SPAWN_X;
        start_game.y = SPAWN_Y;
        start_game.z = SPAWN_Z;
        this->send_packet(start_game);
    }else if(packet_id == UseItemPacket::packet_id){
		UseItemPacket useitem_pk;
		useitem_pk.deserialize_body(stream);
        ItemInstance item(useitem_pk.block, 1, useitem_pk.meta); //TODO serverside inv

        if(item.isValid){
            if(useitem_pk.face == 255){
                //TODO egg/snowballs
            }else{
                int x = useitem_pk.x;
                int y = useitem_pk.y;
                int z = useitem_pk.z;
                auto world = this->server->world; //TODO multiworld

                int blockID = world->get_block_id(x, y, z);
                Block* block = Block::blocks[blockID]; 
                
                if(block != Block::invisible_bedrock && (!block || !block->use(world, x, y, z, this))){
                    float savedX = this->x;
                    float savedY = this->y;
                    float savedZ = this->z;
                    this->setPos(useitem_pk.pos_x, useitem_pk.pos_y, useitem_pk.pos_z);
                    Vec3 vec(useitem_pk.fx + x, useitem_pk.fy + y, useitem_pk.fz + z);
                    this->gamemode->useItemOn(this, world, &item, x, y, z, useitem_pk.face, &vec);

                    this->setPos(savedX, savedY, savedZ);
                }
            }
        }else{
            printf("Unknown item: %d %d %d ICM\n", useitem_pk.block, item.count, item.meta);
        }
	} else if(packet_id == RemoveBlockPacket::packet_id){
		RemoveBlockPacket remove_block_pk;
		remove_block_pk.deserialize_body(stream);
		
		int x = remove_block_pk.x;
		int y = remove_block_pk.y;
		int z = remove_block_pk.z;
		this->gamemode->destroyBlock(x, y, z, 0);
		//this->server->world->set_block(x, y, z, 0, 0, 0b00000010); //TODO flag generator?	
	} else if (packet_id == ReadyPacket::packet_id) {
        ReadyPacket ready_packet;
        ready_packet.deserialize_body(stream);
        if (ready_packet.status != (uint8_t)ReadyStatusEnum::ready_client_generation) return;
        // Join game message
        printf("%s has joined the game\n", this->username.c_str());
        this->server->post_to_chat(this->username + " has joined!");
        // Add the player
        AddPlayerPacket add_player;
        add_player.client_guid = 0;
        add_player.username = this->username.c_str();
        add_player.entity_id = this->entity_id;
        add_player.x = this->x;
        add_player.y = this->y;
        add_player.z = this->z;
        add_player.pitch = this->pitch;
        add_player.yaw = this->yaw;
        this->broadcast_except_packet(add_player);
        // Add the other players
        auto it = this->server->players.begin();
        while (it != this->server->players.end()) {
            if (it->first == this->guid) {
                ++it;
                continue;
            }
            Player *player = it->second;
            add_player.username = player->username.c_str();
            add_player.entity_id = player->entity_id;
            add_player.x = player->x;
            add_player.y = player->y;
            add_player.z = player->z;
            add_player.pitch = player->pitch;
            add_player.yaw = player->yaw;
            this->send_packet(add_player);
            ++it;
        }
    } else if (packet_id == ChatPacket::packet_id || packet_id == MessagePacket::packet_id) {
        // WARN: Currently MessagePacket and ChatPacket are identical save the id
        // if that were to change then this needs to change accordingly
        MessagePacket msg;
        msg.deserialize_body(stream);
        std::string formatted = "<" + this->username + "> " + msg.message.C_String();
        printf("[CHAT]: %s\n", formatted.c_str());
        // Send
        msg.message = msg.message.C_String();
        Player::broadcast_packet(msg);
    } else if (packet_id == AnimatePacket::packet_id) {
        AnimatePacket animate;
        animate.deserialize_body(stream);
        animate.entity_id = this->entity_id;
        Player::broadcast_packet(animate);
    } else if (packet_id == PlayerEquipmentPacket::packet_id) {
        // TODO: Check validity of item
        PlayerEquipmentPacket player_equipment;
        player_equipment.deserialize_body(stream);
        player_equipment.entity_id = this->entity_id;
        this->broadcast_except_packet(player_equipment);
    } else if (packet_id == MovePlayerPacket::packet_id) {
        MovePlayerPacket move_player;
        move_player.deserialize_body(stream);
        bool valid = true;
        // Ensure entity id is that of the player
        if (move_player.entity_id != this->entity_id) {
            // Attempt to move a diffrent entity
            return;
        }
#if WORLD_BORDER
        // Make sure it doesn't go over the world border (X/Z)
        if (move_player.x < 0.f) {
            move_player.x = 0.f;
            valid = false;
        } else if (move_player.x > 256.f) {
            move_player.x = 256.f;
            valid = false;
        }
        if (move_player.z < 0.f) {
            move_player.z = 0.f;
            valid = false;
        } else if (move_player.z > 256.f) {
            move_player.z = 256.f;
            valid = false;
        }
#endif

        // Make sure it isn't a teleport
        // TODO: Check dy and give fall damage as needed
        int dx = abs(move_player.x - this->x);
        if (dx > MAX_DIST){
            this->x += fsignbit(this->x - move_player.x) * MAX_DIST;
            move_player.x = this->x;
            valid = false;
        }
        int dz = abs(move_player.z - this->z);
        if (dz > MAX_DIST) {
            this->z += fsignbit(this->z - move_player.z) * MAX_DIST;
            move_player.z = this->z;
            valid = false;
        }
        // Send
        if (valid) {
            this->broadcast_except_packet(move_player);
        } else {
            Player::broadcast_packet(move_player);
        }
        // Update pos
        this->x = move_player.x;
        this->y = move_player.y;
        this->z = move_player.z;
        this->pitch = move_player.pitch;
        this->yaw = move_player.yaw;
        this->headYaw = move_player.head_yaw;
    } else if (packet_id == SendInventoryPacket::packet_id) {
        SendInventoryPacket send_inventory;
        send_inventory.deserialize_body(stream);
        ItemType some_item = send_inventory.items[0];
        printf("ID: %i, AUX: %i, COUNT: %i\n", some_item.id, some_item.aux, some_item.count);
    } else if (packet_id == RequestChunkPacket::packet_id) {
        RequestChunkPacket request_chunk;
        request_chunk.deserialize_body(stream);

        ChunkDataPacket chunk_data;
        chunk_data.x = request_chunk.x;
        chunk_data.z = request_chunk.z;
        auto chunk = this->server->world->get_chunk(chunk_data.x, chunk_data.z);
        chunk_data.chunk = chunk;
        
        this->send_packet(chunk_data);
    }
}

RoadRunner::Player::~Player() {
    // Remove
    RemovePlayerPacket rm_player;
    rm_player.entity_id = this->entity_id;
    rm_player.client_guid = 0;
    Player::broadcast_packet(rm_player);
    // Log/chat
    std::string msg = this->username + " has left the game";
    puts(msg.c_str());
    this->server->post_to_chat(msg.c_str());

    delete this->gamemode;

    // Call superclass deconstructor
    Entity::~Entity();
}
