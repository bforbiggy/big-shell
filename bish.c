#include "bish.h"

void runProgram(const Program p){
	int status;
	int pid = fork();

	// Parent process, aka "this"
	if(pid){
		waitpid(pid, &status, 0);
	}
	// Execute child with specified IO
	else{
		execvp(p.args[0], p.args);
	}
}

void processLine(Shell *shell){
	// Sanitize input
	char *buffer = shell->buffer;
	buffer[strlen(buffer) - 1] = '\0';

	// Run program
	Program *program = malloc(sizeof(Program));
	program->args = malloc(sizeof(char *) * 1);
	program->args[0] = "ls";
	runProgram(*program);
}

int main(){
	// Automatic flushing
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	// Shell initialization
	Shell *shell = malloc(sizeof(shell));
	getcwd(shell->dir, PATH_MAX);

	// Run through program
	while(true){
		printf("[bish %s]$ ", shell->dir);
		fgets(shell->buffer, MAX_BUFFER, stdin);
		processLine(shell);
	}

	return 0;
}