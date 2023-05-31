#include <stdio.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>

int main ()
{
	int shmID;  // To hold the shared memory ID
    int *s; // Pointer on the first element of the shared memory
	/* Initialize shared memory that can hold 3 integers with key = 1000 */
    shmID = shmget(1000, sizeof(int)*3, 0666 | IPC_CREAT);
    printf("shmID = %d\n",shmID);
    if(shmID < 0){
		printf("error\n");
		exit(1);
    }
    /* Attach to the shared memory using the ID to be able to access it */
    s = (int *)shmat(shmID, NULL, 0);
	/* Read the values from the shared memory */
    // You can treat it like the array, e.g.: for loop to get the value
    printf("values in Shared memory:\n%d\n%d\n%d\n",s[0],s[1],s[2]);
    // After a shared memory is detached, it cannot be used
    shmdt(s);
    // To remove the shared memory: shmctl(shmID , IPC_RMID, NULL);
    return 0;
}