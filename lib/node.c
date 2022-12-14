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
 * @brief Free singly linked list from memory.
 * This includes its contents.
 * 
 * @param head start of linked list
 */
void fullFreeList(Node *node){
	while(node != NULL){
		Node *next = node->next;
		free(node->val);
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

/**
 * @brief Get node at specified index
 * 
 * @param node start of linked list
 * @param target target node to get (0-indexed)
 * @return the retrieved node 
*/
Node *getNode(Node *node, int target){
	while(node && target){
		node = node->next;
		target--;
	}
	return node;
}