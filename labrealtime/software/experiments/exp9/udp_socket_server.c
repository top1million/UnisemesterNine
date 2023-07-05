/* Server side implementation of UDP client-server model */ 
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

int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server";
	char response [80];
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating UDP socket file descriptor 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
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
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{
		perror("Bind failed\n"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Waiting for clients..\n");
	int len, n; 

	len = sizeof(cliaddr); //len is value/resuslt 
	
	while (1){
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
		
		buffer[n] = '\0'; 
		printf("Client name: %s", buffer);
		sprintf(response,"HELLO %s",buffer);
		sendto(sockfd, (char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr,	len); 
		printf("message sent.\n"); 
		printf("**************************************\n"); 
	}
	
	return 0; 
} 

