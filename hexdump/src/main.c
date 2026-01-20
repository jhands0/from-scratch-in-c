#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    int addr_i = 0x0;
    while((c = getchar()) != EOF)
    {
        if (addr_i % 16 == 0)
        {
            printf("\n%08x ", addr_i);
        }
        printf("%02x ", c);
        addr_i += 1;
    }
    printf("\n%08x\n", addr_i);
}
