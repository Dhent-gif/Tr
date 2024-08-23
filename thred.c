// pthread_implementation.c
#include <stdio.h>
#include <stdlib.h>
#include "pthread_header.h"

// Implementasi fungsi mining_thread
void *mining_thread(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    printf("Thread %d is running\n", data->thread_id);
    // Lakukan operasi mining di sini
    pthread_exit(NULL);
}