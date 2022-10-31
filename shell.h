#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "lib/util.h"
#include "lib/program.h"
#include "lib/constants.h"


typedef struct Process{
	int pid;
	Program **programs;
	int count;
} Process;

typedef struct Shell{
	char buffer[MAX_BUFFER];
	char dir[PATH_MAX+1];

	bool isShell;

	Node *children; // Most recent first
	Program *currentProgram;
} Shell;

void changeDirectory(Shell *shell, const Program p);
void jobs(Shell *shell);
void fg(Shell *shell, const Program p);
void shellExit(Shell *shell);

#endif