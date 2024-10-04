#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#define MAX_STRINGS 100
#define MAX_LENGTH 100
void bubbleSort(char arr[][MAX_LENGTH], int n) {
int i, j;
char temp[MAX_LENGTH];
for (i = 0; i < n-1; i++) {
for (j = 0; j < n-i-1; j++) {
if (strcmp(arr[j], arr[j+1]) > 0) {
strcpy(temp, arr[j]);
strcpy(arr[j], arr[j+1]);
strcpy(arr[j+1], temp);
}
}
}
}
void selectionSort(char arr[][MAX_LENGTH], int n) {
int i, j, min_idx;
char temp[MAX_LENGTH];
for (i = 0; i < n-1; i++) {
min_idx = i;
for (j = i+1; j < n; j++) {
if (strcmp(arr[j], arr[min_idx]) < 0) {
min_idx = j;
}
}
strcpy(temp, arr[min_idx]);
strcpy(arr[min_idx], arr[i]);
strcpy(arr[i], temp);
}
}
int main(void) {
int n;
pid_t pid1, pid2;
// Read number of strings
printf("Enter the number of strings: ");
scanf("%d", &n);
// Read the strings
char strings[MAX_STRINGS][MAX_LENGTH];
printf("Enter the strings:\n");
for (int i = 0; i < n; i++) {
scanf("%s", strings[i]);
}
// Fork the first child process
pid1 = fork();
if (pid1 == 0) {
// Child 1 process - perform bubble sort
bubbleSort(strings, n);
printf("Bubble sorted strings:\n");
for (int i = 0; i < n; i++) {
printf("%s\n", strings[i]);
}
exit(0);
} else if (pid1 < 0) {
// Fork failed
perror("Fork failed for child 1");
return 1;
}
// Fork the second child process
pid2 = fork();
if (pid2 == 0) {
// Child 2 process - perform selection sort
selectionSort(strings, n);
printf("Selection sorted strings:\n");
for (int i = 0; i < n; i++) {
printf("%s\n", strings[i]);
}
exit(0);
} else if (pid2 < 0) {
// Fork failed
perror("Fork failed for child 2");
return 1;
}
// Parent process waits for one child to terminate
int status;
wait(&status); // Wait for one child to finish
return 0;
}