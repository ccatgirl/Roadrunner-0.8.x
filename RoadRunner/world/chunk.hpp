#pragma once

#include <map>
#include <cstdint>

#define COORDS_TO_INDEX(x, y, z) (((x & 0x0f) << 11) + ((z & 0x0f) << 7) + (y & 0x7f))
#define NBARR_GET(i, arr) (i & 1 ? arr[i >> 1] >> 4 : arr[i >> 1] & 0x0f)
#define NBARR_SET(i, v, arr) { \
    if (i & 1) { \
        arr[i >> 1] &= 0x0f; \
        arr[i >> 1] |= ((v & 0x0f) << 4); \
    } else { \
        arr[i >> 1] &= 0xf0; \
        arr[i >> 1] |= (v & 0x0f); \
    } \
}

namespace RoadRunner {
    namespace world {
        class Chunk {
        public:
            
            int32_t x;
            int32_t z;
            uint8_t block_ids[32768];
            uint8_t block_metas[16384];
            //TODO skylight, blocklight (both 16384)

            Chunk(int32_t x, int32_t z);

            uint8_t get_block_id(int32_t x, int32_t y, int32_t z);

            void set_block_id(int32_t x, int32_t y, int32_t z, uint8_t block_id);

            uint8_t get_block_meta(int32_t x, int32_t y, int32_t z);

            void set_block_meta(int32_t x, int32_t y, int32_t z, uint8_t block_meta);
        };

        class BlankChunk : public Chunk {
        public:
            static BlankChunk blankChunk; 
            BlankChunk();
            void set_block_id(int32_t x, int32_t y, int32_t z, uint8_t block_id);
            void set_block_meta(int32_t x, int32_t y, int32_t z, uint8_t block_meta);
        };
    }
}