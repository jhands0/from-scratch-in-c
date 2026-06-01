#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT "8080"

int main()
{
    struct addrinfo hints, *server_info;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT, &hints, &server_info) != 0)
    {
        perror("Could not dynamically fetch address information.\n");
        exit(-1);
    }

    int sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (sockfd < 0)
    {
        perror("Could not initialize socket.\n");
        exit(-1);
    }
    

    while(1)
    {
        // Block until request recieved
        printf("Waiting for request...\n");
        sleep(1);
    }

    freeaddrinfo(server_info);
}