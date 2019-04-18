#include <stdio.h>
#include <stdlib.h>

#include "hashNode.h"
#include "hashLink.h"

//Forward Declarations:
void static resizeHashLink(HashLink* hashLink);
int  static resizeNeeded  (HashLink* hashLink);
void static insertNode(HashLink* table, HashNode* newNode);

//Internal Helper Functions:
void static resizeHashLink(HashLink* hashLink)
{

}

int static resizeNeeded(HashLink* hashLink)
{
	return ((float)(hashLink->size + 1) / (float)(hashLink->maxSize)) > hashLink->loadPercent;
}

void static insertNode(HashLink* hashLink, HashNode* newNode)
{
	int modKey = newNode->key % hashLink->maxSize;

	// Start new chain:
	if(hashLink->table[modKey] == NULL)
	{
		hashLink->table[modKey] = newNode;
	}
	// Walk Exsisting chain:
	else
	{
		HashNode* last = hashLink->table[modKey];

		while(last->next != NULL)
		{
			last = last->next;
		}

		last->next = newNode;
	}

	hashLink->size++;
}

// Table operations:
HashLink* createHashLink(float loadPercent)
{
	HashLink* hashLink = malloc(sizeof(hashLink));

	if(hashLink == NULL)
	{
		printf("Failed to allocate HashLink.\n");
		exit(1);
	}

	hashLink->size = 0;
	hashLink->maxSize = 8;
	hashLink->loadPercent = loadPercent;
	hashLink->table = malloc(sizeof(void*) * hashLink->maxSize);

	if(hashLink->table == NULL)
	{
		printf("Failed to allocate storage table of HashLink.\n");
		exit(1);
	}

	return hashLink;
}

void      destroyHashLink(HashLink* target)
{
	free(target->table);
	free(target);
}

// Meta operations:
HashNode*  getNodeAtIndexHashLink(HashLink* hashLink, int index, int chain)
{
	HashNode* temp = hashLink->table[index];

	while(temp != NULL && chain > 0)
	{
		temp = temp->next;
		chain--;
	}

	return temp;
}

int        getChainLengthHashLink(HashLink* hashLink, int index)
{
	return 0;
}

HashNode** getChainArrayHashLink (HashLink* hashLink, int* outSize)
{
	return NULL;
}

// Node Operations:
void  insertValHashLink(HashLink* hashLink, int key, void* value)
{
	HashNode* newNode = malloc(sizeof(HashNode));

	if(newNode == NULL)
	{
		printf("Failed to allocate newNode in HashLink\n");
		exit(1);
	}

	if(resizeNeeded(hashLink) != 0)
	{
		resizeHashLink(hashLink);
	}

	newNode->key   = key;
	newNode->value = value;
	newNode->next = NULL;

	insertNode(hashLink, newNode);
}

void* findValHashLink(HashLink* hashLink, int key)
{
	int modKey = key % hashLink->maxSize;
	HashNode* chain = hashLink->table[modKey];
	void* value = NULL;

	while(chain != NULL)
	{
		if(chain->key == key)
		{
			value = chain->value;
		}
		else
		{
			chain = chain->next;
		}
	}

	return value;
}

void* removeValHashLink(HashLink* hashLink, int key)
{
	return NULL;
}
