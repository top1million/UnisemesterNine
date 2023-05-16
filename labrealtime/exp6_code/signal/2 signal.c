#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int ctrl_c_count = 0;
void(*old_handler); // to save the address of past ctrl+c function

void ctrl_c(int);
void main()
{
    int c;

    old_handler = signal(SIGINT, ctrl_c); // save the original func
    while ((c = getchar()) != '\n')
        ;
    printf("ctrl_c count = %d\n", ctrl_c_count);
    signal(SIGINT, old_handler);
    for (;;)
        ;
}
void ctrl_c(int signum)
{
    signal(SIGINT, ctrl_c); // make sure that the signal will excute ctrl-c function
    // signals are automatically reset
    ++ctrl_c_count;

} // see also the POSIX sigaction() call ‐ more complex but better
