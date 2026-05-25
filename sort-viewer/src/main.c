#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600
#define NUM_ITEMS 30

int array[NUM_ITEMS];
int idx = 0;
bool sorted = false;
int amount_sorted = 0;

void init_array(int inverse)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (inverse) array[i] = NUM_ITEMS - i + 1;
        else array[i] = rand() % NUM_ITEMS + 1;
    }
}

void draw_array()
{
    int x_offset = 30;
    int y_offset;
    int width = (WIDTH - (x_offset * 2)) / (NUM_ITEMS + (NUM_ITEMS * 0.1));
    int gap;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        y_offset = array[i] * 10;
        gap = i * (width + 3);
        Color color;

        if (i == idx) color = RED;
        else if (sorted) color = GREEN;
        else color = LIGHTGRAY;

        DrawRectangle(x_offset - 5 + gap, HEIGHT * 0.8 - y_offset, width, y_offset, color);
    }
}

void swap(int *n1, int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void bubble_step()
{
    if (idx >= NUM_ITEMS - 1)
    {
        if (amount_sorted == NUM_ITEMS) sorted = true;
        idx = 0;
    }
    else
    {
        if (array[idx] > array[idx + 1]) 
        {
            amount_sorted = 0;
            swap(&array[idx], &array[idx + 1]);
        }

        idx++;
    }
}

int main(int argc, char **argv)
{
    bool inverse;
    if (argc == 0 || argc > 2 || argv[1] == "-h")
    {
        printf("Usage: %s <options>\n", argv[0]);
        printf("Options:\n \t-h\tHelp menu\n\t-r\tRandom order\n\t-i\tInverse order\n");
        inverse = false;
    }
    else if (argc == 1 || (argc == 2 && argv[1] == "-r")) inverse = false;
    else if (argc == 2 && argv[1] == "-i") inverse = true; 

    InitWindow(WIDTH, HEIGHT, "Sorting Algorithm Viewer");

    SetTargetFPS(60);

    srand(time(NULL));

    init_array(inverse);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        draw_array();

        EndDrawing();

        bubble_step();

        if (!sorted && amount_sorted != NUM_ITEMS) amount_sorted++;
    }
    
    CloseWindow();
}