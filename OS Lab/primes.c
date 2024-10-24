#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>  //for true and false

//find . -type f -name ".txt" | grep -E '/[^aeiouAEIOU][^/][0-9][^/]{2,}\.txt$’

int start = 2;
int end = 20;
bool is_prime(int n)
{
	if(n <= 1)
		return false;
	else
	{
		for(int i = 2; i*i <= n;i++)
		{
			if(n%i == 0)
				return false;
		}
		return true;
	}	
}
void* gen_prime(void* param)
{
	for(int i= start;i <= end;i++)
	{
		if(is_prime(i))
			printf("%d ",i);
	}
	pthread_exit(NULL);
}

void main()
{
	pthread_t thread;
	pthread_create(&thread, 0, &gen_prime, 0);
	pthread_join(thread,NULL);
}
