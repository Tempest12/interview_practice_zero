#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashLink.h"
#include "hashFall.h"
#include "hashNode.h"

// Forward declarations:
void checkNodeContentsLink(HashLink* hashLink, int index, int chain, int key, char* data);

// Static data:
//static HashFall* hashFallHalf;
//static HashFall* hashFallThree;

static HashLink* hashLinkHalf;
static HashLink* hashLinkThree;

static char* valueZero = "Hello World";
static char* valueOne  = "GOFY";
static char* valueFive = "THWG";
static char* valueThirteen = "Red XIII";

void checkNodeContentsLink(HashLink* hashLink, int index, int chain, int key, char* data)
{
	HashNode* hashNode = getNodeAtIndexHashLink(hashLink, index, chain);

	if(hashNode == NULL)
	{
		printf("Null node found where we expected to find a node with key: %i, and value: \"%s\"\n", key, data);
		exit(1);
	}

	if(hashNode->key != key)
	{
		printf("Key compared failed. Failing key: %i. Expected %i.  Failing value: \"%s\".  Expected value: \"%s\".\n",
		       hashNode->key, key, (char*)hashNode->value, data);
		exit(1);
	}

	if(strcmp(data, (char*)hashNode->value))
	{
		printf("Value compare failed. Expected: \"%s\". Got: \"%s\"\n", data, (char*)hashNode->value);
		exit(1);
	}
}


void checkLinkInsert()
{
	insertValHashLink(hashLinkHalf,  0, valueZero);
	insertValHashLink(hashLinkHalf,  1, valueOne);
	insertValHashLink(hashLinkHalf,  5, valueFive);
	insertValHashLink(hashLinkHalf, 13, valueThirteen);

	//                      I  Ch Key
	checkNodeContentsLink(hashLinkHalf,  0, 0,  0, valueZero);
	checkNodeContentsLink(hashLinkHalf,  1, 0,  1, valueOne);
	checkNodeContentsLink(hashLinkHalf,  5, 0,  5, valueFive);
	checkNodeContentsLink(hashLinkHalf,  5, 1, 13, valueThirteen);

	insertValHashLink(hashLinkThree,  0, valueZero);
	insertValHashLink(hashLinkThree,  1, valueOne);
	insertValHashLink(hashLinkThree,  5, valueFive);
	insertValHashLink(hashLinkThree, 13, valueThirteen);

	printf("Didn't crash.\n");
}

void checkLinkFind();

int main(int argc, char** argv)
{
	hashLinkHalf  = createHashLink(0.5f);
	hashLinkThree = createHashLink(0.75f);

	checkLinkInsert();

	return 0;
}