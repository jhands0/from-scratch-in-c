#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, char **argv)
{
    InitWindow(WIDTH, HEIGHT, "Sorting Algorithm Viewer");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawRectangle(50, 50, 30, 100, LIGHTGRAY);

        EndDrawing();
    }
    
    CloseWindow();
}