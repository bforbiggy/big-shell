#include "node.h"

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