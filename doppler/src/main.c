#include <stdio.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600
#define MAX_WAVES 1000

typedef struct
{
    float x, y
} Vehicle;

typedef struct
{
    float x, y, r
} Soundwave;

void propagate_waves(Soundwave* waves, unsigned int n)
{
    for (int i = 0; i < n; i++)
    {
        waves[i].r += 10;
    }
}

void emit_new_wave(Soundwave* waves, float x, float y, unsigned int idx)
{
    waves[idx] = (Soundwave) {x, y, 55};
}

int main(int argc, char **argv)
{
    InitWindow(WIDTH, HEIGHT, "Doppler Effect");

    Vehicle vehicle = (Vehicle) {400, 400};
    Soundwave waves[MAX_WAVES];
    unsigned int current_waves = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        propagate_waves(waves, current_waves);
        emit_new_wave(waves, vehicle.x, vehicle.y, current_waves);
        if (current_waves < MAX_WAVES) current_waves++;

        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawCircle(vehicle.x, vehicle.y, 50, WHITE);
        for (int i = 0; i < current_waves; i++)
        {
            DrawCircleLines(waves[i].x, waves[i].y, waves[i].r, WHITE);
        }

        EndDrawing();
    }

    return 0;
}