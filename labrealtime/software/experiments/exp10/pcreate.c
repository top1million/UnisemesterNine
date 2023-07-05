#include <stdio.h>
#include <pthread.h>

// To compile: gcc pcreate.c -o pcreate -lpthread

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int, int);
/* Global Variables */
int r1 = 0, r2 = 0;
extern int main(void)
{
	/* pthread_t is like long */
	pthread_t thread1, thread2;
	/*
	We should link each thread with a function
	You should cast the function name and the parameter with (void *) - Genric type (larger that int, long, float, so it include them)
	You can pass local and global variable
	*/
	
	/* They will work in parrallel */
	pthread_create(&thread1, NULL,(void *) do_one_thing,(void *) &r1);
	pthread_create(&thread2, NULL,(void *) do_another_thing,(void *) &r2);

	printf(">> pthread_t : %ld\n",thread1 );
	printf(">> pthread_t : %ld\n",thread2 );
	/* Wait till thread1 finish */
	pthread_join(thread1, NULL);
	/* Wait till thread2 finish */
	pthread_join(thread2, NULL);
	do_wrap_up(r1, r2);
	return 0;
}

void do_one_thing(int *pnum_times)
{
int i, j, x;
for ( i = 0; i < 4; i++ )
	{
	printf("doing one thing\n");
	/* Sleep a while */
	for ( j = 0; j < 10000; j++ )
		x = x + i;
	(*pnum_times)++;
	}
}

void do_another_thing(int *pnum_times)
{
int i, j, x;
for ( i = 0; i < 4; i++ ) {
	printf("doing another \n");
	/* Sleep a while */
	for ( j = 0; j < 10000; j++ )
		x = x + i;
	(*pnum_times)++;
	}
}

void do_wrap_up(int one_times, int another_times)
{
	int total;
	total = one_times + another_times;
	printf("wrap up: one thing %d, another %d, total %d\n",one_times, another_times,total);
}
