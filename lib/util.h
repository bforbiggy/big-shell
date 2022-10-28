#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"

Node *split(char *string, const char delim[], int *size);
bool isOperator(char c);
int lastIndex(const char str[], char c);
bool exists(const char *path);

#endif