#include <stdio.h>
#include "kheavyhash.h"

int main() {
    uint8_t input[] = "Kaspa example input";
    uint8_t output[KHEAVYHASH_HASH_SIZE];

    kheavyhash(input, strlen((char*)input), output);

    printf("Optimized KHeavyHash: ");
    for (int i = 0; i < KHEAVYHASH_HASH_SIZE; ++i) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}