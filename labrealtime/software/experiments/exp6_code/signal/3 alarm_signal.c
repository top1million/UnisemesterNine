/*
 * Testing the alarm signal (SIGALRM)
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int val = 0;
int main(void)
{
	int i;

	void signal_catcher(int);
	alarm(1);										// will send SIGALRM after 1 second
	if (sigset(SIGALRM, signal_catcher) == SIG_ERR) // assigning SIGALRM to signal_catcher function
	{
		perror("SIGSET cannot set SIGALRM");
		exit(SIGINT);
	}
	while (1)
		;
}

/**
 * Each 1 second, this catcher will be called, using SIGALARM signal
 */
void signal_catcher(int the_sig)
{
	val++;
	printf("val = %d\n", val);
	alarm(1); // set an alarm after another second to trigger this function again
}