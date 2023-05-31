/*
 *  Running  the  cat  utility  via  an  exec   system  call
 *  To run it (./run testFile.txt)
 */
#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>
int main(int argc, char *argv[]) {
	if (argc != 2) { // argv[0] = executable filename(i.e. ./run); //argv[1] = first args(i.e. testFile.txt); // argc in this case = 2 (size of argv)
		printf("Usage:  %s  fileName", argv[0]);
		exit(1);
	}

	/*
		int execlp(const char *file, const char *arg, ...);
		first arg (file) is the executable command
		second arg is any name for the process
		other args are parameters for the given command
	*/
	execlp("/bin/cat", "cat", argv[1], (char *) NULL); // this will execute ( cat argv[1] ) 
	perror("exec  failure  ");
	exit(2);
}
