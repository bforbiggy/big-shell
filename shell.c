#include "shell.h"

Program *parseProgram(char *line){
	Program *program = malloc(sizeof(Program));


	// Split input string into args
	int count;
	Node* node = split(line, " ", &count);
	program->args = toArray(node, count);
	freeList(node);
	
	return program;
}