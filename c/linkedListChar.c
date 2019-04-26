#include <stdio.h>
#include <stdlib.h>

#include "linkedListChar.h"


charList* createListChar(void)
{
	charList* list = malloc(sizeof(charList));

	if(list == NULL)
	{
		printf("Something terrible has happened. Malloc failed...\n");
		exit(1);
	}

	list->size = 0;
	list->head = NULL;

	return list;
}

charList* copyListChar(charList* master)
{
	charList* copy = createListChar();

	charNode* temp = master->head;

	while(temp != NULL)
	{
		addAtTail(copy, temp->value);
		temp = temp->next;
	}

	return copy;
}

void     destroyListChar(charList* list)
{
	charNode* temp = list->head;
	charNode* die = temp;

	while(temp != NULL)
	{
		die = temp->next;
		free(temp);
		temp = die;
	}

	free(list);
}

void addAtTail (charList* list, char value)
{
	charNode* newNode = malloc(sizeof(charNode));
	
	newNode->next = NULL;
	newNode->value = value;

	list->size++;

	if(list->size == 1)
	{
		list->head = newNode;
		return;
	}

	charNode* temp = list->head;

	while(temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = newNode;
}

char* buildString(charList* list)
{
	char* string = malloc(list->size + 1);
	int index = 0;
	charNode* temp = list->head;

	for(index = 0; index < list->size; index++)
	{
		string[index] = temp->value;
		temp = temp->next;
	}

	string[index] = '\0';

	return string;
}

int  getIndexOf(charList* list, char value)
{
	int index = 0;

	charNode* temp = list->head;

	while(temp != NULL)
	{
		if(temp->value == value)
		{
			return index;
		}
		else
		{
			temp = temp->next;
			index++;
		}
	}

	return -1;
}

char removeHead(charList* list)
{
	char answer = '\0';

	if(list->head != NULL)
	{
		list->size--;
		charNode* temp = list->head;
		list->head = list->head->next;
		answer = temp->value;
		free(temp);
	}

	return answer;
}
