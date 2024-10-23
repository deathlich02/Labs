#include<stdio.h>
#include<stdlib.h>

#define p 5
#define r 3
/*
    avail, alloc, max, need
*/
void issafe(int proc[], int avail[], int max[][r],int alloc[][r])
{
    int need[p][r],work[r];
    for(int i = 0; i < p; i++)
    {
        for(int j = 0;j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    for(int j = 0;j < r; j++)
            work[j] = avail[j];

    int safeseq[p];
    int finished[p] = {0};
    int count = 0;
    while(count < p)
    {
        int found = 0;
        for(int i = 0 ; i < p; i++)
        {
            if(finished[i] == 0)
            {
                int j;
                for(j = 0; j <r;j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }
                if(j == r)
                {
                    found = 1;
                    for(int k = 0; k < r;k++)
                        work[k] += alloc[i][k];
                    safeseq[count++] = i;
                    finished[i] = 1;
                } 
            }
        }
        if(found != 1)
        {
            printf("Not safe \n");
            return;
        }

    }
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("%d ", safeseq[i]);
    }
    printf("\n");

    return;

}
int main()
{
    int proc[] = {0, 1, 2, 3, 4}; 
    int avail[] = {3, 3, 2};

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

    issafe(proc, avail, max, alloc);

    return 0;
}
