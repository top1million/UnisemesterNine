#include <stdio.h>
#include <stdlib.h>
#define FIFO_FILE "MYFIFO"
int main()
{
FILE *fp;
__pid_t pid;
if((fp = fopen(FIFO_FILE,"w")) == NULL)
{
	exit(1);
}
pid = getpid();
printf("My pid is %d\n",pid);
fprintf(fp,"%d",pid);
fclose(fp);
return(0);

}