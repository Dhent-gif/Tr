#include "kheavyhash.h"
#include <string.h>

// Initial values (IV) for KHeavyHash
const uint32_t IV[8] = {
    0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
    0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
};

// Optimized KHeavyHash implementation
void kheavyhash(uint8_t* input, uint32_t input_len, uint8_t* output) {
    uint32x4_t state[2];
    state[0] = vld1q_u32(&IV[0]);
    state[1] = vld1q_u32(&IV[4]);

    // Process input in blocks of KHEAVYHASH_BLOCK_SIZE
    for (uint32_t i = 0; i < input_len; i += KHEAVYHASH_BLOCK_SIZE) {
        uint32x4_t block[4];
        block[0] = vld1q_u32((uint32_t*)(input + i));
        block[1] = vld1q_u32((uint32_t*)(input + i + 16));
        block[2] = vld1q_u32((uint32_t*)(input + i + 32));
        block[3] = vld1q_u32((uint32_t*)(input + i + 48));

        kheavyhash_round(state, block);
    }

    // Finalize and produce the hash
    vst1q_u32((uint32_t*)output, state[0]);
    vst1q_u32((uint32_t*)(output + 16), state[1]);
}

// Optimized round function using NEON
void kheavyhash_round(uint32x4_t* state, const uint32x4_t* message) {
    for (int i = 0; i < KHEAVYHASH_ROUNDS; ++i) {
        state[0] = veorq_u32(state[0], message[0]);
        state[1] = veorq_u32(state[1], message[1]);
        state[0] = vshlq_n_u32(state[0], 5);
        state[1] = vshlq_n_u32(state[1], 5);
        state[0] = vorrq_u32(state[0], vshrq_n_u32(state[0], 27));
        state[1] = vorrq_u32(state[1], vshrq_n_u32(state[1], 27));
    }
}