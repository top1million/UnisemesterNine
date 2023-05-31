/*
 *  Using  a  pipe  to  send data  from  parent  to  a  child
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
	int f_des[2];
	static char message[BUFSIZ];

	if (pipe(f_des) == -1) {
		perror("Pipe");
		exit(2);
	}
	switch (fork()) {
	case -1: // error
		perror("Fork");
		exit(3);
	case 0: // child
		/*  In  the  child  */
		close(f_des[1]); // close the write
		if (read(f_des[0], message, BUFSIZ) != -1) {//child read from the parent's pipe, and save the text in message array
			//note that read is a blocking function, it will wait forever until it received any data
			printf("Message  received  by  child:  [%s]\n", message);
			fflush(stdout);
		} else {
			perror("Read");
			exit(4);
		}
		break;
	default: /*  In  the  parent  */
		close(f_des[0]);// close the read
		char text [30] = "The best";
		if (write(f_des[1], text, strlen(text)) != -1) {// write to pipe for the child. Note that we have to sent the actual size of the data, that's why we have used strlen
			printf("Message  sent  by  parent:  [%s]\n", text);
			fflush(stdout);
		} else {
			perror("Write");
			exit(5);
		}
	}
	exit(0);
}
