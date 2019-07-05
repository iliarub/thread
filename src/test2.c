/*
 ============================================================================
 Name        : test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


int magazine[5];
pthread_mutex_t ml[5]={PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};


void init()
{
	srand(time(NULL));
	for(int i=0; i<5; i++)
	{
		magazine[i]=rand() % 200+900;
	}
}


void* buyer(void *ptr)
{
	int *buy;
	buy = (int*)ptr;
	int greed=100000;
	while(greed!=0)
	{
		int i=rand()%5;
		if(magazine[i])
		{
			if(!pthread_mutex_trylock(&ml[i]))
			{
					if(magazine[i]<greed)
				{
					greed=greed-magazine[i];
					magazine[i]=0;
				}
				else
				{
					magazine[i]=magazine[i]-greed;
					greed=0;
				}

				printf("Pokupatel: %d   ShopNo:%d    Buyer count:%d\n", *buy, i, greed);
				fflush(stdout);
				pthread_mutex_unlock(&ml[i]);
			}
		}
		sleep(2);
	}
}

void *docker(void* ptr)
{
	while(1)
	{
		int j = rand()%5;
			if(!pthread_mutex_trylock(&ml[j]))
			{
				magazine[j]+=500;
				pthread_mutex_unlock(&ml[j]);
			}
		sleep(1);
	}

}

int main(void)
{

	init();
	pthread_t tid[4];
	int buy[3];
	for(int i=0; i<3; i++)
	{
		buy[i]=i+1;
		pthread_create(&tid[i], NULL, buyer, &buy[i]);

	}
		pthread_create(&tid[4], NULL, docker, NULL);

	sleep(2);
	for(int i=0; i<3; i++)
		pthread_join(tid[i], NULL);

	pthread_cancel(tid[4]);


	return 0;
}
