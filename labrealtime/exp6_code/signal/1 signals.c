/*
 *  Catching  signals  with  sigset
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int i;
	void signal_catcher(int); // create variable of function

	// assigning SIGINT to signal_catcher function(This signal can be used using ctrl + c)
	if (sigset(SIGINT, signal_catcher) == SIG_ERR)
	{
		perror("Sigset  cannot set  SIGINT");
		exit(SIGINT);
	}
	// assigning  SIGQUIT to signal_catcher function(This signal can be used using ctrl + \)
	if (sigset(SIGQUIT, signal_catcher) == SIG_ERR)
	{
		perror("Sigset  cannot set  SIGQUIT");
		exit(SIGQUIT);
	}

	// infinite loop until triggering SIGQUIT signal
	for (i = 0;; ++i)
	{
		printf("%i\n", i);
		sleep(1);
	}
}
void signal_catcher(int sig_number)
{
	printf("\nSignal  %d  received.\n", sig_number);
	if (sig_number == SIGQUIT) // if we press ctrl + \, the code will terminate
		exit(1);
}
