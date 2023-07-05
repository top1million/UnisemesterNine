#include <stdio.h>
#include <sys/socket.h> //for sock()
#include <string.h> // for using memset
#include <arpa/inet.h> // for inet_addr()
#include <unistd.h> //for using write() function
#include <stdlib.h> 
#include <netinet/in.h> 

int main(){

    int sock=0, client_conn=0;
    char data_send[1024];
	/* This struct is in 'netinet/in.h' to to handle internet addresses */
    struct sockaddr_in ServerIp;
    int opt = 1;
	/* Create TCP socket with address family IPv4 */
    sock = socket(AF_INET, SOCK_STREAM, 0);
	/*
	ServerIp is used to store the details of server
	memset used to initialize each byte of the passed variable with zero value
	*/
    memset(&ServerIp,'0',sizeof(ServerIp) );
	
    /* Forcefully attaching socket to the port 9090 */
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

	/* Configure settings in address struct */
    ServerIp.sin_family = AF_INET;
	/* To guarantee data order between host and network(Router) (They could be little endian or big endian architecture) */
	/* You should use port number +1000 */
    ServerIp.sin_port = htons(9090);
	/* Local host address */
    ServerIp.sin_addr . s_addr = inet_addr("127.0.0.1");
     
	/* Allocate a port number to with the IP address to a socket */
    if(bind(sock,(struct sockaddr* )&ServerIp, sizeof(ServerIp)) == -1 ){
        printf("Socket binding failed\n");
		exit(1);
	}
    
	/* Accept incoming connections up to 20 */
    if(listen(sock,20) == -1) {
        printf("listen: Error\n");
		exit(1);
	}
    else	
        printf("Server started\n");
    
	while(1) {
		printf("Waiting for client..\n");
		client_conn = accept( sock, (struct sockaddr*)NULL, NULL);
		printf("A connection established with client\n");
		printf("Enter a response message \n>> ");
		/* stdin: Read from the terminal */
		fgets(data_send, sizeof(data_send), stdin); 
		write(client_conn, data_send, sizeof(data_send));
		close(client_conn);
		printf("*********************************\n");
    }
        
    
    return 0;
    
}

