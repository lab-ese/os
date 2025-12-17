#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_data = 0;
int read_count = 0;

pthread_mutex_t read_mutex;   // For read_count
pthread_mutex_t write_mutex;  // For writing

void *reader(void *arg) {
    int id = *((int *)arg);
    
    for (int i = 0; i < 3; i++) {
        // Entry section
        pthread_mutex_lock(&read_mutex);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&write_mutex);  // First reader locks writer
        }
        pthread_mutex_unlock(&read_mutex);
        
        // Critical section - Reading
        printf("Reader %d: Read data = %d\n", id, shared_data);
        sleep(1);
        
        // Exit section
        pthread_mutex_lock(&read_mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&write_mutex);  // Last reader unlocks writer
        }
        pthread_mutex_unlock(&read_mutex);
        
        sleep(1);
    }
    
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    
    for (int i = 0; i < 3; i++) {
        // Entry section
        pthread_mutex_lock(&write_mutex);
        
        // Critical section - Writing
        shared_data++;
        printf("Writer %d: Wrote data = %d\n", id, shared_data);
        sleep(2);
        
        // Exit section
        pthread_mutex_unlock(&write_mutex);
        
        sleep(2);
    }
    
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    // Initialize mutexes
    pthread_mutex_init(&read_mutex, NULL);
    pthread_mutex_init(&write_mutex, NULL);
    
    printf("========== Reader-Writer Problem using Mutex ==========\n");
    printf("Number of Readers: %d\n", NUM_READERS);
    printf("Number of Writers: %d\n\n", NUM_WRITERS);
    
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Wait for all threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    // Destroy mutexes
    pthread_mutex_destroy(&read_mutex);
    pthread_mutex_destroy(&write_mutex);
    
    printf("\nAll operations completed successfully!\n");
    printf("Final data value: %d\n", shared_data);
    
    return 0;
}

/* 
Compilation: gcc 19_reader_writer_mutex.c -o rw_mutex -lpthread
Execution: ./rw_mutex
*/
