#ifndef STRING_H
#define STRING_H
#include <stdbool.h>

int strlen(const char *ptr);
int strnlen(const char *ptr, int max);
char *strcpy(char *dest, const char *src);
bool isdigit(char c);
int tonumericdigit(char c);
int strncmp(const char *str_1, const char *str_2, int n);
int istrncmp(const char *str_1, const char *str_2, int n);
int strnlen_terminator(const char *str, int max, char terminator);
char tolower(char s1);

#endif