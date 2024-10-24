#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_THREADS 4  // Number of threads to use

// Structure to hold the range for each thread
typedef struct {
    int start;
    int end;
} PrimeRange;

// Function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Function to be executed by each thread to find prime numbers in the range
void* find_primes(void* arg) {
    PrimeRange* range = (PrimeRange*) arg;
    printf("Thread working on range %d to %d\n", range->start, range->end);

    for (int num = range->start; num <= range->end; num++) {
        if (is_prime(num)) {
            printf("%d is prime\n", num);
        }
    }

    pthread_exit(NULL);
}

int main() {
    int start, end;
    printf("Enter the starting number: ");
    scanf("%d", &start);
    printf("Enter the ending number: ");
    scanf("%d", &end);

    // Calculate the range size for each thread
    int total_range = end - start + 1;
    int range_per_thread = total_range / MAX_THREADS;

    // Create an array of threads and ranges
    pthread_t threads[MAX_THREADS];
    PrimeRange ranges[MAX_THREADS];

    // Create threads to process each part of the range
    for (int i = 0; i < MAX_THREADS; i++) {
        ranges[i].start = start + i * range_per_thread;
        ranges[i].end = (i == MAX_THREADS - 1) ? end : (ranges[i].start + range_per_thread - 1);
        
        if (pthread_create(&threads[i], NULL, find_primes, (void*)&ranges[i])) {
            perror("Error creating thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}
