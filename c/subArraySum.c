#include <stdio.h>
#include <stdlib.h>

#define ANS_LEN 41

void subArraySum(int* array, int size, int targetSum, int* first, int* last)
{
    if(size <= 0)
    {
        *first = -1;
        *last = -1;
        return;
    }

    if(size == 1)
    {
        if(array[0] == targetSum)
        {
            *first = 0;
            *last = 0;
            return;
        }
        else
        {
            *first = -1;
            *last = -1;
        }
    }

    int currentSum = 0;
    int startIndex = 0;
    int endIndex = 1;
    currentSum = array[startIndex] + array[endIndex];

    while(startIndex < size)
    {
        if(currentSum == targetSum)
        {
            *first
        }
    }

    *first = -1;
    *last = -1; 
}

void runTest(int* array, int size, int targetSum)
{
    char answerString[ANS_LEN];

    int count = 0;
    int index = 0;

    answerString[ANS_LEN - 1] = '\0';

    count = snprintf(answerString, ANS_LEN, "Checking:");

    for(index = 0; index < size; index++)
    {
        count += snprintf(&(answerString[count]), ANS_LEN - count, " %i", array[index]);
    }

    for(index = count; index < ANS_LEN - 1; index++)
    {
        answerString[index] = '.';
    }

    printf("%s", answerString);
    int firstIndex = 0;
    int lastIndex = 0;
    subArraySum(array, size, targetSum, &firstIndex, &lastIndex);

    printf(" First: %i Last: %i\n", firstIndex, lastIndex);
}

int main(int argc, char** argv)
{
    printf("Hello World!\n");

    return 0;
}
