
/*

The idea here to use the pipe to send message from child to parent . 



To run : 
gcc pipe.c -o pipe
then
./pipe Ahmad 
parent will print ahmad . 




*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
int main(int argc, char *argv[]) // inputs from user like : ./pipe ahmad
{
        int     fd[2], nbytes;//fd == file descriptors
        pid_t   childpid;
        //char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                
                write(fd[1], argv[1], (strlen(argv[1])));
                

                /* Send "string" through the output side of pipe */
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);
           
                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));//will wait until child write
                printf("Received string: %s\n", readbuffer);
        }
        
        
        return(0);
}
