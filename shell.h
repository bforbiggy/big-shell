#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "lib/util.h"

#define ERR_CMD ("Error: invalid command\n")
#define ERR_DIR ("Error: invalid directory\n")
#define MAX_BUFFER (1000)

typedef struct Program{
	int pid;
	char **args;
	int argc;
	int in;
	int out;
} Program;

typedef struct Process{
	int pid;
	Program **programs;
	int count;
} Process;

typedef struct Shell{
	char buffer[MAX_BUFFER];
	char dir[PATH_MAX+1];

	bool isShell;
	Node *children;
	Program *currentProgram;
} Shell;

Program *parseProgram(char *line);
void runProgram(const Program p, int pipeIn, int pipeOut);
void freeProgram(Program *p);
void changeDirectory(const Program p);

#endif