//gcc main.c -lpthread
#include <stdio.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>  /* Needed for the wait function */
#include <unistd.h>    /* Needed for the fork function */
#include <string.h>    /* Needed for the strcat function */
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/mman.h>
#define SHMSIZE 27 /* Bytes */

int main(){
	/* Create 2 Semaphores */
	sem_t *m;
	sem_t *p;
	if((m = sem_open("mysemaphore3",O_CREAT,0644,1)) == SEM_FAILED)
	{
		perror("Error");
        exit(1);
	}
	if((p = sem_open("mysemaphore4",O_CREAT,0644,1)) == SEM_FAILED)
	{
		perror("Error");
        exit(1);
	}
	/* Semaphores initialization */ 
	// 2nd argument is to make it sharable with other processes. 
	// If it 0 it will be sharable within the process (Threads).
	// 3rd argument is initial value of the semaphore.
	sem_init(m,1,1);
	sem_init(p,1,0);

	int shmid;
	int *shm;
	
	if (fork() == 0)
	{
		int i;
        shmid = shmget(2009,SHMSIZE,0);
        shm = (int *)shmat(shmid,0,0);
        *shm =1000;
		while(1)
		{
			sem_wait(m);//block if m=0, continue if m=1
			//m--
			*shm = *shm -1;
			printf("val_child=%d\n",*shm);
			sleep(1);
			sem_post(p);
			//p++
		}
		shmdt(shm);
	}
	else
	{
		shmid = shmget(2009,SHMSIZE,0666 | IPC_CREAT);
        shm = (int *)shmat(shmid,0,0);
        while(1)
		{
			sem_wait(p);//block  if p=0, continue if p=1
			//p--
			*shm = *shm+1;
			printf("val_parent%d\n",*shm);
			sleep(1);
			sem_post(m);
			//m++
		}
		shmdt(shm);
	}
return 0;
}