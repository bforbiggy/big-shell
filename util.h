#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void split(char **args, char *string, const char delim[]);
bool isOperator(char c);
int lastIndex(const char str[], char c);
bool exists(const char *path);

#endif