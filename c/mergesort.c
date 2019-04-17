#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checkSort.h"

#define ANS_LEN 41
#define TEST_NUM 4 //8

void iterativeInplace(int* array, int size)
{
    int bandSize = 2;
    int bandCount = 0;
    int bandIndex = 0;

    int leftSize = 0;
    int leftIndex = 0;
    int leftCount = 0;

    int rightSize = 0;
    int rightIndex = 0;
    int rightCount = 0;

    int round = 0;

    /*printf("Size: %i\n", size);*/

    while(bandSize <= size)
    {
        bandCount = size / bandSize;

        /*printf("Round info %i:\n", round);
        printf("Band Size: %i\n", bandSize);
        printf("Band Count: %i\n", bandCount);*/

        for(bandIndex = 0; bandIndex < bandCount; bandIndex++)
        {
            leftSize = bandSize >> 1;
            rightSize = bandSize >> 1;

            //Set Starts:
            leftIndex = bandSize * bandIndex;
            rightIndex = leftIndex + leftSize;

            //Set Ends: (Make sure to adjust right end if bigger than array)
            leftCount = leftSize;
            rightCount = rightSize;

            if((rightIndex + rightCount ) > size)
            {
                rightCount = size - rightIndex; 
            }


            /*printf("\tBand Index: %i\n", bandIndex);
            printf("\n");
            printf("\t\tLeft Count: %i\n", leftCount);
            printf("\t\tLeft Start: %i\n", leftIndex);
            printf("\n");
            printf("\t\tRight Count: %i\n", rightCount);
            printf("\t\tRight Start: %i\n", rightIndex);
            printf("\n");*/

            while(leftCount > 0 && rightCount > 0)
            {
                //Two scenarios here:
                //Left is smaller than right (or tied.) in which case we just move on.
                if(array[leftIndex] <= array[rightIndex])
                {
                    leftCount--;
                    leftIndex++;
                }
                //Right is smaller in which case we need to swap right into left:
                else
                {
                    int temp = array[leftIndex];
                    array[leftIndex] = array[rightIndex];
                    array[rightIndex] = temp;

                    leftIndex++;
                    rightIndex++;
                    rightCount--;
                }
            }
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
    iterativeInplace(copy, size);

    printf("%s", answerString);

    if(checkSort(array, size) == 1)
    {
        printf("recur_passed ");
    }
    else
    {
        printf("recur_FAILED ");
    }

    if(checkSort(copy, size) == 1)
    {
        printf("iter_passed\n");
    }
    else
    {
        printf("iter_FAILED. ");
        printf("Failing answer:");
        for(index = 0; index < size; index++)
        {
            printf(" %i", copy[index]);
        }

        printf("\n");
    }

    free(copy);
}

int main(int argc, char** argv)
{
    int index = 0;
    int testTable[TEST_NUM][11] =  {{ 0, 0},
                                    { 1, 1},
                                    { 7, 7, 3, 4, 5, 7, 6, 7,},
                                    { 8, 2, 1, 3, 4, 8, 6, 7, 5}};
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