#include "bish.h"

int parent = 1;
int bgID;

void handleSig(int sig){
	// Suspend
	if(sig == SIGTSTP){
		// Suspend child
		if(parent){
			kill(bgID, SIGTSTP);
		}
	}
	// Continue
	else if(sig == SIGCONT){
		// Should continue by default iunno
	}
}

void runProgram(const Program p){
	int status;
	int pid = fork();

	// Parent process, aka "this"
	if(pid){
		parent = 1;
		bgID = pid;
		printf("Waiting\n");
		waitpid(pid, &status, WCONTINUED | WUNTRACED);
		printf("Finished wait\n");
	}
	// Execute child with specified IO
	else{
		parent = 0;
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
		printf("IM RESUMING %d", bgID);
		kill(bgID, SIGCONT);
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
	// signal(SIGCONT, handleSig);

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