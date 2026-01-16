#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

}
