#include "memory.h"

void* memset(void* pointer, int c, size_t size)
{
    char* c_pointer = (char*) pointer;
    for (int i =0; i < size; i++)
    {
        c_pointer[i] = (char) c;
    }
    return pointer;
}

int memcmp(void* s1, void* s2, int count)
{
    char* c1 = s1;
    char* c2 = s2;

    while(count-- > 0)
    {
        if (*c1++ != *c2++)
        {
            return c1[-1] < c2[-1] ? -1 : 1;
        }
    }

    return 0;
}