#include "kheavyhash_mining.h"
#include <string.h>

const uint32_t IV[8] = {
    0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
    0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
};

void init_mining_job(mining_job_t *job, uint8_t* header, uint32_t nonce_start, uint32_t nonce_end, uint32_t* target) {
    memcpy(job->header, header, sizeof(job->header));
    job->nonce_start = nonce_start;
    job->nonce_end = nonce_end;
    memcpy(job->target, target, sizeof(job->target));
}

int perform_mining(mining_job_t *job, uint8_t* output_hash, uint32_t* found_nonce) {
    uint8_t temp_hash[KHEAVYHASH_HASH_SIZE];
    for (uint32_t nonce = job->nonce_start; nonce <= job->nonce_end; ++nonce) {
        memcpy(job->header + 76, &nonce, sizeof(nonce));  // Update nonce in header
        kheavyhash(job->header, sizeof(job->header), temp_hash);

        if (compare_hash_with_target(temp_hash, job->target)) {
            memcpy(output_hash, temp_hash, KHEAVYHASH_HASH_SIZE);
            *found_nonce = nonce;
            return 1;  // Mining successful
        }
    }
    return 0;  // Mining unsuccessful
}

void kheavyhash(uint8_t* input, uint32_t input_len, uint8_t* output) {
    uint32x4_t state[2];
    state[0] = vld1q_u32(&IV[0]);
    state[1] = vld1q_u32(&IV[4]);

    for (uint32_t i = 0; i < input_len; i += KHEAVYHASH_BLOCK_SIZE) {
        uint32x4_t block[4];
        block[0] = vld1q_u32((uint32_t*)(input + i));
        block[1] = vld1q_u32((uint32_t*)(input + i + 16));
        block[2] = vld1q_u32((uint32_t*)(input + i + 32));
        block[3] = vld1q_u32((uint32_t*)(input + i + 48));

        kheavyhash_round(state, block);
    }

    vst1q_u32((uint32_t*)output, state[0]);
    vst1q_u32((uint32_t*)(output + 16), state[1]);
}

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

int compare_hash_with_target(uint8_t* hash, uint32_t* target) {
    for (int i = 7; i >= 0; --i) {
        uint32_t hash_part;
        memcpy(&hash_part, hash + i * 4, sizeof(uint32_t));

        if (hash_part < target[i]) {
            return 1;  // Hash is less than target
        } else if (hash_part > target[i]) {
            return 0;  // Hash is greater than target
        }
    }
    return 1;  // Hash is equal to target
}