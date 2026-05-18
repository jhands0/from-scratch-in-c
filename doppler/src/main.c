#include <stdio.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600
#define MAX_WAVES 1000
#define WAVE_SPEED 20

typedef struct
{
    float x, y
} Vehicle;

typedef struct
{
    float x, y, r
} Soundwave;

void propagate_waves(Soundwave* waves, unsigned int n, float delta)
{
    for (int i = 0; i < n; i++)
    {
        waves[i].r += WAVE_SPEED * delta;
    }
}

void emit_new_wave(Soundwave* waves, float x, float y, unsigned int idx)
{
    waves[idx % MAX_WAVES] = (Soundwave) {x, y, 35};
}

int main(int argc, char **argv)
{
    InitWindow(WIDTH, HEIGHT, "Doppler Effect");

    Vehicle vehicle = (Vehicle) {400, 400};
    Soundwave waves[MAX_WAVES];
    unsigned int current_waves = 0;
    float interval = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float delta_time = GetFrameTime();

        interval += delta_time;
        if (interval > 1.0f)
        {
            emit_new_wave(waves, vehicle.x, vehicle.y, current_waves);
            if (current_waves < MAX_WAVES) current_waves++;
            interval = 0.0f;

        }

        propagate_waves(waves, current_waves, delta_time);

        if (IsKeyDown(KEY_RIGHT))   vehicle.x += 0.2;
        if (IsKeyDown(KEY_LEFT))    vehicle.x -= 0.2;
        if (IsKeyDown(KEY_UP))      vehicle.y -= 0.2;
        if (IsKeyDown(KEY_DOWN))    vehicle.y += 0.2;
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawCircle(vehicle.x, vehicle.y, 20, WHITE);
        for (int i = 0; i < current_waves; i++)
        {
            DrawCircleLines(waves[i].x, waves[i].y, waves[i].r, WHITE);
        }

        EndDrawing();
    }

    return 0;
}