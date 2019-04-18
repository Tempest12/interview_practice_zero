#ifndef _HASH_LINK_H
#define _HASH_LINK_H

struct HashNode;

typedef struct HashLink
{

	struct HashNode** table;
	int size;
	int maxSize;
	float loadPercent;

}HashLink;

// Table operations:
HashLink* createHashLink(float loadPercent);
void      destroyHashLink(HashLink* target);

// Meta operations:
struct HashNode*  getNodeAtIndexHashLink(HashLink* hashLink, int index, int chain);
int               getChainLengthHashLink(HashLink* hashLink, int index);
struct HashNode** getChainArrayHashLink (HashLink* hashLink, int* outSize);

// Node Operations:
void  insertValHashLink(HashLink* hashLink, int key, void* value);
void* findValHashLink  (HashLink* hashLink, int key);
void* removeValHashLink(HashLink* hashLink, int key);

#endif