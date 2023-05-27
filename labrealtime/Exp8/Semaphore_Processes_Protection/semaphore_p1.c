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

/*
 To compile it
 gcc semaphore_p1.c -o p1 -lpthread
 */
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
	/* Semaphore initialization */ 
	// 2nd argument is to make it sharable with other processes. 
	// If it 0 it will be sharable within the process (Threads).
	// 3rd argument is initial value of the semaphore.
	sem_init(m, 1, 0);
	
	printf("Process 1 is waiting for p2 to finish.\n");
	sem_wait(m); //wait until there are resources to available
	/*
		CRITICAL SECTION
	*/
	printf("Process 1 has entered the CRITICAL SECTION after P2 has finished.\n");
	sleep(2);
	printf("Process 1 has finished the work in the CRITICAL SECTION.\n");
	sem_post(m); // release the semaphore
	return 0;
}
