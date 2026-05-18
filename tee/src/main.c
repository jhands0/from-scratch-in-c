#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL)
    {
        perror("Opening file to write went wrong");
        return 0;
    }

    char c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        
        putc(c, fp);
    }
}