#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class LoginPacket {
            public:
                static const uint8_t packet_id;

                RakNet::RakString username;
                int32_t protocol_1;
                int32_t protocol_2;
                int32_t client_id;
                RakNet::RakString realms_data;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
