#include <network/packets/set_entity_link_packet.hpp>

const uint8_t RoadRunner::network::packets::SetEntityLinkPacket::packet_id = 0xa9;

bool RoadRunner::network::packets::SetEntityLinkPacket::deserialize_body(RakNet::BitStream *stream) {
	if (!stream->Read<int32_t>(this->from)) {
		return false;
	}
	if (!stream->Read<int32_t>(this->to)) {
		return false;
	}
	if (!stream->Read<int32_t>(this->type)) {
		return false;
	}
	return true;
}

void RoadRunner::network::packets::SetEntityLinkPacket::serialize_body(RakNet::BitStream *stream) {
	stream->Write<int32_t>(this->from);
	stream->Write<int32_t>(this->to);
	stream->Write<int32_t>(this->type);
}
