#include <network/packets/message_packet.hpp>

const uint8_t RoadRunner::network::packets::MessagePacket::packet_id = 0x85;

bool RoadRunner::network::packets::MessagePacket::deserialize_body(RakNet::BitStream *stream) {
	if (!this->username.Deserialize(stream)) {
        return false;
    }
    if (!this->message.Deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::MessagePacket::serialize_body(RakNet::BitStream *stream) {
    this->username.Serialize(stream);
    this->message.Serialize(stream);
}
