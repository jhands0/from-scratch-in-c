#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress()
{
    int next_char;
    int seen_char = getchar();
    int cnt = 1;
    while ((next_char = getchar()) != EOF)
    {
        if (next_char == seen_char)
        {
            cnt++;

            if (cnt >= 255)
            {
                putchar(seen_char);
                putchar(cnt);

                cnt = 0;
            }
        }

        else 
        {
            putchar(seen_char);
            putchar(cnt);
            
            seen_char = next_char;
            cnt = 1;
        }
    }
    cnt++;
    putchar(seen_char);
    putchar(cnt);    
}

void decompress()
{
    while (1)
    {
        int c = getchar();
        if (c == EOF) break;
        int cnt = getchar();
        if (cnt == EOF) break;

        for (int i = 0; i < cnt; i++)
        {
            putchar(c);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s [compress|decompress]\n", argv[0]);
        exit(-1);
    }

    if (!strcmp(argv[1], "compress") || !strcmp(argv[1], "-c"))
    {
        compress();
    }

    if (!strcmp(argv[1], "decompress") || !strcmp(argv[1], "-d"))
    {
        decompress();
    }

    return 0;
}