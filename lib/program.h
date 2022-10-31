#ifndef PROGRAM_HEADER
#define PROGRAM_HEADER

#include "util.h"
#include "constants.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct Program{
	int pid;
	char **args;
	int argc;
	int in;
	int out;
} Program;

Program *parseProgram(char *line);
void runProgram(const Program p);

#endif