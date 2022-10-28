#include "shell.h"

Program *parseProgram(char *line){
	Program *program = malloc(sizeof(Program));

	// Split input string into args
	Node* node = split(line, " ", &program->argc);
	program->args = (char**)toArray(node, program->argc);
	freeList(node);
	
	return program;
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