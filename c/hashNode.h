#ifndef _HASH_NODE_H
#define _HASH_NODE_H

typedef struct HashNode
{

	int key;
	void* value;

	struct HashNode* next;
}HashNode;

#endif