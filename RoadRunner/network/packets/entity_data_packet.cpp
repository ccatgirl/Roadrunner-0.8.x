#include <network/packets/entity_data_packet.hpp>

const uint8_t RoadRunner::network::packets::EntityDataPacket::packet_id = 0xb8;

bool RoadRunner::network::packets::EntityDataPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int16_t>(this->x)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->y)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->x)) {
        return false;
    }
    // TODO: Read nbt data
    return true;
}

void RoadRunner::network::packets::EntityDataPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int16_t>(this->x);
    stream->Write<uint8_t>(this->y);
    stream->Write<int16_t>(this->z);
    // TODO: Write nbt data
}
