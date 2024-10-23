#include <stdio.h>
#include<pthread.h>

#define max 100;
int sume,sumo;

typedef struct{
    int *arr;
    int size;
}thread_data;

void *even(void *param)
{
    thread_data* data = (thread_data *)param;
    for(int i = 0; i < data->size ;i++)
    {
        if((data->arr[i]%2) == 0)
            sume += data->arr[i];
    }
    printf("Sum of even numbers is: %d \n", sume);
    return NULL;
}

void *odd(void *param)
{
    thread_data* data = (thread_data *)param;
    for(int i = 0; i < data->size ;i++)
    {
        if((data->arr[i] % 2) != 0)
            sumo += data->arr[i];
    }
    printf("Sum of odd numbers is: %d \n", sumo);
    return NULL;
}

int main() 
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    thread_data data = {arr, size};
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, even, (void*)&data);
    pthread_create(&thread2, NULL, odd, (void*)&data);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}