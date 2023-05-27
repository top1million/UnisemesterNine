/*
	The server has a listing type which is 1
	it open a file and returns data of file to the client
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#define FIFO_FILE "MYFIFO"

/*THEY MUST HAVE THE SAME KEY*/
#define KEY 600
#define PUBLIC_PORT 1
struct msg
{
	long int type;
	char a[1024]; // actual message 
	int pid; // to know to which client to return the file data
}p;

int main(){

	int m,n,fd,m1;
	FILE *fp;
	char readbuf[80];
	mknod(FIFO_FILE,S_IFIFO|0666,0);
	fp=fopen(FIFO_FILE,"r");
	fgets(readbuf,80,fp);
	m = msgget(KEY,0666|IPC_CREAT); //create new queue
	int pid = atoi(readbuf);
	while(1){
		msgrcv(m, &p, sizeof(p)-4, pid, 0); // receive fileName at type=1 (-4 to remove the size of the type (Getting the actual size of the meesage))
		printf("Filename from received from client: (%s)\n",p.a);
		fd = open(p.a , O_RDONLY); // open the file received from the client
		n = read(fd , p.a , 1024);//read 1024 byte of it
		p.type = p.pid; // the client pid
		p.pid = getpid();
		msgsnd(m,&p,sizeof(p) -4 ,0);// send pointer to p on the queue
	
	}
}