#include  <stdio.h>
#include  <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{ int i;
  pid_t p;
   for(i=0;i<3;i++)
   {
          p=fork();
		//        if(p==0)
        	// 	while(1);
   }
   printf("My id is:%d\n",getpid());
   sleep(1);

}
