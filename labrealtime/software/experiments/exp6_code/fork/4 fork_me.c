#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{
    pid_t pid,p2;
    pid =fork();


    if (pid == 0) 
    {
        // child1

    }
    else 
    {
        p2 = fork();
        if (p2 == 0)
        {
            // child2
        }

        else 
        {
            // parent
        }
    }

 
    return 0;
}