#include "shell.h"

Program *parseProgram(const char line[]){
	Program *program = malloc(sizeof(Program));
	program->args = malloc(sizeof(char *));
	program->args[0] = "ls";

	return program;
}