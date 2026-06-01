#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT "8080"
#define BACKLOG_LEN 15

int main()
{
    struct sockaddr_storage incoming_addr;
    socklen_t addr_size;
    int new_fd;

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

    if (bind(sockfd, server_info->ai_addr, server_info->ai_addrlen) == -1)
    {
        perror("Could not bind socket to address.\n");
        exit(-1);
    }
    
    // Block until request recieved
    if (listen(sockfd, BACKLOG_LEN) < 0)
    {
        perror("Could not listen for connections.\n");
        freeaddrinfo(server_info);
        exit(-1);
    }

    addr_size = sizeof(incoming_addr);
    new_fd = accept(sockfd, (struct sockaddr *) &incoming_addr, &addr_size);

    freeaddrinfo(server_info);
}