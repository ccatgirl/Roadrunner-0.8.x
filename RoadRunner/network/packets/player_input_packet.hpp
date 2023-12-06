#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class PlayerInputPacket {
            public:
                static const uint8_t packet_id;

                float motion_x;
                float motion_y;
                bool jumping;
                bool sneaking;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
