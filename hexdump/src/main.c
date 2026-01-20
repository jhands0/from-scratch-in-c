#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    while((c = getchar()) != EOF)
    {
        printf("%02x ", c);
    }
    printf("\n");
}
