#include "bish.h"

void handleSig(int sig){
	// Suspend child
	if(sig == SIGTSTP){
		if(shell->child){
			kill(shell->child, SIGTSTP);
		}
	}
}

void runProgram(const Program p){
	int status;
	shell->child = fork();

	// Parent process, aka "this"
	if(shell->child){
		waitpid(shell->child, &status, WUNTRACED);
	}
	// Execute child with specified IO
	else{
		shell->child = 0;
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

void processProgram(Program *program){
	// Ignore invalid programs
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
	// System command: fg
	else if(!strcasecmp(program->args[0], FG)){
		if(kill(shell->child, 0) != -1){
			kill(shell->child, SIGCONT);

			int status;
			waitpid(shell->child, &status, WUNTRACED);
		}
	}
	// Run normal program
	else{
		runProgram(*program);
	}
}

void processLine(){
	// Sanitize input then parse
	shell->buffer[strlen(shell->buffer) - 1] = '\0';
	Program *program = parseProgram(shell->buffer);
	processProgram(program);
}

int main(){
	// Automatic flushing
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	signal(SIGTSTP, handleSig);

	// Shell initialization
	shell = malloc(sizeof(Shell));
	getcwd(shell->dir, PATH_MAX);

	// Run through program
	while(true){
		printf("[bish %s]$ ", shell->dir);
		fgets(shell->buffer, MAX_BUFFER, stdin);
		processLine();
	}

	return 0;
}