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
		if(p.in){
			dup2(p.in, 0);
			close(p.in);
		}
		if(p.out){
			dup2(p.out, 1);
			close(p.out);
		}
		execvp(p.args[0], p.args);
	}
}

void processLine(Shell *shell){
	// Sanitize input then parse
	shell->buffer[strlen(shell->buffer) - 1] = '\0';
	Program *program = parseProgram(shell->buffer);
	if(program == NULL || !program->argc){
		return;
	}

	// System command: change directory
	if(!strcasecmp(program->args[0], CD)){
		changeDirectory(*program);
		getcwd(shell->dir, PATH_MAX);
	}
	// System command: exit
	else if(!strcasecmp(program->args[0], EXIT)){
		free(shell);
		exit(0);
	}
	// Normal command
	else{
		runProgram(*program);
	}
	// freeProgram(program);
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