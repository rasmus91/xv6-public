#include "types.h"
#include "stat.h"
#include "user.h"

int partition(int* array, int low, int high);

void quicksort(int* array, int low, int high);


int main(int argc, char* args[])
{
    if(argc <= 1)
    {
        printf(1, "Error: Quicksort needs more than 1 argument\n");
        exit();
    }

    int* numbers = malloc(sizeof(int) * (argc - 1));

    for(int i = 1; i < argc; i++)
    {
        numbers[i - 1] = atoi(args[i]);
    }

    quicksort(numbers, 0, (argc - 2));

    for(int i = 0; i < (argc - 1); i++)
    {
        if(i == (argc - 2))
        {
            printf(2, "%d\n", numbers[i]);
        }
        else
        {
            printf(2, "%d, ", numbers[i]);
        }
    }

    free(numbers);

    exit();
}

void quicksort(int* array, int low, int high)
{
    if(low < high)
    {
        int p = partition(array, low, high);
        quicksort(array, low, p - 1);
        quicksort(array, p + 1, high);
    }
}

int partition(int* array, int low, int high)
{
    int pivot = array[high];
    int i = low;
    for(int j = low; j < high; j++)
    {
        if(array[j] < pivot)
        {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
        }
    }
    int temp = array[i];
    array[i] = array[high];
    array[high] = temp;
    
    return i;
}

