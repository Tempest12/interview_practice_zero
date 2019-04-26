#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedListChar.h"

//  Find the longest non-repeating(Every character is unique) sub string.

//Aka for aabc answer is a[abc]

// Hard shit is stuff like:
// abcadeb a[bcade]b

// or

// cbaadeb cba[adeb]

char* findNR(char* str)
{
	int left = 0;
	int index = 0;
	int current = 0;
	int length = strlen(str);

	char hash[256];
	memset(hash, 0, 256);
	char* sub = NULL;

	charList* list = createListChar();
	charList* longest = createListChar();

	while(current < length)
	{
		//Check current character.  Then two things happen:
		// * Character is unique and we can add it
		// 
		// OR
		// 
		// * Character is a repeat and we have to redo our list:
		char temp = str[current];

		//printf("current is: %i\n", current);


		// Case One: (Unique character)
		if(hash[(size_t)temp] == 0)
		{
			current++;
		}
		else // Case Two: (Chracter is a repeat)
		{
			//Check against current longest:
			if(longest->size < list->size)
			{
				destroyListChar(longest);
				longest = copyListChar(list);
			}

			// How many things to get rid of?
			int kill = getIndexOf(list, temp);

			//Kill from the left until repeat dies:
			for(index = 0; index <= kill; index++)
			{
				char dying = removeHead(list);
				hash[(size_t)dying] = 0;
				left++;
			}

			current = left;
		}

		hash[(size_t)temp] = 1;
		addAtTail(list, temp);
	}


	if(list->size > longest->size)
	{
		sub = buildString(list);
	}
	else
	{
		sub = buildString(longest);
	}

	destroyListChar(list);
	destroyListChar(longest);

	return sub;
}

void runTest(char* testString, char* expected)
{
	char* temp = findNR(testString);

	printf("Testing \"%s\"...", testString);

	if(strcmp(temp, expected) == 0)
	{
		printf("passed\n");
	}
	else
	{
		printf("FAILED!. Expected: \"%s\" and got \"%s\".\n", expected, temp);
	}

	free(temp);
}

int main(int argc, char** argv)
{
	runTest("aabc", "abc");
	runTest("abcadeb", "bcade");
	runTest("cbaadeb", "adeb");

	return 0;
}