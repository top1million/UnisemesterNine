/*
 *  Catching  signals  with  sigset
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int count = 0;
int f_des[2];
static char message[BUFSIZ];
int main(void)
{
    int i;
    void signal_catcher(int); // create variable of function
    void signal_catcher2(int);

    // assigning SIGINT to signal_catcher function(This signal can be used using ctrl + c)
    if (sigset(SIGQUIT, signal_catcher) == SIG_ERR)
    {
        perror("Sigset  cannot set  SIGINT");
        exit(SIGINT);
    }
    if (sigset(SIGINT, signal_catcher2) == SIG_ERR)
    {
        perror("Sigset  cannot set  SIGINT");
        exit(SIGINT);
    }

    // infinite loop until triggering SIGQUIT signal
    for (i = 0;; ++i)
    {
        sleep(1);
    }
}
void signal_catcher(int sig_number)
{
    count++;
    printf("count = %d\n", count);
}

void signal_catcher2(int sig_number)
{
    int pid = getpid(); // Get the process ID
    char pid_str[16];   // Assuming the process ID can fit in 16 characters
    char count_str[16]; // Assuming the count can fit in 16 characters
    snprintf(pid_str, sizeof(pid_str), "%d", pid);
    snprintf(count_str, sizeof(count_str), "%d", count);

    // Concatenate the strings
    char result[50]; // Assuming the result can fit in 32 characters
    snprintf(result, sizeof(result), "pid%sCount%s", pid_str, count_str);
    close(f_des[0]); // close the read
    if (write(f_des[1], result, strlen(result)) != -1)
    { // write to pipe for the child. Note that we have to sent the actual size of the data, that's why we have used strlen
        printf("Message  sent  by  parent:  [%s]\n", result);
        fflush(stdout);
    }
    else
    {
        perror("Write");
        exit(5);
    }
}