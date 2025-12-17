#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

void displayFrames(int frames[], int num_frames) {
    printf("Frames: [");
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("]\n");
}

int findOptimal(int pages[], int frames[], int num_frames, int current_index, int n) {
    int farthest = current_index;
    int replace_index = 0;
    
    for (int i = 0; i < num_frames; i++) {
        int next_use = -1;
        
        // Find next occurrence of this frame page
        for (int j = current_index + 1; j < n; j++) {
            if (pages[j] == frames[i]) {
                next_use = j;
                break;
            }
        }
        
        if (next_use == -1) {
            // Page will never be used, replace it
            return i;
        }
        
        if (next_use > farthest) {
            farthest = next_use;
            replace_index = i;
        }
    }
    
    return replace_index;
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int n, num_frames;
    int page_faults = 0, page_hits = 0;
    int frame_count = 0;
    
    printf("========== Optimal Page Replacement Algorithm ==========\n\n");
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter number of frames: ");
    scanf("%d", &num_frames);
    
    // Initialize frames
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
    
    printf("\n%-10s %-20s %-10s\n", "Page", "Frames", "Status");
    printf("----------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;
        
        // Check if page is already in frame
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = true;
                page_hits++;
                break;
            }
        }
        
        printf("%-10d ", page);
        
        if (!found) {
            // Page fault
            if (frame_count < num_frames) {
                // Empty frame available
                frames[frame_count++] = page;
            } else {
                // Find optimal page to replace
                int optimal_index = findOptimal(pages, frames, num_frames, i, n);
                frames[optimal_index] = page;
            }
            
            page_faults++;
            displayFrames(frames, num_frames);
            printf(" FAULT\n");
        } else {
            displayFrames(frames, num_frames);
            printf(" HIT\n");
        }
    }
    
    printf("\n========== Results ==========\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", page_hits);
    printf("Hit Ratio: %.2f%%\n", (float)page_hits / n * 100);
    printf("Fault Ratio: %.2f%%\n", (float)page_faults / n * 100);
    printf("\nNote: Optimal algorithm gives minimum page faults.\n");
    
    return 0;
}

/*
Example Input:
Pages: 12
Reference String: 7 0 1 2 0 3 0 4 2 3 0 3
Frames: 3

Expected Output:
Page Faults: 6 (optimal)
*/
