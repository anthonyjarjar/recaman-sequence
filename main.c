#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000
#define CACHE_SIZE 100

void printArray(int *arr, int arrLength);
bool recInSequence(int *cache, long lookingFor, int currSeqLen);
long recamanRecursively(int *cache, int termNum);
void addToCache(int *cache, int value, int *cacheSize);
void drawRecaman(SDL_Renderer *renderer, int *sequence, int seqLen);

int main(int argc, char *argv[])
{
    if ((argc < 2) || (atoi(argv[1]) < 1))
    {
        fprintf(stderr, "Usage: %s <pos num>\n", argv[0]);
        exit(-1);
    }

    int seqLen = atoi(argv[1]);

    int *cache = malloc((sizeof(int)) * CACHE_SIZE);
    if (cache == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    for (int idx = 0; idx < CACHE_SIZE; ++idx)
        cache[idx] = -1;

    int *sequence = malloc((sizeof(int)) * seqLen);
    if (sequence == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }

    for (int termNum = 0; termNum < seqLen; termNum++)
        sequence[termNum] = recamanRecursively(cache, termNum);

    printArray(sequence, seqLen);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        free(cache);
        free(sequence);
        exit(1);
    }

    SDL_Window *win = SDL_CreateWindow("Recaman Sequence Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(cache);
        free(sequence);
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(cache);
        free(sequence);
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    drawRecaman(renderer, sequence, seqLen);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    free(cache);
    free(sequence);

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
    for (int i = 0; i < currSeqLen; i++)
    {
        if (cache[i] == lookingFor)
        {
            return true;
        }
    }
    return false;
}

long recamanRecursively(int *cache, int termNum)
{
    if (termNum == 0)
    {
        cache[termNum] = 0;
        return cache[termNum];
    }

    long prevTerm = cache[termNum - 1];
    long potentialTerm = prevTerm - termNum;
    bool validTerm = (potentialTerm > 0) && (!recInSequence(cache, potentialTerm, termNum));

    if (!validTerm)
    {
        potentialTerm = prevTerm + termNum;
    }

    addToCache(cache, potentialTerm, &termNum);
    return potentialTerm;
}

void addToCache(int *cache, int value, int *cacheSize)
{
    if (*cacheSize < CACHE_SIZE)
    {
        cache[*cacheSize] = value;
        (*cacheSize)++;
    }
    else
    {
        for (int i = 1; i < CACHE_SIZE; i++)
        {
            cache[i - 1] = cache[i];
        }
        cache[CACHE_SIZE - 1] = value;
    }
}

void drawArc(SDL_Renderer *renderer, int x, int y, int radius, int startAngle, int endAngle)
{
    int prevX = x + radius * cos(startAngle * M_PI / 180);
    int prevY = y + radius * sin(startAngle * M_PI / 180);

    for (int angle = startAngle + 1; angle <= endAngle; angle++)
    {
        double rad = angle * M_PI / 180;
        int nextX = x + radius * cos(rad);
        int nextY = y + radius * sin(rad);
        SDL_RenderDrawLine(renderer, prevX, prevY, nextX, nextY);
        prevX = nextX;
        prevY = nextY;
    }
}

void drawRecaman(SDL_Renderer *renderer, int *sequence, int seqLen)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int x0 = WINDOW_WIDTH / 2;
    int y0 = WINDOW_HEIGHT / 2;
    int direction = 1;
    int scale = 5;

    for (int i = 1; i < seqLen; i++)
    {
        int x1 = x0 + (sequence[i] - sequence[i - 1]) * scale * direction;
        int radius = abs(sequence[i] - sequence[i - 1]) * scale / 2;
        int centerX = (x0 + x1) / 2;
        int centerY = y0;

        if (direction > 0)
        {
            drawArc(renderer, centerX, centerY, radius, 180, 360);
        }
        else
        {
            drawArc(renderer, centerX, centerY, radius, 0, 180);
        }

        direction *= -1;
        x0 = x1;
    }
}
