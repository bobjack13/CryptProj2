// CSCE 4050 Project 1
// Bob Jack
// 2-25-15
// Original server.c program from http://www.linuxhowtos.org/C_C++/socket.htm
// Compile with   gcc server.c  -o server  -lcrypto
// Usage:   ./server  <port>
// Server Just runs and waits for connections

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/aes.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h> 

const int BUFF_SIZE = 64;   // Input buffer size

// Generic encryption user key established for AES
static const unsigned char enc_key[] = {
    0x00, 0x01, 0x02, 0x03, 
    0x10, 0x11, 0x12, 0x13, 
    0x20, 0x21, 0x22, 0x23,
    0x30, 0x31, 0x32, 0x33
    };

// Reports error message and quits
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Encryption function accepts a string and size, then encrypts and returns 
// the ciphertext pointer
char * encryptAES(char *p, int size)
{
    char *temp;
    int len = strlen(p);
    temp = malloc(sizeof(char) * (len + 1));
    AES_KEY a_key;

    // Make encryption
    AES_set_encrypt_key(enc_key, 128, &a_key);
    AES_encrypt(p, temp, &a_key);
    //printf("PT: %s\nCT: %s\n Size:%i\n", p, temp. size); // For debugging

    return temp;
}


// Server Main
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[BUFF_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // If port is not entered, then display usage and quit
    if(argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Loops through infinitely listening
    while(1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        char *encBuffer;

        if(newsockfd < 0) 
            error("ERROR on accept");

        bzero(buffer, BUFF_SIZE);
        n = read(newsockfd, buffer, BUFF_SIZE-1);
        
        if(n < 0)
            error("ERROR reading from socket");

        //printf("Here is the message: %s\n",buffer); // For debugging
        encBuffer = encryptAES(buffer, BUFF_SIZE);

        //printf("CT: %s\n", encBuffer);

        // Writes the ciphertext to the socket
        n = write(newsockfd, encBuffer, BUFF_SIZE);
        
        // Failed to write to socket
        if(n < 0)
            error("ERROR writing to socket");

        close(newsockfd);
     
        sleep(1);
    }
    close(sockfd);

    return 0; 
}
