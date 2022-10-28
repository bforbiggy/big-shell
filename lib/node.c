#include "node.h"

Node *init(void *val, Node *next){
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->next = next;
	return node;
}

/**
 * @brief Free singly linked list from memory.
 * This does not include its contents.
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

/**
 * @brief Converts a linkedlist into array
 * 
 * @param head start of linked list
 * @param count size of linked list
 */
void **toArray(Node *head, int count){
	void **arr = malloc(sizeof(void*) * (count+1));
	for(int i = 0; head != NULL; i++){
		arr[i] = head->val;
		head = head->next;
	}
	arr[count] = NULL;
	return arr;
}