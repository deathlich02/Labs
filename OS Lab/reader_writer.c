#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

sem_t mutex;
sem_t rw_mutex;
int read_count = 0;

void* reader(void* param)
{
    int rid = *((int*)param);

    sem_wait(&mutex);
    read_count += 1;
    if(read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);

    printf("%d is reading... \n",rid);
    sleep(1);

    sem_wait(&mutex);
    read_count -= 1;
    if(read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex);

    pthread_exit(NULL);
}

void* writer(void* param)
{
    int wid = *((int*)param);

    sem_wait(&rw_mutex);
    printf("%d is writing... \n", wid);
    sleep(1);
    sem_post(&rw_mutex);

    pthread_exit(NULL);
}

int main()
{
    pthread_t readers[5],writers[3];
    int rids[5],wids[3];

    sem_init(&rw_mutex,0,1);
    sem_init(&mutex,0,1);

    for(int i = 0; i < 5; i++)
    {
        rids[i] = i+1;
        pthread_create(&readers[i],NULL,reader,&rids[i]);
    }
    for(int i = 0; i < 5; i++)
    {
        wids[i] = i+1;
        pthread_create(&writers[i],NULL,writer,&wids[i]);
    }
    for(int i = 0; i < 3; i++)
        pthread_join(readers[i],NULL);
    
    for(int i = 0; i < 5; i++)
        pthread_join(writers[i],NULL);
    
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;

}