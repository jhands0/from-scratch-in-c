#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

void print_help(char* exec_alias)
{
    printf("USAGE:\n");
    printf("\t%s <event/file/path> [OPTIONS]\n\n", exec_alias);

    printf("OPTIONS:\n");
    printf("\t-h <help>\t\tPrints program help to the screen\n");
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        print_help(argv[0]);
        exit(0);
    }

    if (!strcmp(argv[1], "-h"))
    {
        print_help(argv[0]);
        exit(0);
    }

    char *mousepath = argv[1];
    printf("Intercepting device %s ...\n", mousepath);
    int fd = open(mousepath, 0, O_RDONLY);
    printf("File descriptor: %d\n", fd);

    struct input_event ie;
    read(fd, &ie, sizeof(ie));
    printf("\nEvent recieved.\n");
    printf("Time = %lds %ldus\n", ie.time.tv_sec, ie.time.tv_usec);
    printf("Type = %hu\n", ie.type);
    printf("Code = %hu\n", ie.code);
    printf("Value = %d\n", ie.value);
}
