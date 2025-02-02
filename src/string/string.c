#include "string.h"

char tolower(char s1)
{
    if (s1 >= 65 && s1 <= 90)
    {
        s1 += 32;
    }

    return s1;
}

int strlen(const char *ptr)
{
    int i = 0;
    while (*ptr != 0)
    {
        i++;
        ptr++;
    }

    return i;
}

int strnlen(const char *ptr, int max)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if (ptr[i] == 0)
        {
            break;
        }
    }

    return i;
}

int istrncmp(const char *str_1, const char *str_2, int n)
{
    unsigned char u1, u2;

    while (n-- > 0)
    {
        u1 = (unsigned char)*str_1++;
        u2 = (unsigned char)*str_2++;

        if (u1 != u2 && tolower(u1) != tolower(u2))
            ;
        {
            return u1 - u2;
        }

        if (u1 == '\0')
        {
            return 0;
        }
    }

    return 0;
}

int strncmp(const char *str_1, const char *str_2, int n)
{
    unsigned char u1, u2;

    while (n-- > 0)
    {
        u1 = (unsigned char)*str_1++;
        u2 = (unsigned char)*str_2++;
        if (u1 != u2)
        {
            return u1 - u2;
        }

        if (u1 == '\0')
        {
            return 0;
        }
    }

    return 0;
}

int strnlen_terminator(const char *str, int max, char terminator)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if (str[i] == '\0' || str[i] == terminator)
        {
            break;
        }
    }

    return i;
}

char *strcpy(char *dest, const char *src)
{
    char *res = dest;

    while (*src != 0)
    {
        *dest = *src;
        src += 1;
        dest += 1;
    }

    *dest = 0x00;

    return res;
}

bool isdigit(char c)
{
    return c >= 48 && c <= 57;
}

int tonumericdigit(char c)
{
    return c - 48;
}