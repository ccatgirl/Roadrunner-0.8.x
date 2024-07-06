#include <network/packets/container_set_content_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerSetContentPacket::packet_id = 0xb4;

bool RoadRunner::network::packets::ContainerSetContentPacket::deserialize_body(RakNet::BitStream *stream) {
	if (!stream->Read<uint8_t>(this->window_id)) {
		return false;
	}
	int16_t item_count = 0;
	if (!stream->Read<int16_t>(item_count)) {
		return false;
	}
	this->items.clear();
	for (int i = 0; i < item_count; i++) {
		ItemType item;
		if (!item.deserialize(stream)) {
			return false;
		}
		this->items.push_back(item);
	}
	int16_t slots_count = 0;
	for (int i = 0; i < slots_count; i++) {
		int32_t slot;
		if (!stream->Read<int32_t>(slot)) {
			return false;
		}
		this->hotbar_slots.push_back(slot);
	}
	return true;
}

void RoadRunner::network::packets::ContainerSetContentPacket::serialize_body(RakNet::BitStream *stream) {
	stream->Write<uint8_t>(this->window_id);
	stream->Write<int16_t>(this->items.size());
	for (size_t i = 0; i < this->items.size(); ++i) {
		this->items[i].serialize(stream);
	}
	stream->Write<int16_t>(this->hotbar_slots.size());
	for (size_t i = 0; i < this->hotbar_slots.size(); ++i) {
		stream->Write<int32_t>(this->hotbar_slots[i]);
	}
}
