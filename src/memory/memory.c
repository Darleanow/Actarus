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