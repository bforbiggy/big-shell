#include "shell.h"

void changeDirectory(Shell *shell, const Program p){
	// If there is an invalid number of arguments, fail function
	if(p.argc != 2){
		fprintf(stderr, ERR_CMD);
		return;
	}
	
	// Change directory, printing an error on fail
	if(chdir(p.args[1]) == -1){
    fprintf(stderr, ERR_DIR);
  }
	else{
		getcwd(shell->dir, PATH_MAX);
	}
}

void jobs(Shell *shell){
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

void fg(Shell *shell, const Program p){
	if(p.argc != 2){
		fprintf(stderr, ERR_CMD);
	}
	int index = atoi(p.args[1]) - 1;

	printf("Yo printing out node #%d\n", index);
	// Continue process
	Process *process = getNode(shell->children, index)->val;
	kill(process->pid, SIGCONT);
	
	// Wait for process
	int status;
	waitpid(process->pid, &status, WUNTRACED);
}

void shellExit(Shell *shell){
	free(shell);
	exit(0);
}