/* Server side implementation of UDP client-server model */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define MAXLINE 1024
void do_one_thing(int *);

int r1 = 0, r2 = 0, r3 = 0;
pthread_t thread1, thread2, thread3;

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    char response[80];
    struct sockaddr_in servaddr, cliaddr;

    // Creating UDP socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for clients..\n");
    int len, n;

    len = sizeof(cliaddr); // len is value/resuslt

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);

    buffer[n] = '\0';
    printf("Client name: %s", buffer);
    int value = atoi(buffer);
    pthread_create(&thread1, NULL, (void *)do_one_thing, (void *)&value);
    pthread_create(&thread2, NULL, (void *)do_one_thing, (void *)&value);
    pthread_create(&thread3, NULL, (void *)do_one_thing, (void *)&value);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
void do_one_thing(int *x)
{
    /*Each thread will has it's own k local variable */
    int k;
    int value = *x;
    pthread_t thread;

    thread = pthread_self();
    if (pthread_equal(thread1, thread))
    {
        int first_digit = value / 100;
        printf("Thread %ld: %d\n", thread, first_digit);
    }
    else if (pthread_equal(thread2, thread))
    {
        int second_digit = (value / 10) % 10;
        printf("Thread %ld: %d\n", thread, second_digit);
    }
    else
    {
        int third_digit = value % 10;
        printf("Thread %ld: %d\n", thread, third_digit);
    }

    /* Delay */
    for (k = 0; k < 100000; k++)
        ;
}
