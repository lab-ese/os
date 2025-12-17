#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void printGanttChart(int gantt_pid[], int gantt_time[], int gantt_size) {
    printf("\nGantt Chart:\n");
    
    printf(" ");
    for (int i = 0; i < gantt_size; i++) {
        printf("----");
    }
    printf("\n|");
    
    for (int i = 0; i < gantt_size; i++) {
        if (gantt_pid[i] == -1)
            printf("IDLE|");
        else
            printf("P%d |", gantt_pid[i]);
    }
    printf("\n ");
    
    for (int i = 0; i < gantt_size; i++) {
        printf("----");
    }
    printf("\n");
    
    for (int i = 0; i <= gantt_size; i++) {
        printf("%-4d", gantt_time[i]);
    }
    printf("\n");
}

void calculateTimes(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int gantt_pid[1000];
    int gantt_time[1000];
    int gantt_size = 0;
    
    gantt_time[0] = 0;
    
    while (completed < n) {
        int highest_priority = -1;
        int max_priority = 99999;
        
        // Find process with highest priority
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 &&
                processes[i].priority < max_priority) {
                max_priority = processes[i].priority;
                highest_priority = i;
            }
        }
        
        if (highest_priority == -1) {
            gantt_pid[gantt_size] = -1;
            current_time++;
            gantt_time[gantt_size + 1] = current_time;
            gantt_size++;
        } else {
            if (gantt_size == 0 || gantt_pid[gantt_size - 1] != processes[highest_priority].pid) {
                gantt_pid[gantt_size] = processes[highest_priority].pid;
                gantt_time[gantt_size] = current_time;
                gantt_size++;
            }
            
            processes[highest_priority].remaining_time--;
            current_time++;
            
            if (processes[highest_priority].remaining_time == 0) {
                processes[highest_priority].completion_time = current_time;
                processes[highest_priority].turnaround_time = processes[highest_priority].completion_time - processes[highest_priority].arrival_time;
                processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - processes[highest_priority].burst_time;
                completed++;
            }
        }
    }
    
    gantt_time[gantt_size] = current_time;
    printGanttChart(gantt_pid, gantt_time, gantt_size);
}

void printResults(Process processes[], int n) {
    float total_wt = 0, total_tat = 0;
    
    printf("\n%-10s %-15s %-15s %-10s %-15s %-18s %-15s\n", 
           "Process", "Arrival Time", "Burst Time", "Priority", "Completion Time", "Turnaround Time", "Waiting Time");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%-9d %-15d %-15d %-10d %-15d %-18d %-15d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
        
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }
    
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("\n========== Priority Scheduling Preemptive ==========\n");
    calculateTimes(processes, n);
    printResults(processes, n);
    
    return 0;
}
