#include "node.h"

Node *init(void *val, Node *next){
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->next = next;
	return node;
}

/**
 * @brief Free singly linked list.
 * 
 * @param head start of linked list
 */
void freeList(Node *node){	
	while(node != NULL){
		Node *next = node->next;
		free(node);
		node = next;
	}
}