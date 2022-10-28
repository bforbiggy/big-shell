#include "node.h"

Node *init(void *val, Node *next){
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->next = NULL;
	return node;
}

/**
 * @brief Free singly linked list by value.
 * This assumes the l
 * 
 * @param head start of linked list
 */
void freeList(Node *node){	
	while(node != NULL){
		Node *next = node->next;
		free(node->val);
		free(node);
		node = next;
	}
}