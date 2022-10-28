#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <limits.h>

#define MAX_BUFFER (1000)

typedef struct Shell{
	char buffer[MAX_BUFFER];
	char dir[PATH_MAX+1];
} Shell;

typedef struct Program{
	char **args;
	int in;
	int out;
} Program;

#endif