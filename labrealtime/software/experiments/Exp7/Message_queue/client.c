/*
	Client Code
	it sends a file name for server to open it and return the file's data.

	this code create data with type=1 and send it to server(1 is like listening socket for server)
	then server sends response with type=(pid of client) so only the client can receive it

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define FIFO_FILE "MYFIFO"

/*THEY MUST HAVE THE SAME KEY*/
#define KEY 600
#define PUBLIC_PORT 1

struct msg
{
	long int type ; 
	char data[1024];
	int pid;
} p , p1; // creating two instances of msg


int main(){
	int m;// queue id
	m = msgget(KEY, 0666|IPC_CREAT ); // since the queue is created before,it just will get it

	p.type = getpid(); // set the type(id) of the new msg p
	p.pid=getpid();// to make server return mess with this type
	
	FILE *fp;
	__pid_t pid;
	if((fp = fopen(FIFO_FILE,"w")) == NULL)
	{
		exit(1);
	}
	pid = getpid();
	printf("My pid is %d\n",pid);
	fprintf(fp,"%d",pid);
	fclose(fp);
	printf("\nEnter a file name>>");
	scanf("%s",&(p.data)); // set the data of p


	msgsnd(m, &p, sizeof(p)-4, 0);
	
	msgrcv(m, &p1, sizeof(p1)-4, p.pid, 0);//note that msgrcv has 5 parameters not 4, the last forth one is the type to receive
	printf("%s",p1.data);
}