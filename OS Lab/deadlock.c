#include<stdio.h>
#include<stdlib.h>

#define p 5
#define r 3

void deadlock(int proc[],int max[][r],int alloc[][r],int avail[])
{
    int count = 0;
    int finished[p] = {0};
    int deadlocked[p] = {0};
    int need[p][r];
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < r ;j++)
            need[i][j] = max[i][j] = alloc[i][j];
    }
    int work[r];
    for(int j = 0; j < r ;j++)
        work[j] = avail[j];

    while(count < p)
    {
        int found = 0;
        for(int i = 0; i < p; i++)
        {
            if(finished[i] == 0)
            {
                int j;
                for(j = 0; j < r;j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }
                if(j==r)
                {
                    found = 1;
                    for (int k = 0; k < r; k++)
                        work[k] += alloc[i][k];
                    finished[i] = 1;
                    count++;
                }
            }
            
        }
        if(found == 0)
        {
            printf("System is in deadlock state due to the following processes: \n");
            for(int i = 0; i < p;i++)
            {
                if(finished[i] == 0)
                {
                    deadlocked[i] = 1;
                    printf("Process %d\n", i);
                }
            }
            return;
        }
    }
    printf("No deadlock detected.\n");
}

int main() {
    int proc[] = {0, 1, 2, 3, 4}; // Process IDs
    int avail[] = {3, 3, 2}; // Available resources

    int max[p][r] = { 
        {7, 5, 3},  
        {3, 2, 2},  
        {9, 0, 2},  
        {2, 2, 2},  
        {4, 3, 3}   
    };

    int alloc[p][r] = { 
        {0, 1, 0},  
        {2, 0, 0},  
        {3, 0, 2},  
        {2, 1, 1},  
        {0, 0, 2}  
    };

    deadlock(proc, max, alloc, avail);

    return 0;
}