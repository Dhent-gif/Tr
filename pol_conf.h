#ifndef POOL_CONFIG_H
#define POOL_CONFIG_H

#include <stdint.h>

// Structure to hold pool configuration
typedef struct {
    char url[256];       // Pool URL (e.g., stratum+tcp://pool.example.com)
    uint16_t port;       // Pool port (e.g., 3333)
    char username[128];  // Username (e.g., wallet address or username.worker)
    char password[64];   // Password (if any, often empty)
} pool_config_t;

// Function prototypes

// Initialize pool configuration with given parameters
void init_pool_config(pool_config_t *config, const char *url, uint16_t port, const char *username, const char *password);

// Connect to the mining pool using the given configuration
int connect_to_pool(const pool_config_t *config);

// Send mining job result to the pool
int submit_result_to_pool(const pool_config_t *config, uint32_t nonce, uint8_t *hash);

// Receive and parse mining jobs from the pool
int receive_mining_job_from_pool(const pool_config_t *config, mining_job_t *job);

#endif // POOL_CONFIG_H