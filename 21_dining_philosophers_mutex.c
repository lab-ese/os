#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

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
            pthread_mutex_lock(&chopsticks[left]);
            printf("Philosopher %d: Picked up left chopstick %d\n", id, left);
            pthread_mutex_lock(&chopsticks[right]);
            printf("Philosopher %d: Picked up right chopstick %d\n", id, right);
        } else {
            pthread_mutex_lock(&chopsticks[right]);
            printf("Philosopher %d: Picked up right chopstick %d\n", id, right);
            pthread_mutex_lock(&chopsticks[left]);
            printf("Philosopher %d: Picked up left chopstick %d\n", id, left);
        }
        
        // Eating
        printf("Philosopher %d: EATING...\n", id);
        sleep(2);
        
        // Put down chopsticks
        pthread_mutex_unlock(&chopsticks[left]);
        printf("Philosopher %d: Put down left chopstick %d\n", id, left);
        pthread_mutex_unlock(&chopsticks[right]);
        printf("Philosopher %d: Put down right chopstick %d\n", id, right);
    }
    
    printf("Philosopher %d: Finished dining\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    
    // Initialize mutexes for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }
    
    printf("========== Dining Philosophers Problem using Mutex ==========\n");
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
    
    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    
    printf("\nAll philosophers finished dining successfully!\n");
    
    return 0;
}

/* 
Compilation: gcc 21_dining_philosophers_mutex.c -o dp_mutex -lpthread
Execution: ./dp_mutex
*/
