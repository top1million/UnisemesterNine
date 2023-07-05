// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char data_send[1024];
	struct sockaddr_in	 servaddr; 

	// Creating UDP socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	printf("Enter Your name \n>> ");
    fgets(data_send, sizeof(data_send), stdin ); 
	sendto(sockfd, (char *)data_send, strlen(data_send), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
	printf("message sent.\n"); 
	/* MSG_WAITALL: Wait all the fragments of a message */
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
	buffer[n] = '\0'; // End of the string
	printf("Server reply: %s\n", buffer); 

	close(sockfd); 
	return 0; 
} 

