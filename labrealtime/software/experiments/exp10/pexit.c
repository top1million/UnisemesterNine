#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//pthread_t thread;

static int arg;
static const int real_bad_error = 12;
static const int normal_error = 0;
static const int success = 1;

void *routine_x(void *arg_in)
{
int *arg = (int *)arg_in;
// *arg to get the value
if ( *arg < 0 )
// pthread_exit is equivalent to return
pthread_exit((void *) &real_bad_error);
else if ( *arg == 0 )
return ((void *) &normal_error);
else
return ((void *) &success);
}

int main(int argc, char **argv)
{
	// pthread_t size is 4 bytes
	pthread_t thread;
	int r;
	void *statusp;
	// Validate user that the user entered input
	if ( argc != 2 )
	{
		fprintf(stderr, "You must supply an integer as argument!\n");
		exit(-1);
	}
	r = atoi(argv[1]);
	pthread_create(&thread, NULL, routine_x,&r);
	pthread_join(thread, &statusp);
	// Thread exited in running, rare to occur
	if ( (int *) statusp == PTHREAD_CANCELED )
		printf("Thread was canceled.\n");
	else
		// Get the value in statusp (1, 10 or 12)
		printf("Thread completed and exit status is %d.\n", *(int *)statusp);
	return 0;
}
