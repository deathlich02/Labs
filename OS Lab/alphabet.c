#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main()
{
int shmid;
char *shared_mem;
char charp;
shmid = shmget((key_t)1234,1024,0666|IPC_CREAT);
pid_t pid = fork();
if(pid < 0)
perror("Fork failed \n");
else if(pid > 0)
{
shared_mem = (char*)shmat(shmid, NULL,0);
printf("Enter the character: \n");
scanf("%c", &charp);
*shared_mem = charp;
wait(NULL);
printf("Child's reply: %c \n", *shared_mem);
shmdt(shared_mem);
shmctl(shmid, IPC_RMID,NULL);
}
else
{
sleep(5);
shared_mem = (char*)shmat(shmid, NULL, 0);
printf("Char received from parent: %c \n", *shared_mem);
char charc = *shared_mem;
if(charc == 'z')
charc = 'a';
else if(charc == 'Z')
charc = 'A';
else
charc += 1;
*shared_mem = charc;
shmdt(shared_mem);
}
return 0;
}