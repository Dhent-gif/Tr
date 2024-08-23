#include <stdio.h>
#include "kheavyhash_mining.h"

int main() {
    uint8_t header[80] = {0};  // Initialize block header (you need to fill this with actual block data)
    uint32_t target[8] = {0};  // Initialize target (you need to set this based on difficulty)
    uint8_t output_hash[KHEAVYHASH_HASH_SIZE];
    uint32_t found_nonce;

    mining_job_t job;
    init_mining_job(&job, header, 0, 0x