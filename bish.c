#include "bish.h"

void handleSuspend(int sig){
	if(sig != SIGTSTP)
		return;

	// Process runners execute default behaviour
	if(!shell->isShell){
		signal(SIGTSTP, SIG_DFL);
		raise(SIGTSTP);
	}
}

void handleContinue(int sig){
	if(sig != SIGCONT)
		return;

	// If process runner, resume current program if it exists
	if(!shell->isShell && shell->currentProgram->pid){
		kill(shell->currentProgram->pid, SIGCONT);
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
	// System command: fg (auto suspends first one for now)
	else if(!strcasecmp(p->args[0], FG)){
		// Continue process runner
		int *childPID = shell->children->val;
		kill(*childPID, SIGCONT);

		// Wait for process runner to finish
		int status;
		waitpid(*childPID, &status, WUNTRACED);
	}
	// No system command found.
	else{
		return false;
	}
	return true;
}

void runProcess(Process *process){
	// Ignore empty commands/Override with shell commands if detected
	if(!process->count || runShellCommand(process->programs[0]))
		return;

	// Create process runner
	process->pid = fork();

	// Parent aka the shell (waits for process runner to finish)
	if(process->pid){
		shell->isShell = true;

		int status;
		waitpid(process->pid, &status, WUNTRACED);
	}
	// Child aka process runner (runs through all processes)
	else{
		shell->isShell = false;

		// Run all programs, waiting for each one
		for (int i = 0; i < process->count; i++){
			shell->currentProgram = process->programs[i];
			runProgram(*process->programs[i], 0, 0);
		}
		exit(0);
	}
}

void processLine(){
	// Initialization and sanitization
	Process *process = malloc(sizeof(Process));
	shell->buffer[strlen(shell->buffer) - 1] = '\0';

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

	// Add new process to shell's children then run
	Node *newProcess = init(process, NULL);
	shell->children = newProcess;
	runProcess(process);
}

int main(){
	// Automatic flushing
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	signal(SIGTSTP, handleSuspend);
	signal(SIGCONT, handleContinue);

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