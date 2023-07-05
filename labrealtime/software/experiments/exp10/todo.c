#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void do_one_thing(int *);

int r1 = 0, r2 = 0, r3 = 0;
pthread_t thread1, thread2,thread3;
int value = 976;
int main(int argc, char **argv)
{
	pthread_create(&thread1,NULL,(void *) do_one_thing,(void *) &r1);
	pthread_create(&thread2,NULL,(void *) do_one_thing,(void *) &r2);
    pthread_create(&thread3,NULL,(void *) do_one_thing,(void *) &r3);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
	return 0;
}
void do_one_thing(int *pnum_times)
{
	/*Each thread will has it's own k local variable */
	int k;
	pthread_t thread;

	thread = pthread_self();
if (pthread_equal(thread1, thread)){
    int first_digit = value/100;
	printf("Thread %ld: %d\n", thread, first_digit);
}
else if(pthread_equal(thread2, thread)){
    int second_digit = (value/10)%10;
	printf("Thread %ld: %d\n", thread, second_digit);
}
else{
    int third_digit = value%10;
    printf("Thread %ld: %d\n", thread, third_digit);
}

/* Delay */
for ( k = 0; k < 100000; k++ );

}
