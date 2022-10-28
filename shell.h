#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <limits.h>
#include "lib/util.h"
#include "lib/node.c"

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

Program *parseProgram(char *line);

#endif