#ifndef NODE_HEADER
#define NODE_HEADER

#include <stdlib.h>

struct Node{
	void *val;
	struct Node *next;
};

typedef struct Node Node;

void freeList(Node *node);

#endif