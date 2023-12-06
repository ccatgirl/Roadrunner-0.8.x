#include <network/packets/move_entity_packet.hpp>

const uint8_t RoadRunner::network::packets::MoveEntityPacket::packet_id = 0x90;

bool RoadRunner::network::packets::MoveEntityPacket::deserialize_body(RakNet::BitStream *stream) {
    return true;
}

void RoadRunner::network::packets::MoveEntityPacket::serialize_body(RakNet::BitStream *stream) {
}
