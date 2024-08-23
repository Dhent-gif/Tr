// pthread_header.h
#ifndef PTHREAD_HEADER_H
#define PTHREAD_HEADER_H

#include <pthread.h>

// Struktur data yang akan digunakan oleh thread
typedef struct {
    int thread_id;
    // Tambahkan lebih banyak variabel sesuai kebutuhan
} thread_data_t;

// Fungsi untuk menjalankan thread
void *mining_thread(void *arg);

#endif // PTHREAD_HEADER_H