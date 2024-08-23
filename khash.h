#ifndef KHEAVYHASH_H
#define KHEAVYHASH_H

#include <stdint.h>
#include <arm_neon.h>

// Constants for KHeavyHash
#define KHEAVYHASH_ROUNDS 13
#define KHEAVYHASH_BLOCK_SIZE 64
#define KHEAVYHASH_HASH_SIZE 32

// Function prototypes
void kheavyhash(uint8_t* input, uint32_t input_len, uint8_t* output);
void kheavyhash_round(uint32x4_t* state, const uint32x4_t* message);

#endif // KHEAVYHASH_H