#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#define FIFO_FILE "MYFIFO"
int main (void)
{
FILE *fp;
char readbuf[80];
mknod(FIFO_FILE,S_IFIFO|0666,0);
while(1)
{
fp=fopen(FIFO_FILE,"r");
fgets(readbuf,80,fp);
int toprint = 0;
toprint = atoi(readbuf);
printf("Rec Int: %d\n",toprint+1);
printf("Rec String: %s\n",readbuf);
fclose(fp);
}
return(0);
}