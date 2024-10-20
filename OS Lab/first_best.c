#include <stdio.h>
#include <stdlib.h>

#define MAX 100  

typedef struct {
    int size;
    int isFree; 
} Block;

Block memory[MAX];  

void init(int blockSizes[], int n) {
    for (int i = 0; i < n; i++) {
        memory[i].size = blockSizes[i];
        memory[i].isFree = 1;
    }
}

void firstFit(int processSize, int n) {
    for (int i = 0; i < n; i++) {
        if (memory[i].isFree && memory[i].size >= processSize) {
            memory[i].isFree = 0;  
            printf("Process of size %d allocated at block %d\n", processSize, i);
            return;
        }
    }
    printf("Process of size %d could not be allocated using First Fit\n", processSize);
}

void bestFit(int processSize, int n) {
    int bestIndex = -1;
    for (int i = 0; i < n; i++) {
        if (memory[i].isFree && memory[i].size >= processSize) {
            if (bestIndex == -1 || memory[i].size < memory[bestIndex].size) {
                bestIndex = i;
            }
        }
    }
    if (bestIndex != -1) {
        memory[bestIndex].isFree = 0;  
        printf("Process of size %d allocated at block %d\n", processSize, bestIndex);
    } else {
        printf("Process of size %d could not be allocated using Best Fit\n", processSize);
    }
}

void deallocate(int blockIndex, int n) {
    if (blockIndex < 0 || blockIndex >= n) {
        printf("Invalid block index\n");
        return;
    }
    if (!memory[blockIndex].isFree) {
        memory[blockIndex].isFree = 1;  // Mark block as free
        printf("Block %d deallocated\n", blockIndex);
    } else {
        printf("Block %d is already free\n", blockIndex);
    }
}

int main() {
    int blockSizes[] = {100, 500, 200, 300, 600};  // mem block sizes
    int n = sizeof(blockSizes) / sizeof(blockSizes[0]);

    init(blockSizes, n);

    // Simulate processes
    printf("First Fit Allocation:\n");
    firstFit(212, n);  
    firstFit(417, n); 
    firstFit(112, n);  
    firstFit(426, n);  

    printf("\nDeallocate block 1:\n");
    deallocate(1, n);  

    printf("\nBest Fit Allocation:\n");
    bestFit(212, n);   
    bestFit(417, n);   
    bestFit(112, n);   
    bestFit(426, n);   

    return 0;
}
