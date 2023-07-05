#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void do_one_thing(int *);

int r1 = 0, r2 = 0, r3 = 0;
pthread_mutex_t r3_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_t thread1, thread2;

int main(int argc, char **argv)
{
	pthread_create(&thread1,NULL,(void *) do_one_thing,(void *) &r1);
	pthread_create(&thread2,NULL,(void *) do_one_thing,(void *) &r2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}
void do_one_thing(int *pnum_times)
{
	/*Each thread will has it's own k local variable */
	int k;
	pthread_t thread;
while ( 1 ) {
	pthread_mutex_lock(&r3_mutex);
	thread = pthread_self();
if (pthread_equal(thread1, thread))
	printf("Thread %ld: %d\n", thread, ++r3);
else
	printf("Thread %ld: %d\n", thread, --r3);
	pthread_mutex_unlock(&r3_mutex);

/* Delay */
for ( k = 0; k < 100000; k++ );
}
}
