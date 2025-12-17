#include <stdio.h>
#include <stdbool.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int period;
    float utilization;
    int remaining_time;
    int next_deadline;
} Task;

// Rate Monotonic Scheduling
void rateMonotonicScheduling(Task tasks[], int n, int total_time) {
    printf("\n========== Rate Monotonic Scheduling ==========\n");
    printf("Priority: Shorter period = Higher priority\n\n");
    
    // Sort by period (shorter period = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].period > tasks[j + 1].period) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    
    printf("Schedule (Time 0 to %d):\n", total_time);
    printf("%-10s %-10s\n", "Time", "Task");
    printf("----------------------\n");
    
    for (int t = 0; t < total_time; t++) {
        // Release tasks at their periods
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = t + tasks[i].period;
            }
        }
        
        // Find highest priority task that needs execution
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                selected = i;
                break;
            }
        }
        
        if (selected != -1) {
            printf("%-10d T%-9d\n", t, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("%-10d %-10s\n", t, "IDLE");
        }
    }
}

// Least Laxity First Scheduling
void leastLaxityFirst(Task tasks[], int n, int total_time) {
    printf("\n========== Least Laxity First Scheduling ==========\n");
    printf("Laxity = Deadline - Current Time - Remaining Time\n\n");
    
    // Initialize
    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_deadline = tasks[i].period;
    }
    
    printf("Schedule (Time 0 to %d):\n", total_time);
    printf("%-10s %-10s %-10s\n", "Time", "Task", "Laxity");
    printf("--------------------------------\n");
    
    for (int t = 0; t < total_time; t++) {
        // Release tasks at their periods
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0 && t > 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = t + tasks[i].period;
            }
        }
        
        // Find task with minimum laxity
        int selected = -1;
        int min_laxity = 99999;
        
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                int laxity = tasks[i].next_deadline - t - tasks[i].remaining_time;
                if (laxity < min_laxity) {
                    min_laxity = laxity;
                    selected = i;
                }
            }
        }
        
        if (selected != -1) {
            printf("%-10d T%-9d %-10d\n", t, tasks[selected].id, min_laxity);
            tasks[selected].remaining_time--;
        } else {
            printf("%-10d %-10s %-10s\n", t, "IDLE", "-");
        }
    }
}

bool checkSchedulability(Task tasks[], int n) {
    // Calculate total utilization
    float total_utilization = 0;
    for (int i = 0; i < n; i++) {
        total_utilization += tasks[i].utilization;
    }
    
    // Liu & Layland bound: U <= n * (2^(1/n) - 1)
    float bound = n * (1.0 - 1.0 / (1 << n));
    
    printf("Total Utilization: %.2f\n", total_utilization);
    printf("Schedulability Bound: %.2f\n", bound);
    
    if (total_utilization <= 1.0) {
        printf("System is schedulable (U <= 1.0)\n");
        return true;
    } else {
        printf("System may not be schedulable (U > 1.0)\n");
        return false;
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n, choice;
    
    printf("========== Real-Time Scheduling Algorithms ==========\n\n");
    
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d:\n", i + 1);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        tasks[i].utilization = (float)tasks[i].execution_time / tasks[i].period;
    }
    
    printf("\n========== Schedulability Test ==========\n");
    bool schedulable = checkSchedulability(tasks, n);
    
    if (!schedulable) {
        printf("\nWarning: System may not meet all deadlines!\n");
    }
    
    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Rate Monotonic Scheduling (RMS)\n");
    printf("2. Least Laxity First (LLF)\n");
    printf("3. Both\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    int total_time = 20; // Simulate for 20 time units
    
    // Make copies for different algorithms
    Task tasks_rms[MAX_TASKS];
    Task tasks_llf[MAX_TASKS];
    
    for (int i = 0; i < n; i++) {
        tasks_rms[i] = tasks[i];
        tasks_llf[i] = tasks[i];
    }
    
    switch (choice) {
        case 1:
            rateMonotonicScheduling(tasks_rms, n, total_time);
            break;
        case 2:
            leastLaxityFirst(tasks_llf, n, total_time);
            break;
        case 3:
            rateMonotonicScheduling(tasks_rms, n, total_time);
            leastLaxityFirst(tasks_llf, n, total_time);
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}

/*
Example Input:
Tasks: 3
Task 1: Execution=1, Period=4
Task 2: Execution=2, Period=6
Task 3: Execution=2, Period=8

Rate Monotonic: Assigns priorities based on period (shorter period = higher priority)
Least Laxity First: Schedules based on laxity (deadline - current time - remaining time)
*/
