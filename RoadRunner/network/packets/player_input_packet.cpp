#include <network/packets/player_input_packet.hpp>

const uint8_t RoadRunner::network::packets::PlayerInputPacket::packet_id = 0xb9;

bool RoadRunner::network::packets::PlayerInputPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<float>(this->motion_x)) {
        return false;
    }
    if (!stream->Read<float>(this->motion_y)) {
        return false;
    }
    if (!stream->Read<bool>(this->jumping)) {
        return false;
    }
    if (!stream->Read<bool>(this->sneaking)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::PlayerInputPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<float>(this->motion_x);
    stream->Write<float>(this->motion_y);
    stream->Write<bool>(this->jumping);
    stream->Write<bool>(this->sneaking);
}
