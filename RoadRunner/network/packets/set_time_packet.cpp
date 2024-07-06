#include <network/packets/set_time_packet.hpp>

const uint8_t RoadRunner::network::packets::SetTimePacket::packet_id = 0x86;

bool RoadRunner::network::packets::SetTimePacket::deserialize_body(RakNet::BitStream *stream) {
	if (!stream->Read<int32_t>(this->time)) {
		return false;
	}
	if (!stream->Read<bool>(this->started)) {
		return false;
	}
	return true;
}

void RoadRunner::network::packets::SetTimePacket::serialize_body(RakNet::BitStream *stream) {
	stream->Write<int32_t>(this->time);
	stream->Write<bool>(this->started);
}
