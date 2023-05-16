#include  <stdio.h>
#include  <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{  int status;
   int x=10;
   int y=20;
   if(fork()==0)
   {
           //In child
           printf("In child:%d\n",getpid());
           return(x+y);
   }
   else
   {       wait(&status);
           printf("In parent:%d\n",getpid());
           printf("Result from child is:%d\n",WEXITSTATUS(status));
           //In parent
   }


}
