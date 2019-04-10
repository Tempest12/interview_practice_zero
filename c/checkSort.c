int checkSort(int* array, int size)
{
    int index = 0;

    for(index = 0; index < size - 1; index++)
    {
        if(array[index] > array[index + 1])
        {
            return 0;
        }
    }

    return 1;
}