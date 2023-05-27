/*

 The idea to make counter and update it each one second. 
 The P1 and P2 processes change it using semaphore between them.

 gcc semaphore_example.c -o run -lpthread
 ./run

 */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/wait.h>  /* Needed for the wait function */
#include <unistd.h>    /* Needed for the fork function */
#include <string.h>    /* Needed for the strcat function */
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/mman.h>

int main() {
	// Create a Semaphore
	sem_t *m;
	// The name should be unique "mysemaphore1"
	// 2nd argument(O_CREAT): If the semaphore is not exist, create it.
	// 4th argument is initial value, you can use the sem_init function as below.
	if ((m = sem_open("mysemaphore1", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initialization");
		exit(1);
	}
	/*
		CRITICAL SECTION
	*/
	printf("Process 2 has started its CRITICAL SECTION.\n");
	sleep(2);
	printf("Process 2 has finished its CRITICAL SECTION.\n");

	sem_post(m); // release the semaphore to make other processes enter their critical section

	return 0;
}
