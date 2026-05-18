#include <stdio.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, char **argv)
{
    InitWindow(WIDTH, HEIGHT, "Doppler Effect");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        
        EndDrawing();
    }

    return 0;
}