#include "program.h"

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

// Run program and sets program's pid
void runProgram(Program p, int pipeIn, int pipeOut){
	int status;
	p.pid = fork();

	// Parent: Wait for process to finish
	if(p.pid){
		waitpid(p.pid, &status, WUNTRACED);
	}
	// Child: Run process
	else{
		// Set input if available
		int in = p.in ? p.in : pipeIn;
		if(in){
			dup2(in, 0);
			close(in);
		}

		// Set output if available
		int out = p.out ? p.out : pipeOut;
		if(out){
			dup2(out, 1);
			close(out);
		}

		execvp(p.args[0], p.args);
	}
}