#include <stdio.h>
#include <stdlib.h>

void print_clear(char *buffer, int len)
{
    printf("|");
    for (int i = 0; i < len; i++)
    {
        if (buffer[i] <= 0x20 || buffer[i] >= 0x7E)
        {
            printf(".");
        } else {
            printf("%c", buffer[i]);
        }
    }
    printf("|");
}

void add_space(int index)
{
    int i = index;
    while (i % 0x10 == 1)
    {
        printf("   ");
    }
}

int main()
{
    int c;
    int addr_i = 0x0;
    char *buffer = (char *) calloc(0x10, sizeof(char));
    while((c = getchar()) != EOF)
    {
        if (addr_i % 0x10 == 0)
        {
            if (addr_i != 0x0)
            {
                print_clear(buffer, 0x10);
                printf("\n");
            }
            printf("%08x ", addr_i);

        }

        buffer[addr_i % 0x10] = c;
        printf("%02x ", c);
        addr_i += 1;
    }

    add_space(addr_i);
    print_clear(buffer, addr_i);
    printf("\n");
    printf("%08x\n", addr_i);
}
