#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void printSequence(int sequence[], int n) {
    printf("Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d", sequence[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\n");
}

void printGanttChart(int sequence[], int n) {
    printf("\nGantt Chart:\n");
    
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n|");
    
    for (int i = 0; i < n; i++) {
        printf(" %4d  |", sequence[i]);
    }
    printf("\n ");
    
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n");
}

int main() {
    int requests[MAX_REQUESTS];
    int n, head;
    int total_seek_time = 0;
    
    printf("========== FCFS Disk Scheduling Algorithm ==========\n\n");
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    printf("Enter disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    printf("\n========== Processing Requests ==========\n");
    printf("Initial Head Position: %d\n\n", head);
    
    int sequence[MAX_REQUESTS + 1];
    sequence[0] = head;
    
    for (int i = 0; i < n; i++) {
        sequence[i + 1] = requests[i];
    }
    
    printf("%-15s %-15s %-20s\n", "From", "To", "Seek Distance");
    printf("--------------------------------------------------------\n");
    
    int current = head;
    for (int i = 0; i < n; i++) {
        int seek_distance = abs(requests[i] - current);
        total_seek_time += seek_distance;
        
        printf("%-15d %-15d %-20d\n", current, requests[i], seek_distance);
        current = requests[i];
    }
    
    printf("\n");
    printSequence(sequence, n + 1);
    printGanttChart(sequence, n + 1);
    
    printf("\n========== Results ==========\n");
    printf("Total Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);
    
    return 0;
}

/*
Example Input:
Requests: 8
Request Queue: 98 183 37 122 14 124 65 67
Initial Head: 53

Expected Output:
Seek Sequence: 53 -> 98 -> 183 -> 37 -> 122 -> 14 -> 124 -> 65 -> 67
Total Seek Time: 640
*/
