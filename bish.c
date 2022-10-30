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

// Runs shell process, returning true if it's a shell
bool runShellCommand(Program *p){
	// System command: change directory
	if(!strcasecmp(p->args[0], CD)){
		changeDirectory(*p);
		getcwd(shell->dir, PATH_MAX);
	}
	// System command: exit
	else if(!strcasecmp(p->args[0], EXIT)){
		free(shell);
		exit(0);
	}
	// System command: fg
	else if(!strcasecmp(p->args[0], FG)){
		if(kill(shell->child, 0) != -1){
			kill(shell->child, SIGCONT);
			int status;
			waitpid(shell->child, &status, WUNTRACED);
		}
	}
	// No system command found.
	else{
		return false;
	}
	return true;
}

void runProcess(Process *process){
	// Ignore empty processes
	if(!process->count){
		return;
	}

	// Run normal program if no shell command was found
	if(runShellCommand(process->programs[0]))
		return;

	// Run all programs in process (process->count)
	for (int i = 0; i < process->count; i++){ 
		runProgram(*process->programs[i]);
	}
}

void processLine(){
	// Initialization and sanitization
	Process *process = malloc(sizeof(Process));
	shell->buffer[strlen(shell->buffer) - 1] = '\0';
	shell->child = -1;

	// Split process string into program strings
	Node *programStrings = split(shell->buffer, "|", &process->count);
	Program **programs = malloc(sizeof(Program*) * (process->count));

	// Parse program strings into program
	for (int i = 0; i < process->count; i++)
	{
		Program *program = parseProgram((char*)programStrings->val);
		programs[i] = program;
		programStrings = programStrings->next;
	}
	process->programs = programs;

	runProcess(process);
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