/*
 *  Using  a  pipe  to  send data  from  parent  to  a  child
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
int count;
int f_des[2];
static char message[BUFSIZ];
void signal_catcher(int); // create variable of function
void signal_catcher2(int);
int main(int argc, char *argv[])
{
	if (pipe(f_des) == -1)
	{
		perror("Pipe");
		exit(2);
	}
	switch (fork())
	{
	case -1: // error
		perror("Fork");
		exit(3);
	case 0: // child
			/*  In  the  child  */
		count = 0;
		if (sigset(SIGQUIT, signal_catcher) == SIG_ERR)
		{
			perror("Sigset  cannot set  SIGINT");
			exit(SIGINT);
		}
		if (sigset(SIGINT, signal_catcher2) == SIG_ERR)
		{
			perror("Sigset  cannot set  SIGINT");
			exit(SIGINT);
		}
		for (;;)
		{
			sleep(1);
		}
		break;
	default:			 /*  In  the  parent  */
		close(f_des[1]); // close the write
		if (read(f_des[0], message, BUFSIZ) != -1)
		{ // child read from the parent's pipe, and save the text in message array
			// note that read is a blocking function, it will wait forever until it received any data
			printf("Message  received  by  parent:  [%s]\n", message);
			fflush(stdout);
		}
		else
		{
			perror("Read");
			exit(4);
		}
		for(;;)
		{
			sleep(1);
		}
	}
	exit(0);
}

void signal_catcher(int sig_number)
{
	count++;
	printf("count = %d\n", count);
}

void signal_catcher2(int sig_number)
{
	int pid = getpid(); // Get the process ID
	char pid_str[16];	// Assuming the process ID can fit in 16 characters
	char count_str[16]; // Assuming the count can fit in 16 characters
	snprintf(pid_str, sizeof(pid_str), "%d", pid);
	snprintf(count_str, sizeof(count_str), "%d", count);

	// Concatenate the strings
	char result[50]; // Assuming the result can fit in 32 characters
	snprintf(result, sizeof(result), "pid%sCount%s", pid_str, count_str);
	close(f_des[0]); // close the read
	if (write(f_des[1], result, strlen(result)) != -1)
	{ // write to pipe for the child. Note that we have to sent the actual size of the data, that's why we have used strlen
		printf("Message  sent  by  child:  [%s]\n", result);
		fflush(stdout);
	}
	else
	{
		perror("Write");
		exit(5);
	}
	exit(0);
}