#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


/*
producer waitfs for an empty slot, then locks mutex and produces an item and puts it into the buff, then it unlocks the buffer and 
posts that a slot is now full (ready to be consumed)
consumer waits for a full slot, then locks mutex and consumes an item, then it unlocks mutex and posts that a slot is now
empty(ready to produce)
*/

#define buff 5


int in = 0;
int out = 0;
int buffer[buff];

sem_t empty;
sem_t full;
pthread_mutex_t mutex; 

void* producer(void* param)
{
    while(1)
    {
        int item;
        item = (rand() % 100);

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        in = (in+1)&buff;
        printf("Producer produced: %d \n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(rand()%2);
    }
}

void* consumer(void* param)
{
    while(1)
    {
        int item;
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d \n",item);
        out = (out+1)%buff;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand()%2);
    }

}

int main() {
    pthread_t prod, cons;

    // Initialize the semaphores
    sem_init(&empty, 0, buff); // Initially, all slots are empty
    sem_init(&full, 0, 0); // Initially, no items are in the buffer
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for the threads to complete (they won't in this example)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}