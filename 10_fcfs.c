#include <stdio.h>

// Structure to represent a process
typedef struct {
    int pid;          // Process ID
    int arrival_time; // Arrival Time
    int burst_time;   // Burst Time
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void printGanttChart(Process processes[], int n) {
    int i;
    
    printf("\nGantt Chart:\n");
    
    // Print top border
    printf(" ");
    for (i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n|");
    
    // Print process IDs
    for (i = 0; i < n; i++) {
        printf("  P%d   |", processes[i].pid);
    }
    printf("\n ");
    
    // Print bottom border
    for (i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n");
    
    // Print timeline
    printf("0");
    for (i = 0; i < n; i++) {
        printf("       %d", processes[i].completion_time);
    }
    printf("\n");
}

void calculateTimes(Process processes[], int n) {
    int current_time = 0;
    
    for (int i = 0; i < n; i++) {
        // If CPU is idle, jump to process arrival time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Calculate completion time
        processes[i].completion_time = current_time + processes[i].burst_time;
        
        // Calculate turnaround time = completion_time - arrival_time
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        
        // Calculate waiting time = turnaround_time - burst_time
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        
        current_time = processes[i].completion_time;
    }
}

void printResults(Process processes[], int n) {
    float total_wt = 0, total_tat = 0;
    
    printf("\n%-10s %-15s %-15s %-15s %-18s %-15s\n", 
           "Process", "Arrival Time", "Burst Time", "Completion Time", "Turnaround Time", "Waiting Time");
    printf("----------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%-9d %-15d %-15d %-15d %-18d %-15d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
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
    
    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    // Calculate times
    calculateTimes(processes, n);
    
    // Print results
    printf("\n========== FCFS CPU Scheduling ==========\n");
    printResults(processes, n);
    printGanttChart(processes, n);
    
    return 0;
}
