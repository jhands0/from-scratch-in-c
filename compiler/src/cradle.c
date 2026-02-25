#include "../include/cradle.h"
#include <stdio.h>
#include <stdlib.h>

void GetChar()
{
    Look = getchar();
}

void Error(char *s)
{
    printf("\nError: %s.", s);
}

void Abort(char *s)
{
    Error(s);
    exit(1);
}

void Expected(char *s)
{
    sprintf(buf, "%s Expected", s);
    Abort(buf);
}

void Match(char x)
{
    if (Look == x) {
        GetChar();
    } else {
        sprintf(buf, "' %c ' ", x);
        Expected(buf);
    }
}

int IsAlpha(char c)
{
    return (UPCASE(c) >= 'A') && (UPCASE(c) <= 'Z');
}

int IsDigit(char c)
{
    return (c >= '0') && (c <= '9');
}

char GetName()
{
    char c = Look;

    if (!IsAlpha(Look)) {
        sprintf(buf, "Name");
        Expected(buf);
    }

    GetChar();

    return UPCASE(c);
}

char GetNum()
{
    char c = Look;

    if (!IsDigit(Look)) {
        sprintf(buf, "Integer");
        Expected(buf);
    }

    GetChar();

    return c;
}

void Emit(char *s)
{
    printf("\t%s", s);
}

void EmitLn(char *s)
{
    Emit(s);
    printf("\n");
}

void Init()
{
    GetChar();
}
