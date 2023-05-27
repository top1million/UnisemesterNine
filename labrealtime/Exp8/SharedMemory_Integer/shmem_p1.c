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
	/* Write values on the shared memory */
    s[0]=5; // You can replace with *s = 5;
    s[1]=6;
    s[2]=7;
    printf("Values written successfully!\n");
    // After a shared memory is detached, it cannot be used
    shmdt(s);
    // To remove the shared memory: shmctl(shmID , IPC_RMID, NULL);
    return 0;
}