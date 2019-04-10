#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checkSort.h"

#define ANS_LEN 41
#define TEST_NUM 3 //8

void iterativeInplace(int* array, int size)
{
    int bandSize = 2;
    int bandCount = 0;
    int bandIndex = 0;

    int leftSize = 0;
    int leftStart = 0;
    int leftCount = 0;

    int rightSize = 0;
    int rightStart = 0;
    int rightCount = 0;

    int answerIndex = 0;
    int startIndex = 0;
    int odd = 0;
    int round = 0;

    while(bandSize < size)
    {
        bandCount = size / bandSize;

        printf("Round info %i:\n", round);
        printf("Band Size: %i\n", bandSize);

        for(bandIndex = 0; bandIndex < bandCount; bandIndex++)
        {
            leftSize = bandSize >> 1;
            rightSize = bandSize >> 1;

            //Set Starts:
            startIndex = bandSize * bandIndex;
            leftStart = startIndex;
            rightStart = leftStart + leftSize;
            answerIndex = startIndex;

            //Set Ends: (Make sure to adjust right end if bigger than array)
            leftCount = leftSize;
            rightCount = rightSize;

            if((rightStart + rightCount ) > size)
            {
                rightCount = size - rightStart; 
            }


            printf("\tBand Index: %i\n", bandIndex);
            printf("\n");
            printf("\tLeft Count: %i\n", leftCount);
            printf("\tLeft Start: %i\n", leftStart);
            printf("\n");
            printf("\tRight Count: %i\n", rightCount);
            printf("\tRight Start: %i\n", rightStart);
            printf("\n");
        }

        bandSize *= 2;
        round++;
    }
}

void recursive(int* array, int size)
{
    int odd = 1 & size;

    int* left = NULL;
    int* right = NULL;

    int leftSize = size >> 1;
    int rightSize = (size >> 1) + odd;

    if(size <= 1)
    {
        return;
    }

    left = malloc(leftSize * sizeof(int));
    right = malloc(rightSize * sizeof(int));

    if(left == NULL || right == NULL)
    {
        return;
    }

    memcpy(left, array, leftSize * sizeof(int));
    memcpy(right, &(array[leftSize]), rightSize * sizeof(int));

    //Split and call again:
    recursive(left, leftSize);

    //Combine left and right:
    recursive(right, rightSize);

    //Merge:
    int leftIndex = 0;
    int rightIndex = 0;
    int answerIndex = 0;

    while(leftIndex < leftSize && rightIndex < rightSize)
    {
        //Left smaller than right, move left:
        if(left[leftIndex] < right[rightIndex])
        {
            array[answerIndex] = left[leftIndex];
            leftIndex++;
            answerIndex++;
        }
        //Left bigger than right, move right:
        else
        {
            array[answerIndex] = right[rightIndex];
            rightIndex++;
            answerIndex++;
        }
    }

    //Dump any remaining values:
    while(leftIndex < leftSize)
    {
        array[answerIndex] = left[leftIndex];
        leftIndex++;
        answerIndex++;
    }

    while(rightIndex < rightSize)
    {
        array[answerIndex] = right[rightIndex];
        rightIndex++;
        answerIndex++;
    }

    //Free left and right:
    free(left);
    free(right);
}

void runTest(int* array, int size)
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

    int* copy = malloc(size * sizeof(int));

    memcpy(copy, array, size * sizeof(index));

    recursive(array, size);
    iterativeInplace(array, size);

    //printf("%s", answerString);

    if(checkSort(array, size) == 1)
    {
        //printf("recur_passed ");
    }
    else
    {
        //printf("recur_FAILED ");
    }

    if(checkSort(copy, size) == 1)
    {
        //printf("iter_passed\n");
    }
    else
    {
        // printf("iter_FAILED\n");
    }

    free(copy);
}

int main(int argc, char** argv)
{
    int index = 0;
    int testTable[TEST_NUM][11] =  {{ 0, 0},
                                    { 1, 1},
                                    { 7, 7, 3, 4, 5, 7, 6, 7,}};
                                    /*{ 2, 7, 6},
                                    { 3, 5, 4, 3},
                                    { 4, 1, 2, 3, 4},
                                    { 5, 1, 4, 2, 3, 5},
                                    { 6, 9, 8, 5, 6, 4, 7},
                                    { 7, 7, 3, 4, 5, 7, 6, 7,}};*/

    for(index = 0; index < TEST_NUM; index++)
    {
        runTest(&(testTable[index][1]), testTable[index][0]);
    }

    return 0;
}