#include "shell.h"

Program *parseProgram(char *line){
	Program *program = malloc(sizeof(Program));
	program->args = malloc(sizeof(char *) * 1);
	program->args[0] = "ls";

	// Linkedlist of args
	int count;
	Node* head = split(line, " ", &count);
	while(head != NULL){
		printf("Node value:%s\n", (char*)head->val);
		head = head->next;
	}
	return program;
}