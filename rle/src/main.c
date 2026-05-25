#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s [compress|decompress]\n", argv[0]);
        exit(-1);
    }

    if (!strcmp(argv[1], "compress") || !strcmp(argv[1], "-c"))
    {
        //compress();
    }

    if (!strcmp(argv[1], "decompress") || !strcmp(argv[1], "-d"))
    {
        //decompress();
    }

    return 0;
}