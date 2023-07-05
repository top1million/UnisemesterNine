#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for sock()
#include <string.h> //for using memset
#include <arpa/inet.h> // for inet_addr()
#include <unistd.h> //for using write() function

int main(){
    char data_received[1024];
    int sock=0;
	/* This struct is in 'netinet/in.h' to to handle internet addresses */
    struct sockaddr_in ServerIp;
     
	/* Create TCP socket with address family IPv4 */
    if(	(sock = socket(AF_INET, SOCK_STREAM ,0 )) == -1 ){
		printf("Socket creation failed ");
		exit(1);
	}
    
    ServerIp.sin_family = AF_INET;
    ServerIp.sin_port = htons(9090);
    ServerIp.sin_addr . s_addr = inet_addr("127.0.0.1");	
     
	/* Connect the local socket to the remote server socket */
    if((connect( sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp) )) == -1){
        printf("Connection to the socket failed\n");
        exit(1);
    }
    else
        printf("Connected to socket\n");
    
    printf("Waiting for respose..\n");	
    
    /* receive a message from a socket */	
    if(recv(sock, data_received, 1024, 0 ) == -1){
        printf("Error !! cannot get response\n");
		exit(1);
	}
    else
        printf("\nResponse Received is : %s", data_received);
	
	/* Close the connection */
	close( sock );
}
    
