#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define NUM_ITEMS 10

int array[NUM_ITEMS];

void init_array(int inverse)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (inverse) array[i] = NUM_ITEMS - i + 1;
        else array[i] = rand() % NUM_ITEMS + 1;
    }
}

int main(int argc, char **argv)
{
    int inverse;
    if (argc == 0 || argc > 2 || argv[1] == "-h")
    {
        printf("Usage: %s <options>\n", argv[0]);
        printf("Options:\n \t-h\tHelp menu\n\t-r\tRandom order\n\t-i\tInverse order\n");
        inverse = 0;
    }
    else if (argc == 1 || (argc == 2 && argv[1] == "-r")) inverse = 0;
    else if (argc == 2 && argv[1] == "-i") inverse = 1; 

    InitWindow(WIDTH, HEIGHT, "Sorting Algorithm Viewer");

    srand(time(NULL));

    init_array(inverse);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawRectangle(50, 50, 30, 100, LIGHTGRAY);

        EndDrawing();
    }
    
    CloseWindow();
}