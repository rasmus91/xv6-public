#include "types.h"
#include "stat.h"
#include "user.h"

struct intList {

    int* numbers;
    int length;

};


int* Mergesort(int length, int* numbers);

int main(int argc, char* args[])
{

    /*if(argc != 2)
    {
        exit();
    }*/

    //char* numbersInArgs = args[1];

    struct intList mergeList; //= //BuildNumberArray(numbersInArgs);

    mergeList.numbers = malloc(sizeof(int) * argc - 1);
    mergeList.length = argc - 1;

    for(int i = 1; i < argc; i++)
    {
        int number = atoi(args[i]);
        mergeList.numbers[i - 1] = number;
    }

    mergeList.numbers = Mergesort(mergeList.length, mergeList.numbers);

    for(int i = 0; i < mergeList.length; i++)
    {
        if(i < (mergeList.length - 1))
        {
            printf(2, "%d, ", mergeList.numbers[i]);
        }
        else
        {
            printf(2, "%d\n", mergeList.numbers[i]);
        }
    }

    free(mergeList.numbers);

    exit();
}



int* Mergesort(int length, int numbers[])
{
    if(length > 1)
    {
        int midPosition = length / 2;

        int* firstHalf = malloc(sizeof(int) * midPosition);
        int* secondHalf = malloc(sizeof(int) * (length - midPosition));

        for(int i = 0; i < length; i++)
        {
            if(i < midPosition)
            {
                firstHalf[i] = numbers[i];
            }
            else
            {
                secondHalf[i - midPosition] = numbers[i];
            }
        }

        firstHalf = Mergesort(midPosition, firstHalf);
        secondHalf = Mergesort(length - midPosition, secondHalf);

        int cFIndex = 0;
        int cSIndex = 0;

        for(int i = 0; i < length; i++)
        {
            if(cFIndex < midPosition && cSIndex < (length - midPosition))
            {
                if(firstHalf[cFIndex] < secondHalf[cSIndex])
                {
                    numbers[i] = firstHalf[cFIndex];
                    cFIndex++;
                }
                else
                {
                    numbers[i] = secondHalf[cSIndex];
                    cSIndex++;
                }
            }
            else if(cFIndex >= midPosition)
            {
                numbers[i] = secondHalf[cSIndex];
                cSIndex++;
            }
            else if(cSIndex >= (length - midPosition))
            {
                numbers[i] = firstHalf[cFIndex];
                cFIndex++;
            }
            
        }

        free(firstHalf);
        free(secondHalf);
    }

    return numbers;
}
