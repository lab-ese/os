#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_data = 0;
int read_count = 0;

sem_t mutex;        // For read_count
sem_t write_mutex;  // For writing

void *reader(void *arg) {
    int id = *((int *)arg);
    
    for (int i = 0; i < 3; i++) {
        // Entry section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_mutex);  // First reader locks writer
        }
        sem_post(&mutex);
        
        // Critical section - Reading
        printf("Reader %d: Read data = %d\n", id, shared_data);
        sleep(1);
        
        // Exit section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&write_mutex);  // Last reader unlocks writer
        }
        sem_post(&mutex);
        
        sleep(1);
    }
    
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    
    for (int i = 0; i < 3; i++) {
        // Entry section
        sem_wait(&write_mutex);
        
        // Critical section - Writing
        shared_data++;
        printf("Writer %d: Wrote data = %d\n", id, shared_data);
        sleep(2);
        
        // Exit section
        sem_post(&write_mutex);
        
        sleep(2);
    }
    
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);
    
    printf("========== Reader-Writer Problem using Semaphores ==========\n");
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
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    
    printf("\nAll operations completed successfully!\n");
    printf("Final data value: %d\n", shared_data);
    
    return 0;
}

/* 
Compilation: gcc 18_reader_writer_semaphore.c -o rw_sem -lpthread
Execution: ./rw_sem
*/
