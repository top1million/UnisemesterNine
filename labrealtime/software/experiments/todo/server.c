/*
 *  Using  a  pipe  to  send data  from  parent  to  a  child
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int f_des[2];
    static char message[BUFSIZ];

    if (pipe(f_des) == -1)
    {
        perror("Pipe");
        exit(2);
    }

    /*  In  the  parent  */
    close(f_des[1]); // close the read
    if(read(f_des[0], message, BUFSIZ) != -1)
    { // read from the parent's pipe, and save the text in message array
        //note that read is a blocking function, it will wait forever until it received any data
        printf("Message  received  by  child:  [%s]\n", message);
        fflush(stdout);
    }
    else
    {
        perror("Read");
        exit(4);
    }
    while(1);

exit(0);
}
