#include<stdio.h>

typedef struct{
	int pid;
	int at;
	int bt;
	int ct;
	int wt;
	int tat;
}process;

void sort_proc(process processes[], int n)
{
	process temp;
	for(int i = 0;i < n-1;i++)
	{
		for(int j = i+1; j < n;j++)
		{
			if(processes[i].at > processes[j].at)
			{
				temp = processes[i];
				processes[i] = processes[j];
				processes[j] = temp;
			}
		}
	}
}

int main()
{
	int n = 4;
	process processes[4] = {
        {1, 0, 8, 0, 0, 0}, // Process 1: pid=1, at=0, bt=8
        {2, 1, 4, 0, 0, 0}, // Process 2: pid=2, at=1, bt=4
        {3, 2, 9, 0, 0, 0}, // Process 3: pid=3, at=2, bt=9
        {4, 3, 5, 0, 0, 0}  // Process 4: pid=4, at=3, bt=5
    };
	
	sort_proc(processes, n);
	
	int current_time = 0;
	int completed = 0;
	int min = -1;
	int tot_wt = 0;
	int tot_tat = 0;
	
	while(completed != n)
	{
		min = -1;
		int min_bt = 1000;
		
		for(int i = 0;i < n;i++)
		{
			if(processes[i].at <= current_time && processes[i].ct == 0)
			{
				if(processes[i].bt <= min_bt)
				{
					min_bt = processes[i].bt;
					min = i;
				}
			}
		}
		if(min != -1)
		{
			current_time += processes[min].bt;
			completed += 1;
			processes[min].ct = current_time;
			processes[min].tat = current_time - processes[min].at;
			processes[min].wt = processes[min].tat - processes[min].bt;
			tot_tat += processes[min].tat;
			tot_wt += processes[min].wt;
		}
		else
			current_time++;
	}
	printf("\nAverage Waiting Time: %.2f\n", (float)tot_wt / n);
    	printf("Average Turnaround Time: %.2f\n", (float)tot_tat / n);
    	
    	return 0;
   }