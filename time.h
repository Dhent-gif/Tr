#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define NONCE_START 0
#define NONCE_END 1000000

typedef struct {
    int thread_id;
    uint32_t start_nonce;
    uint32_t end_nonce;
} thread_data_t;

void *mining_thread(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    uint32_t nonce;
    clock_t start_time, end_time;
    double time_taken;

    start_time = clock(); // Mulai pengukuran waktu

    // Simulasi proses hashing
    for (nonce = data->start_nonce; nonce < data->end_nonce; nonce++) {
        // Perform mining operation here
    }

    end_time = clock(); // Akhiri pengukuran waktu
    time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Thread %d completed in %f seconds\n", data->thread_id, time_taken);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int i;

    // Membagi rentang nonce di antara thread
    for (i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start_nonce = NONCE_START + (i * (NONCE_END - NONCE_START) / NUM_THREADS);
        thread_data[i].end_nonce = NONCE_START + ((i + 1) * (NONCE_END - NONCE_START) / NUM_THREADS);
        pthread_create(&threads[i], NULL, mining_thread, (void *)&thread_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}