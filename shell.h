#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "lib/util.h"

#define ERR_CMD ("Error: invalid command\n")
#define ERR_DIR ("Error: invalid directory\n")
#define MAX_BUFFER (1000)

typedef struct Shell{
	char buffer[MAX_BUFFER];
	char dir[PATH_MAX+1];
	int child;
} Shell;

typedef struct Program{
	char **args;
	int argc;
	int in;
	int out;
} Program;

typedef struct Process{
	Program **programs;
	int count;
} Process;

Program *parseProgram(char *line);
void freeProgram(Program *p);
void changeDirectory(const Program p);

#endif