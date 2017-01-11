/*from dodng
2016.12.9*/
#include <stdio.h>
#include "ring_queue.h" 
#include <unistd.h>
#include <sys/time.h>

const int LOOP_SIZE = 10000;

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


#define THREAD_NUM 1

#define DATA_TYPE int

void *customer(void *arg)
{
	Ring_Queue queue = *(Ring_Queue *)arg;

	while(1)
	{
		for(int i = 0;i < LOOP_SIZE; )
		{
			int *p = 0;
			p = (DATA_TYPE *)queue.SOLO_Read();
			if (p)
			{
				assert(i == *p);
//				printf("[%d]:%d\n",i,*p);
				queue.SOLO_Read_Over();
				i++;
			}
		}
	}
}

void *producer(void *arg)
{
	Ring_Queue queue = *(Ring_Queue *)arg;
	
	int loop = 0;
	struct timeval last_time,now_time;
	gettimeofday(&last_time,NULL);
	gettimeofday(&now_time,NULL);
	while(1)
	{
		for(int i = 0;i < LOOP_SIZE; )
		{
			int *p = 0;
			p = (DATA_TYPE *)queue.SOLO_Write();
			if (p)
			{
				*p = i;
				queue.SOLO_Write_Over();
				i++;
			}
		}
		gettimeofday(&now_time,NULL);
		if (now_time.tv_sec - last_time.tv_sec >= 5)
		{
			printf("LOOP_COUNT is %.2f=[ %d[RING_SIZE] * %.2f[RING_COUNT]] per second\n",(LOOP_SIZE*loop)/5.0,LOOP_SIZE,loop/5.0);
			last_time = now_time;
			loop = 0;
		}
		loop++;
	}
}

int main(int argc,char *argv[])
{
	pthread_t tid_customer[THREAD_NUM];
	pthread_t tid_producer[THREAD_NUM];
	Ring_Queue *queue = new Ring_Queue[THREAD_NUM](LOOP_SIZE,sizeof(DATA_TYPE));

	for (int i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&tid_customer[i],NULL,&customer,(void*)&queue[i]) != 0)
		{
			fprintf(stderr,"thread create failed\n");
			return -1;
		}
	}
	for (int i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&tid_producer[i],NULL,&producer,(void*)&queue[i]) != 0)
		{
			fprintf(stderr,"thread create failed\n");
			return -1;
		}
	}

	for (int i = 0 ;i < THREAD_NUM; i++)
		pthread_join(tid_customer[i],NULL);
	
	for (int i = 0 ;i < THREAD_NUM; i++)
		pthread_join(tid_producer[i],NULL);

}
