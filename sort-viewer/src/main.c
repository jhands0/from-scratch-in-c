#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define NUM_ITEMS 50

int array[NUM_ITEMS];

void init_array(int inverse)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (inverse) array[i] = NUM_ITEMS - i + 1;
        else array[i] = rand() % NUM_ITEMS + 1;
    }
}

void draw_array(Color color)
{
    int x_offset = 30;
    int y_offset;
    int width = (WIDTH - (x_offset * 2)) / (NUM_ITEMS + (NUM_ITEMS * 0.1));
    int gap;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        y_offset = array[i] * 5;
        gap = i * (width + 3);
        DrawRectangle(x_offset - 5 + gap, HEIGHT * 0.8 - y_offset, width, y_offset, color);
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

        draw_array(LIGHTGRAY);

        EndDrawing();
    }
    
    CloseWindow();
}