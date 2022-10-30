#include "bish.h"

void handleSuspend(int sig){
	if(sig != SIGTSTP)
		return;

}

void handleContinue(int sig){
	if(sig != SIGCONT)
		return;

	// If process runner, resume current program if it exists
	if(!shell->isShell){
		int status;
		kill(shell->currentProgram->pid, SIGCONT);
		waitpid(shell->currentProgram->pid, &status, WUNTRACED);
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
	// System command: jobs
	else if(!strcasecmp(p->args[0], JOBS)){
		Node *curr = shell->children;

		// Print out all suspended processes
		for (int i = 1; curr != NULL; i++){
			Process *process = curr->val;
			printf("[%d]", i);

			// Print out all programs in suspended process
			for (int j = 0; j < process->count; j++){
				Program *p = process->programs[j];
				// Print out all program args
				for (int h = 0; h < p->argc; h++){
					printf(" %s", p->args[h]);
				}
			}
			curr = curr->next;
			printf("\n");
		}
	}
	// System command: fg (auto suspends first one for now)
	else if(!strcasecmp(p->args[0], FG)){
		Process *p = shell->children->val;

		// Continue process runner and wait
		kill(p->pid, SIGCONT);
		int status;
		waitpid(p->pid, &status, WUNTRACED);
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

	// Add process to shell's children
	Node *newProcess = init(process, shell->children);
	shell->children = newProcess;

	// Parent aka the shell (creates & waits for process runner)
	if((process->pid = fork())){
		int status;
		waitpid(process->pid, &status, WUNTRACED);
	}
	// Child aka process runner (runs through all processes)
	else{
		shell->isShell = false;
		signal(SIGTSTP, SIG_DFL);

		// Run all programs, waiting for each one
		for (int i = 0; i < process->count; i++){
			shell->currentProgram = process->programs[i];
			runProgram(*process->programs[i], 0, 0);
		}
		exit(0);
	}
}

void processLine(){
	// Process initializaion and input sanitization
	Process *process = malloc(sizeof(Process));
	shell->buffer[strlen(shell->buffer) - 1] = '\0';

	// Split process string into program strings to be parsed
	Node *programStrings = split(shell->buffer, "|", &process->count);
	Program **programs = malloc(sizeof(Program*) * (process->count));
	for (int i = 0; i < process->count; i++){
		programs[i] = parseProgram(programStrings->val);
		programStrings = programStrings->next;
	}
	process->programs = programs;

	// Run Process
	runProcess(process);
}

int main(){
	// Automatic flushing
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	// Shell initialization
	shell = malloc(sizeof(Shell));
	shell->children = NULL;
	shell->isShell = true;
	getcwd(shell->dir, PATH_MAX);
	signal(SIGTSTP, handleSuspend);
	signal(SIGCONT, handleContinue);

	// Run through program
	while(true){
		printf("[bish %s]$ ", shell->dir);
		fgets(shell->buffer, MAX_BUFFER, stdin);
		processLine();
	}

	return 0;
}