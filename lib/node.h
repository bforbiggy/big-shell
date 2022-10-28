#ifndef NODE_HEADER
#define NODE_HEADER

#include <stdlib.h>

typedef struct Node{
	void *val;
	struct Node *next;
}Node;

Node *init(void *val, Node *next);
void freeList(Node *node);
void **toArray(Node *head, int count);

#endif