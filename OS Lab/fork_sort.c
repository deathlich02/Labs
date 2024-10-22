#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX 100

void bubble(char strings[MAX][MAX], int n) {
    char temp[MAX];
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(strcmp(strings[j], strings[j+1]) > 0) {
                strcpy(temp, strings[j]);
                strcpy(strings[j], strings[j+1]);
                strcpy(strings[j+1], temp);
            }
        }
    }
}

void selection(char strings[MAX][MAX], int n) {
    int min;
    char temp[MAX];
    for(int i = 0; i < n-1; i++) {
        min = i;
        for(int j = i+1; j < n; j++) {
            if(strcmp(strings[j], strings[min]) < 0) {
                min = j;
            }
        }
        strcpy(temp, strings[min]);
        strcpy(strings[min], strings[i]);
        strcpy(strings[i], temp);
    }
}

int main() {
    char strings[MAX][MAX], strings_copy[MAX][MAX];
    int n;
    pid_t pid1, pid2;

    printf("Enter the number of words: \n");
    scanf("%d", &n);
    printf("Enter the words: \n");
    for(int i = 0; i < n; i++) {
       scanf("%s", strings[i]);
       strcpy(strings_copy[i], strings[i]);  // Make a copy of the original strings
    }

    // First child process for bubble sort
    pid1 = fork();
    if(pid1 == 0) {
        bubble(strings, n);
        printf("Bubble Sorted words are:\n");
        for(int i = 0; i < n; i++)
            printf("%s\n", strings[i]);  // Print each word with a newline
        exit(0);
    }
    else if(pid1 < 0) {
        perror("Fork failed\n");
        return 0;
    }

    // Second child process for selection sort
    pid2 = fork();
    if(pid2 == 0) {
        selection(strings_copy, n);  // Use the copied array for selection sort
        printf("Selection Sorted words are:\n");
        for(int i = 0; i < n; i++)
            printf("%s\n", strings_copy[i]);  // Print each word with a newline
        exit(0);
    }
    else if(pid2 < 0) {
        perror("Fork failed\n");
        return 0;
    }

    // Parent process waits for both child processes to finish
    int status;
    waitpid(pid1, &status, 0);  // Wait for first child
    waitpid(pid2, &status, 0);  // Wait for second child

    return 0;
}
