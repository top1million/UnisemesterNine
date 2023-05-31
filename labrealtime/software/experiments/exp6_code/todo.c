// C program to demonstrate waitpid() 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
int x = 129;
void waitexample() 
{ 
	int i, stat; 
	pid_t pid[5]; 
	for (i=0; i<2; i++) 
	{ 
		if ((pid[i] = fork()) == 0) 
		{ 

			//sleep(1); 
            if(i == 0){
                while (x>10){
                    x = x/10;
                }
                exit (x);
            }
            else{
                while (x>100){
                    x = x/10;
                }
                exit (x%10);
            }
            

		} 

	} 

	// Using waitpid() and printing exit status 
	// of children. 
	for (i=0; i<2; i++) 
	{ 
		pid_t cpid = waitpid(pid[i],&stat,0);  
                
                printf("%d",WEXITSTATUS(stat));
	} 
} 

// Driver code 
int main() 
{ 
	waitexample(); 
    printf("%d",x%10);
	return 0; 
} 

