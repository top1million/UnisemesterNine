#include  <stdio.h>
#include  <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("My  PID  is %d\n", getpid()); // the process id of the c code
	printf("My  parent  PID  is %d\n", getppid()); // the process id of the parent of the c code(i.e. the shell that executed it)
	while (1)
		;
}
