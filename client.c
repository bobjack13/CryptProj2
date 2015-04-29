// CSCE 4050 Project 1
// Bob Jack
// 2-25-15
// Original client.c program from http://www.linuxhowtos.org/C_C++/socket.htm
// Compile with   gcc client.c  -o client
// Usage:   ./client  <Host Address>  <port>
// Enter text at prompt, then receive cipher text from server.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// For Errors
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

// Main 
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    // If the host and port are not entered, display the usage
    if(argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) 
        error("ERROR opening socket");
    
    portno = atoi(argv[2]); 
    server = gethostbyname(argv[1]);
    
    // If there is no host found, report
    if(server == NULL)
    { 
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    
    // Prompt user to enter message
    printf("Please enter the message: ");
    // Establish the input buffer and accept data
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    // Writes input to socket
    n = write(sockfd,buffer,strlen(buffer));
    
    // Socket writing failed
    if(n < 0) 
        error("ERROR writing to socket");
    
    // Awaiting response from server
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    
    // Error in reading response
    if(n < 0) 
        error("ERROR reading from socket");
    
    // Prints out response
    printf("%s\n",buffer);

    // Close socket
    close(sockfd);
    
    return 0;
}