#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT "8080"
#define BACKLOG_LEN 15

void output_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

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

    if (getaddrinfo(NULL, PORT, &hints, &server_info) != 0) output_error("Could not dynamically fetch address information.");

    int sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (sockfd < 0) output_error("Could not initialize socket.");

    if (bind(sockfd, server_info->ai_addr, server_info->ai_addrlen) == -1) output_error("Could not bind socket to address.");
    
    // Block until request recieved
    if (listen(sockfd, BACKLOG_LEN) < 0)
    {
        freeaddrinfo(server_info);
        output_error("Could not listen for connections.");
    }

    addr_size = sizeof(incoming_addr);
    new_fd = accept(sockfd, (struct sockaddr *) &incoming_addr, &addr_size);

    freeaddrinfo(server_info);
}