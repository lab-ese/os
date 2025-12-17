#include <stdio.h>
#include <stdbool.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int deadline;
    int remaining_time;
    bool is_completed;
} Task;

void sortByDeadline(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].deadline > tasks[j + 1].deadline) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n;
    int current_time = 0;
    bool schedulable = true;
    
    printf("========== Earliest Deadline First (EDF) Scheduling ==========\n\n");
    
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d:\n", i + 1);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Deadline: ");
        scanf("%d", &tasks[i].deadline);
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].is_completed = false;
    }
    
    printf("\n========== Schedule ==========\n");
    printf("%-10s %-10s %-15s %-10s %-10s %-15s\n", 
           "Time", "Task", "Exec Time", "Deadline", "Remaining", "Status");
    printf("--------------------------------------------------------------------------------\n");
    
    while (true) {
        // Find task with earliest deadline that is not completed
        int earliest = -1;
        int min_deadline = 99999;
        
        for (int i = 0; i < n; i++) {
            if (!tasks[i].is_completed && tasks[i].deadline < min_deadline) {
                min_deadline = tasks[i].deadline;
                earliest = i;
            }
        }
        
        if (earliest == -1) {
            break; // All tasks completed
        }
        
        // Execute task for 1 time unit
        printf("%-10d %-10d %-15d %-10d %-10d ", 
               current_time, tasks[earliest].id, 
               tasks[earliest].execution_time,
               tasks[earliest].deadline,
               tasks[earliest].remaining_time);
        
        tasks[earliest].remaining_time--;
        current_time++;
        
        if (tasks[earliest].remaining_time == 0) {
            tasks[earliest].is_completed = true;
            printf("%-15s\n", "COMPLETED");
            
            if (current_time > tasks[earliest].deadline) {
                printf("*** Task %d MISSED deadline! ***\n", tasks[earliest].id);
                schedulable = false;
            }
        } else {
            printf("%-15s\n", "RUNNING");
        }
    }
    
    printf("\n========== Results ==========\n");
    printf("Total Time: %d\n", current_time);
    
    if (schedulable) {
        printf("Status: All tasks met their deadlines! ✓\n");
    } else {
        printf("Status: Some tasks missed their deadlines! ✗\n");
    }
    
    printf("\nTask Summary:\n");
    printf("%-10s %-15s %-10s\n", "Task", "Exec Time", "Deadline");
    printf("--------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("T%-9d %-15d %-10d\n", 
               tasks[i].id, tasks[i].execution_time, tasks[i].deadline);
    }
    
    return 0;
}

/*
Example Input:
Tasks: 3
Task 1: Execution=2, Deadline=5
Task 2: Execution=3, Deadline=7
Task 3: Execution=1, Deadline=3

EDF schedules tasks dynamically based on earliest deadline
*/
