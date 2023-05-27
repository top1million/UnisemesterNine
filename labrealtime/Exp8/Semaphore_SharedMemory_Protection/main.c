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

int main() {
  // Create a Semaphore
  sem_t *m;
  // The name should be unique "mysemaphore2"
  // 2nd argument(O_CREAT): If the semaphore is not exist, create it.
  // 4th argument is initial value, you can use the sem_init function as below.
  if ((m = sem_open("mysemaphore2", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("Error");
    exit(1);
  }
  int shmid;
  int * shm;
  /* Semaphore initialization */ 
  // 2nd argument is to make it sharable with other processes. 
  // If it 0 it will be sharable within the process (Threads).
  // 3rd argument is initial value of the semaphore.
  sem_init(m, 1, 1);

  if (fork() == 0) {
    int i;
    shmid = shmget(2009, SHMSIZE, 0);
    shm = (int * ) shmat(shmid, 0, 0);
    * shm = 1000;
    while (1) {
      sem_wait(m);
      * shm = * shm - 1;
      printf("val_child=%d\n", * shm);
      //sleep(1);
      sem_post(m);
    }
    shmdt(shm);
  } else {
    shmid = shmget(2009, SHMSIZE, 0666 | IPC_CREAT);
    shm = (int * ) shmat(shmid, 0, 0);
    while (1) {
      sem_wait(m);
      * shm = * shm + 1;
      printf("val_parent=%d\n", * shm);
      //sleep(1);
      sem_post(m);
    }
    shmdt(shm);
  }
  return 0;
}