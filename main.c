#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ITERATIVE 'i'
#define RECURSIVE 'r'

void printLongArray(long *arr, int arr_length);

bool inSequence(long *arr, int lookingFor);
long iterativeProcess(int seqLen);

bool recInSequence(long lookingFor, int currSeqLen);
long recamanRecursively(int term_number);

int main(int argc, char *argv[])
{

    if (argc < 3 || (argv[1][0] != ITERATIVE && argv[1][0] != RECURSIVE) ||
        atoi(argv[2]) < 1)
    {
        fprintf(stderr, "Usage: %s <i/r> <pos num>\n", argv[0]);
        return 1;
    }

    if (argv[1][0] == RECURSIVE)
    {
        int seqLen = atoi(argv[2]);
        long *recamanSeq = malloc(sizeof(long) * seqLen);

        for (int termNum = 0; termNum < seqLen; termNum++)
        {
            recamanSeq[termNum] = recamanRecursively(termNum);
        }

        printLongArray(recamanSeq, seqLen);

        free(recamanSeq);
    }
    else
    {
        iterativeProcess(atoi(argv[2]));
    }

    return 0;
}

void printLongArray(long *arr, int arr_length)
{
    while (arr_length--)
    {
        printf("%ld ", *arr++);
    }
    printf("\n");
}

bool inSequence(long *arr, int lookingFor)
{
    for (int idx = 0; (idx < sizeof(arr)); idx++)
    {
        if (lookingFor == arr[idx])
        {
            return true;
        }
    }
    return false;
}

long iterativeProcess(int seqLen)
{
    long *tempArr = malloc(sizeof(long) * seqLen);
    for (int termNum = 0; termNum <= seqLen; termNum++)
    {
        if (termNum == 0)
        {
            tempArr[termNum] = 0;
        }
        else if (termNum > 0)
        {
            int potentialTerm = tempArr[termNum - 1] - termNum;
            if (((inSequence(tempArr, potentialTerm)) == true) ||
                (potentialTerm < 0))
            {
                potentialTerm = tempArr[termNum - 1] + termNum;
                tempArr[termNum] = potentialTerm;
            }
            else
            {
                tempArr[termNum] = potentialTerm;
            }
        }
    }

    printLongArray(tempArr, seqLen);
    free(tempArr);

    return 0;
}

bool recInSequence(long lookingFor, int currSeqLen)
{
    if (currSeqLen == 0)
        return lookingFor == recamanRecursively(0);

    if (lookingFor == recamanRecursively(currSeqLen))
        return true;

    return recInSequence(lookingFor, currSeqLen - 1);
}

long recamanRecursively(int termNum)
{
    if (termNum == 0)
        return 0;

    long prevTerm = recamanRecursively(termNum - 1);

    long potentialTerm = prevTerm - termNum;
    bool validTerm =
        potentialTerm > 0 && !recInSequence(potentialTerm, termNum - 1);

    if (!validTerm)
        potentialTerm = prevTerm + termNum;

    return potentialTerm;
}