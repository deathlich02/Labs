#include <stdio.h>
#include <limits.h>

// Structure to store process details
struct Process {
    int pid;         // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime;   // Burst time of the process
    int remainingTime; // Remaining time of the process (for preemption)
    int completionTime; // Completion time of the process
    int waitingTime; // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
    int isComplete;  // Completion flag
};

// Function to find the shortest remaining time process at a given time
int findNextProcess(struct Process processes[], int n, int currentTime) {
    int shortestProcessIndex = -1;
    int minRemainingTime = INT_MAX;
    
    // Traverse through all processes
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && !processes[i].isComplete && processes[i].remainingTime < minRemainingTime) {
            minRemainingTime = processes[i].remainingTime;
            shortestProcessIndex = i;
        }
    }
    return shortestProcessIndex;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initially, remaining time is burst time
        processes[i].isComplete = 0; // Mark the process as incomplete
    }
    
    int completedProcesses = 0;
    int currentTime = 0;

    // Loop until all processes are complete
    while (completedProcesses != n) {
        int shortestProcessIndex = findNextProcess(processes, n, currentTime);
        
        if (shortestProcessIndex == -1) {
            currentTime++; // No process is available, so increment the current time
            continue;
        }

        // Execute the process with the shortest remaining time
        processes[shortestProcessIndex].remainingTime--;
        currentTime++;

        // Check if the process has completed
        if (processes[shortestProcessIndex].remainingTime == 0) {
            processes[shortestProcessIndex].isComplete = 1;
            completedProcesses++;
            processes[shortestProcessIndex].completionTime = currentTime;
            processes[shortestProcessIndex].turnaroundTime = processes[shortestProcessIndex].completionTime - processes[shortestProcessIndex].arrivalTime;
            processes[shortestProcessIndex].waitingTime = processes[shortestProcessIndex].turnaroundTime - processes[shortestProcessIndex].burstTime;

            totalWaitingTime += processes[shortestProcessIndex].waitingTime;
            totalTurnaroundTime += processes[shortestProcessIndex].turnaroundTime;
        }
    }
    
    // Display the results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
