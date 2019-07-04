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
#include <stdlib.h>
#include <pthread.h>
void func(void *ptr)
{
	int *num;
	num=(int*)ptr;
	printf("%d\n", *num);
}

int main(void)
{
	int a[5];
	pthread_t tid[5];
	for(int i=0; i<5;i++)
	{
		a[i]=i+1;
		pthread_create(&tid[i], NULL,func, &a[i]);

	}
sleep(500);
	for(int i=0;i<5;i++)
		pthread_join(&tid[i], NULL);
	return 1;
}
