#include "bish.h"

void runProgram(const Program p){
	int pid = fork();

	// Parent process, aka "this"
	if(pid){
		int status;
		waitpid(pid, &status, 0);
	}
	// Execute child with specified IO
	else{
		execvp(p.args[0], p.args);
	}
}

void processLine(Shell *shell){
	// Sanitize input then parse
	shell->buffer[strlen(shell->buffer) - 1] = '\0';
	Program *program = parseProgram(shell->buffer);

	// System command: change directory
	if(!strcasecmp(program->args[0], CD)){
		changeDirectory(*program);
		getcwd(shell->dir, PATH_MAX);
	}
	// System command: exit
	else if(!strcasecmp(program->args[0], EXIT)){
		exit(0);
	}
	else runProgram(*program);
	free(program);
}

int main(){
	// Automatic flushing
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	// Shell initialization
	Shell *shell = malloc(sizeof(Shell));
	getcwd(shell->dir, PATH_MAX);

	// Run through program
	while(true){
		printf("[bish %s]$ ", shell->dir);
		fgets(shell->buffer, MAX_BUFFER, stdin);
		processLine(shell);
	}

	return 0;
}