#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m; // n = processes, m = resources
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int safe_sequence[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int count = 0;
    
    // Initialize work with available
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    while (count < n) {
        bool found = false;
        
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                
                // Check if need <= work
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // Add allocated resources to work
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        if (!found) {
            return false; // System is not in safe state
        }
    }
    
    return true;
}

void displayMatrices() {
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMax Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    printf("\nAvailable Resources: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int main() {
    int safe_sequence[MAX_PROCESSES];
    
    printf("========== Banker's Algorithm - Deadlock Avoidance ==========\n\n");
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("\nEnter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    calculateNeed();
    displayMatrices();
    
    printf("\n========== Safety Algorithm ==========\n");
    
    if (isSafe(safe_sequence)) {
        printf("\nSystem is in SAFE state!\n");
        printf("\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in UNSAFE state!\n");
        printf("Deadlock may occur!\n");
    }
    
    return 0;
}

/*
Example Input:
Processes: 5
Resources: 3

Allocation:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Max:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Available: 3 3 2

Expected Output: Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2
*/
