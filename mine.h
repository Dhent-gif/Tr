#ifndef KHEAVYHASH_MINING_H
#define KHEAVYHASH_MINING_H

#include <stdint.h>
#include <arm_neon.h>

// Constants for KHeavyHash Mining
#define KHEAVYHASH_ROUNDS 13
#define KHEAVYHASH_BLOCK_SIZE 64
#define KHEAVYHASH_HASH_SIZE 32

// Structure to hold mining job information
typedef struct {
    uint8_t header[80];          // Block header (80 bytes)
    uint32_t nonce_start;        // Starting nonce
    uint32_t nonce_end;          // Ending nonce
    uint32_t target[8];          // Target for the hash
} mining_job_t;

// Function prototypes

// Initialize a mining job with the given header and nonce range
void init_mining_job(mining_job_t *job, uint8_t* header, uint32_t nonce_start, uint32_t nonce_end, uint32_t* target);

// Perform the mining operation, returning the successful nonce if found
int perform_mining(mining_job_t *job, uint8_t* output_hash, uint32_t* found_nonce);

// Hashing function for KHeavyHash
void kheavyhash(uint8_t* input, uint32_t input_len, uint8_t* output);

// Internal round function used by kheavyhash
void kheavyhash_round(uint32x4_t* state, const uint32x4_t* message);

// Compare hash with the target
int compare_hash_with_target(uint8_t* hash, uint32_t* target);

#endif // KHEAVYHASH_MINING_H