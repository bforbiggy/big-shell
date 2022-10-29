#include "shell.h"

Program *parseProgram(char *line){
	Program *program = malloc(sizeof(Program));
	program->in = 0;
	program->out = 0;

	// Split input string into args
	Node* node = split(line, " ", &program->argc);
	if(!program->argc)
		return program;

	// Convert arg linkedlist to arg array
	program->args = (char**)toArray(node, program->argc);
	// freeList(node);

	// IO Redirection
	for(int i = 0; i < program->argc; i++){
		if(strncmp(program->args[i], ">>", 2) == 0){
			if(program->out){
				fprintf(stderr, ERR_CMD);
				return NULL;
			}

			program->args[i] = NULL;
			program->out = open(program->args[i+1], O_CREAT|O_WRONLY|O_APPEND, S_IRUSR|S_IWUSR);
		}
		else if(strncmp(program->args[i], ">", 1) == 0){
			if(program->out){
				fprintf(stderr, ERR_CMD);
				return NULL;
			}

			program->args[i] = NULL;
			program->out = open(program->args[i+1], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
		}
		else if(strncmp(program->args[i], "<", 1) == 0){
			if(program->in){
				fprintf(stderr, ERR_CMD);
				return NULL;
			}

			program->args[i] = NULL;
			program->in = open(program->args[i+1], O_RDONLY);
		}
	}
	
	return program;
}

void freeProgram(Program *p){
	for(int i = 0; i < p->argc; i++){
		free(p->args[i]);
	}
	free(p);
}

void changeDirectory(const Program p){
	// If there is an invalid number of arguments, fail function
	if(p.argc != 2){
		fprintf(stderr, ERR_CMD);
		return;
	}
	
	// Change directory, printing an error on fail
	if(chdir(p.args[1]) == -1){
    fprintf(stderr, ERR_DIR);
  }
}