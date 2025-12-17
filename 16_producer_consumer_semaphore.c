#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg) {
    int item;
    int id = *((int *)arg);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100;
        
        sem_wait(&empty);
        sem_wait(&mutex);
        
        // Critical Section
        buffer[in] = item;
        printf("Producer %d: Produced %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        
        sem_post(&mutex);
        sem_post(&full);
        
        sleep(1);
    }
    
    return NULL;
}

void *consumer(void *arg) {
    int item;
    int id = *((int *)arg);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        
        // Critical Section
        item = buffer[out];
        printf("Consumer %d: Consumed %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        
        sem_post(&mutex);
        sem_post(&empty);
        
        sleep(2);
    }
    
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    int prod_id = 1, cons_id = 1;
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    
    printf("========== Producer-Consumer Problem using Semaphores ==========\n");
    printf("Buffer Size: %d\n", BUFFER_SIZE);
    printf("Number of items to produce/consume: %d\n\n", NUM_ITEMS);
    
    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, &prod_id);
    pthread_create(&cons_thread, NULL, consumer, &cons_id);
    
    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    printf("\nAll operations completed successfully!\n");
    
    return 0;
}

/* 
Compilation: gcc 16_producer_consumer_semaphore.c -o pc_sem -lpthread
Execution: ./pc_sem
*/
