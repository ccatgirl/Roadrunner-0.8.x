#include <network/packets/rotate_head_packet.hpp>

const uint8_t RoadRunner::network::packets::RotateHeadPacket::packet_id = 0x94;

bool RoadRunner::network::packets::RotateHeadPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<int8_t>(this->yaw)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::RotateHeadPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int8_t>(this->yaw);
}
