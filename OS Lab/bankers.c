#include <stdio.h>
void main()
{
    int row = 5, column = 3;
    int max[5][3] = {{7, 5, 3}, // P0 // MAX Matrix
                     {3, 2, 2}, // P1
                     {9, 0, 2}, // P2
                     {2, 2, 2}, // P3
                     {4, 3, 3}};
    ;
    int alloc[5][3] = {{0, 1, 0}, // P0 // Allocation Matrix
                       {2, 0, 0}, // P1
                       {3, 0, 2}, // P2
                       {2, 1, 1}, // P3
                       {0, 0, 2}};
    int available[3] = {3, 3, 2};
    int finished[5], answer[5];
    for (int i = 0; i < 5; i++)
    {
        finished[i] = 0;
    }
    int need[5][3];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    int index = 0, flag;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < row; j++)
        {
            flag = 0;
            for (int k = 0; k < column; k++)
            {
                if (finished[j] == 0)
                {
                    if (need[j][k] > available[k])
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag == 0 && finished[j] == 0)
            {
                answer[index] = j;
                index++;
                for (int x = 0; x < 3; x++)
                {
                    available[x] += alloc[j][x];
                }
                finished[j] = 1;
            }
        }
    }
    if (index < row - 1)
    {
        printf("\nSEQUENCE IS UNSAFE");
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            printf("P%d->", answer[i]);
        }
    }
}