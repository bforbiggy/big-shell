#include "shell.h"

Program *parseProgram(char *line){
	Program *program = malloc(sizeof(Program));


	// Split input string into args
	int count;
	Node* node = split(line, " ", &count);
	Node* head = node;

	// Merge arguments into array
	program->args = malloc(sizeof(char*) * (count+1));
	for(int i = 0; i < count; i++){
		program->args[i] = node->val;
		node = node->next;
	}
	program->args[count] = NULL;
	freeList(head);
	return program;
}