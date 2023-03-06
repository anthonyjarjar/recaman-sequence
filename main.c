#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int arrLength);

bool recInSequence(int *cache, long lookingFor, int currSeqLen);
long recamanRecursively(int *cache, int termNum);

int main(int argc, char *argv[])
{

    if ((argc < 2) || (atoi(argv[1]) < 1))
    {
        fprintf(stderr, "Usage: %s <pos num>\n", argv[0]);
        exit(-1);
    }

    int seqLen = atoi(argv[1]);

    int *cache = malloc((sizeof(int)) * (seqLen));
    for (int idx = 0; idx < seqLen; ++idx)
        cache[idx] = -1;

    for (int termNum = 0; termNum < seqLen; termNum++)
        recamanRecursively(cache, termNum);

    printArray(cache, seqLen);

    free(cache);

    return 0;
}

void printArray(int *arr, int arrLength)
{
    int term = 1;
    while (arrLength--)
        printf("Term %d: %d\n", term++, *arr++);

    printf("\n");
}

bool recInSequence(int *cache, long lookingFor, int currSeqLen)
{
    if (currSeqLen == 0)
        return lookingFor == 0;

    if (lookingFor == cache[currSeqLen])
        return true;

    return recInSequence(cache, lookingFor, currSeqLen - 1);
}

long recamanRecursively(int *cache, int termNum)
{
    if (termNum == 0)
    {
        cache[termNum] = 0;
        return cache[termNum];
    }

    if (cache[termNum] == -1)
    {
        long prevTerm = cache[termNum - 1];
        long potentialTerm = prevTerm - termNum;
        bool validTerm = ((potentialTerm > 0) && (!recInSequence(cache, potentialTerm, termNum - 1)));

        if (!validTerm)
        {
            potentialTerm = prevTerm + termNum;
            cache[termNum] = potentialTerm;
            return cache[termNum];
        }

        cache[termNum] = potentialTerm;
        return cache[termNum];
    }
}