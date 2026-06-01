#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT "8080"

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
}