#include "pool_config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

void init_pool_config(pool_config_t *config, const char *url, uint16_t port, const char *username, const char *password) {
    strncpy(config->url, url, sizeof(config->url));
    config->port = port;
    strncpy(config->username, username, sizeof(config->username));
    strncpy(config->password, password, sizeof(config->password));
}

int connect_to_pool(const pool_config_t *config) {
    struct addrinfo hints, *server_info, *p;
    int sockfd;
    char port_str[6];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    snprintf(port_str, sizeof(port_str), "%u", config->port);

    if (getaddrinfo(config->url, port_str, &hints, &server_info) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    for (p = server_info; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to connect to pool\n");
        return -1;
    }

    freeaddrinfo(server_info);
    return sockfd;
}

int submit_result_to_pool(const pool_config_t *config, uint32_t nonce, uint8_t *hash) {
    // Assume a Stratum protocol is used; adjust the implementation according to the pool's protocol.
    char submit_message[512];
    snprintf(submit_message, sizeof(submit_message),
             "{\"id\": 4, \"method\": \"mining.submit\", \"params\": [\"%s\", \"job_id\", \"%08x\", \"%s\"]}\n",
             config->username, nonce, hash); // 'job_id' should be filled with the actual job ID received from the pool.

    // Send the result to the pool
    int sockfd = connect_to_pool(config);
    if (sockfd == -1) {
        return -1;
    }
    
    if (send(sockfd, submit_message, strlen(submit_message), 0) == -1) {
        perror("send");
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}

int receive_mining_job_from_pool(const pool_config_t *config, mining_job_t *job) {
    // Assuming a Stratum protocol; implementation may vary depending on the pool's protocol.
    char receive_buffer[1024];
    int sockfd = connect_to_pool(config);
    if (sockfd == -1) {
        return -1;
    }

    if (recv(sockfd, receive_buffer, sizeof(receive_buffer), 0) == -1) {
        perror("recv");
        close(sockfd);
        return -1;
    }

    // Parse the received message and populate the mining job structure.
    // This is a placeholder. Actual parsing depends on the pool's protocol.
    // For instance, you might use JSON parsing here.

    close(sockfd);
    return 0;
}