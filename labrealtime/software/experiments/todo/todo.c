#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int pipefd[2];
char message[] = "Hello from Process 1!";
int count;
char buffer[100];
void signal_catcher(int); // create variable of function
void signal_catcher2(int);
int main()
{

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process (Process 2)
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
        sleep(50);

    }
    else
    {
            
    }
    sleep(50);

    return 0;
}

void signal_catcher(int sig_number)
{
	count++;
	printf("count from child = %d\n", count);
    fflush(stdout);
    
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
	close(pipefd[0]); // close the read
	if (write(pipefd[1], result, strlen(result)) != -1)
	{ // write to pipe for the child. Note that we have to sent the actual size of the data, that's why we have used strlen
		printf("Message  sent  by  parent:  [%s]\n", result);
		fflush(stdout);
	}
	else
	{
		perror("Write");
		exit(5);
	}
}