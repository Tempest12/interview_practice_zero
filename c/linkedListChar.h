#ifndef _LINKED_LIST_CHAR_H
#define _LINKED_LIST_CHAR_H

typedef struct charNode
{
	char value;
	struct charNode* next;
}charNode;

typedef struct charList
{
	charNode* head;
	int size;
}charList;

charList* createListChar();
charList* copyListChar(charList* master);
void      destroyListChar();

void  addAtTail  (charList* list, char value);
char* buildString(charList* list);
char  removeHead (charList* list);
int   getIndexOf (charList* list, char value);

#endif