#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
} Process;

void printGanttChart(int gantt_pid[], int gantt_time[], int gantt_size) {
    printf("\nGantt Chart:\n");
    
    // Print top border
    printf(" ");
    for (int i = 0; i < gantt_size; i++) {
        printf("--------");
    }
    printf("\n|");
    
    // Print process IDs
    for (int i = 0; i < gantt_size; i++) {
        if (gantt_pid[i] == -1)
            printf(" IDLE  |");
        else
            printf("  P%d   |", gantt_pid[i]);
    }
    printf("\n ");
    
    // Print bottom border
    for (int i = 0; i < gantt_size; i++) {
        printf("--------");
    }
    printf("\n");
    
    // Print timeline
    for (int i = 0; i <= gantt_size; i++) {
        printf("%-8d", gantt_time[i]);
    }
    printf("\n");
}

void calculateTimes(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int gantt_pid[100];
    int gantt_time[100];
    int gantt_size = 0;
    
    gantt_time[0] = 0;
    
    while (completed < n) {
        int shortest = -1;
        int min_burst = 99999;
        
        // Find process with shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].is_completed && 
                processes[i].arrival_time <= current_time &&
                processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            // CPU is idle
            gantt_pid[gantt_size] = -1;
            current_time++;
            gantt_time[gantt_size + 1] = current_time;
            gantt_size++;
        } else {
            // Execute process
            gantt_pid[gantt_size] = processes[shortest].pid;
            current_time += processes[shortest].burst_time;
            gantt_time[gantt_size + 1] = current_time;
            gantt_size++;
            
            processes[shortest].completion_time = current_time;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            processes[shortest].is_completed = true;
            completed++;
        }
    }
    
    printGanttChart(gantt_pid, gantt_time, gantt_size);
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
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].is_completed = false;
    }
    
    printf("\n========== SJF Non-Preemptive CPU Scheduling ==========\n");
    calculateTimes(processes, n);
    printResults(processes, n);
    
    return 0;
}
