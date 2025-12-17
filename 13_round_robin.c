#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void printGanttChart(int gantt_pid[], int gantt_time[], int gantt_size) {
    printf("\nGantt Chart:\n");
    
    printf(" ");
    for (int i = 0; i < gantt_size; i++) {
        printf("--------");
    }
    printf("\n|");
    
    for (int i = 0; i < gantt_size; i++) {
        if (gantt_pid[i] == -1)
            printf(" IDLE  |");
        else
            printf("  P%d   |", gantt_pid[i]);
    }
    printf("\n ");
    
    for (int i = 0; i < gantt_size; i++) {
        printf("--------");
    }
    printf("\n");
    
    for (int i = 0; i <= gantt_size; i++) {
        printf("%-8d", gantt_time[i]);
    }
    printf("\n");
}

void calculateTimes(Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int completed = 0;
    int gantt_pid[1000];
    int gantt_time[1000];
    int gantt_size = 0;
    
    int queue[100];
    int front = 0, rear = 0;
    bool in_queue[100] = {false};
    
    gantt_time[0] = 0;
    
    // Add first arrived process to queue
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }
    
    while (completed < n) {
        if (front == rear) {
            // Queue is empty, CPU idle
            gantt_pid[gantt_size] = -1;
            current_time++;
            gantt_time[gantt_size + 1] = current_time;
            gantt_size++;
            
            // Add newly arrived processes
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }
        
        int idx = queue[front++];
        in_queue[idx] = false;
        
        gantt_pid[gantt_size] = processes[idx].pid;
        gantt_time[gantt_size] = current_time;
        
        int exec_time = (processes[idx].remaining_time < time_quantum) ? 
                        processes[idx].remaining_time : time_quantum;
        
        processes[idx].remaining_time -= exec_time;
        current_time += exec_time;
        gantt_time[gantt_size + 1] = current_time;
        gantt_size++;
        
        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (!in_queue[i] && i != idx && 
                processes[i].arrival_time <= current_time && 
                processes[i].remaining_time > 0) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }
        
        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        } else {
            queue[rear++] = idx;
            in_queue[idx] = true;
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
    int n, time_quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);
    
    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("\n========== Round Robin CPU Scheduling (Time Quantum = %d) ==========\n", time_quantum);
    calculateTimes(processes, n, time_quantum);
    printResults(processes, n);
    
    return 0;
}
