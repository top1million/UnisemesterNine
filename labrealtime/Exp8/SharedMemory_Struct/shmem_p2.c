#include <stdio.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>

struct node{
    int x;
    char text1[30];
    char text2[100];
    char text3[20];
};
int main ()
{
	int shmID;
    struct node *s;
    shmID = shmget(2000, sizeof(struct node)*5, 0666 | IPC_CREAT);
    printf("shmID = %d\n",shmID);
    if(shmID < 0){
		printf("error\n");
		exit(1);
    }
    s = (struct node *)shmat(shmID, NULL, 0);
    printf("value: %d %s\n",s[1].x,s[1].text1);
    shmdt(s);
    return 0;
}