#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

void *producer(void *arg) {
    int item;
    int id = *((int *)arg);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100;
        
        pthread_mutex_lock(&mutex);
        
        // Wait while buffer is full
        while (count == BUFFER_SIZE) {
            printf("Producer %d: Buffer full, waiting...\n", id);
            pthread_cond_wait(&not_full, &mutex);
        }
        
        // Add item to buffer
        buffer[count] = item;
        printf("Producer %d: Produced %d at position %d\n", id, item, count);
        count++;
        
        // Signal that buffer is not empty
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        
        sleep(1);
    }
    
    return NULL;
}

void *consumer(void *arg) {
    int item;
    int id = *((int *)arg);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);
        
        // Wait while buffer is empty
        while (count == 0) {
            printf("Consumer %d: Buffer empty, waiting...\n", id);
            pthread_cond_wait(&not_empty, &mutex);
        }
        
        // Remove item from buffer
        count--;
        item = buffer[count];
        printf("Consumer %d: Consumed %d from position %d\n", id, item, count);
        
        // Signal that buffer is not full
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        
        sleep(2);
    }
    
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    int prod_id = 1, cons_id = 1;
    
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
    
    printf("========== Producer-Consumer Problem using Mutex ==========\n");
    printf("Buffer Size: %d\n", BUFFER_SIZE);
    printf("Number of items to produce/consume: %d\n\n", NUM_ITEMS);
    
    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, &prod_id);
    pthread_create(&cons_thread, NULL, consumer, &cons_id);
    
    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    
    printf("\nAll operations completed successfully!\n");
    
    return 0;
}

/* 
Compilation: gcc 17_producer_consumer_mutex.c -o pc_mutex -lpthread
Execution: ./pc_mutex
*/
