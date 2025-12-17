#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    
    for (int i = 0; i < 3; i++) {
        // Thinking
        printf("Philosopher %d: Thinking...\n", id);
        sleep(1);
        
        // Pick up chopsticks (avoid deadlock by picking lower numbered first)
        if (left < right) {
            sem_wait(&chopsticks[left]);
            printf("Philosopher %d: Picked up left chopstick %d\n", id, left);
            sem_wait(&chopsticks[right]);
            printf("Philosopher %d: Picked up right chopstick %d\n", id, right);
        } else {
            sem_wait(&chopsticks[right]);
            printf("Philosopher %d: Picked up right chopstick %d\n", id, right);
            sem_wait(&chopsticks[left]);
            printf("Philosopher %d: Picked up left chopstick %d\n", id, left);
        }
        
        // Eating
        printf("Philosopher %d: EATING...\n", id);
        sleep(2);
        
        // Put down chopsticks
        sem_post(&chopsticks[left]);
        printf("Philosopher %d: Put down left chopstick %d\n", id, left);
        sem_post(&chopsticks[right]);
        printf("Philosopher %d: Put down right chopstick %d\n", id, right);
    }
    
    printf("Philosopher %d: Finished dining\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    
    // Initialize semaphores for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    
    printf("========== Dining Philosophers Problem using Semaphores ==========\n");
    printf("Number of Philosophers: %d\n", NUM_PHILOSOPHERS);
    printf("Deadlock Prevention: Resource ordering (picking lower numbered chopstick first)\n\n");
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    
    // Wait for all philosophers
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }
    
    printf("\nAll philosophers finished dining successfully!\n");
    
    return 0;
}

/* 
Compilation: gcc 20_dining_philosophers_semaphore.c -o dp_sem -lpthread
Execution: ./dp_sem
*/
