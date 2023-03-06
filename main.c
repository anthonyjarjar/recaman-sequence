#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define RECURSIVE 'r'

//! TO DO: GIT PUSH!!!, and fix syntax, such as unecessary {} on if and loop statements

void printArray(int *arr, int arrLength);

bool recInSequence(int *cache, long lookingFor, int currSeqLen);
long recamanRecursively(int *cache, int termNum);

int main(int argc, char *argv[])
{

    // Preforms input validation
    if ((argc < 2) || (atoi(argv[1]) < 1))
    {
        fprintf(stderr, "Usage: %s <pos num>\n", argv[0]);
        return 1;
    }

    // Declares sequence length, and creates an array ready to store the sequence
    int seqLen = atoi(argv[1]);

    int *cache = malloc((sizeof(int)) * (seqLen));
    for (int idx = 0; idx < seqLen; ++idx)
        cache[idx] = -1;

    // Preforms the loop to create the sequence
    for (int termNum = 0; termNum < seqLen; termNum++)
    {
        printf("."); // Temporary loading visuilization
        recamanRecursively(cache, termNum);
    }

    printf("\n"); // Using for format
    // Prints the sequence
    printArray(cache, seqLen);

    free(cache);

    return 0;
}

void printArray(int *arr, int arrLength)
{
    while (arrLength--)
        printf("%d ", *arr++);

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