#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdbool.h>

#include "../include/utils.h"

#define WIDTH 800
#define HEIGHT 600

#define POINT_RADIUS 10
#define POINT_COLOUR WHITE

#define DBSCAN_RADIUS 100
#define DBSCAN_MINPTS 5

Color all_colours[] = {
    PINK, YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE, RED, GOLD, LIME, BLUE, VIOLET, BROWN, MAROON, ORANGE, MAGENTA
};
size_t colours_len = sizeof(all_colours) / sizeof(all_colours[0]);

typedef struct
{
    Vector2 position;
    bool visited;
    Color colour;
} Point;

typedef struct
{
    Point *items;
    size_t count;
    size_t capacity;
} Points;

typedef struct
{
    size_t *items;
    size_t count;
    size_t capacity;
} Indices;

void get_neighbours(Points points, size_t target, Indices *neighbours)
{
    if (target >= points.count) return;
    for (size_t index = 0; index < points.count; index++)
    {
        if (index == target) continue;
        if (Vector2Distance(points.items[index].position, points.items[target].position) <= DBSCAN_RADIUS)
        {
            da_append(neighbours, index);
        }
    }
}

size_t count_neighbours(Points points, Vector2 centre)
{
    size_t count = 0;
    for(size_t index = 0; index < points.count; index++)
    {
        if (Vector2Distance(points.items[index].position, centre) <= DBSCAN_RADIUS)
        {
            count += 1;
        }
    }
    return count;
}

int main(void)
{
    Points points = {0};
    Indices neighbours = {0};

    Indices wave = {0};
    Indices next_wave = {0};

    bool show_radius = false;

    InitWindow(WIDTH, HEIGHT, "DBSCAN");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Point point = {
                .position = GetMousePosition(),
                .colour = POINT_COLOUR,
            };
            da_append(&points, point);
        }

        if (IsKeyPressed(KEY_R)) show_radius = !show_radius;

        if (IsKeyPressed(KEY_SPACE))
        {
            for (size_t i = 0; i < points.count; i++)
            {
                points.items[i].visited = false;
            }

            if (points.count > 0)
            {
                size_t points_visited = 0;
                size_t target;

                for (size_t cluster = 0; points_visited < points.count; cluster++)
                {
                    wave.count = 0;
                    Color colour = all_colours[cluster % colours_len];
                    for (target = 0; target < points.count; target++)
                    {
                        if (!points.items[target].visited)
                        {
                            neighbours.count = 0;
                            get_neighbours(points, target, &neighbours);

                            if (neighbours.count == 0)
                            {
                                points.items[target].visited = true;
                                points.items[target].colour = GRAY;
                                points_visited += 1;
                            }
                            else
                            {
                                points.items[target].visited = true;
                                points.items[target].colour = colour;
                                points_visited += 1;
                                da_append(&wave, target);
                            }
                            break;
                        }
                    }

                    while (wave.count > 0)
                    {
                        next_wave.count = 0;
                        for (size_t j = 0; j < wave.count; j++)
                        {
                            neighbours.count = 0;
                            target = wave.items[j];
                            get_neighbours(points, target, &neighbours);
                            for (size_t k = 0; k < neighbours.count; k++)
                            {
                                if (!points.items[neighbours.items[k]].visited)
                                {
                                    da_append(&next_wave, neighbours.items[k]);
                                    points.items[da_last(&next_wave)].visited = true;
                                    points.items[da_last(&next_wave)].colour = colour;
                                    points_visited += 1;
                                }
                            }
                        }
                        swap(Indices, wave, next_wave);
                    }
                }
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (size_t index = 0; index < points.count; index++)
        {
            Point point = points.items[index];
            DrawCircleV(point.position, POINT_RADIUS, point.colour);
            if (show_radius) 
            {
                DrawRing(point.position, DBSCAN_RADIUS, DBSCAN_RADIUS + 2, 0, 360, 70, point.colour);
            }
        }
        EndDrawing();
    }
    CloseWindow();

    da_free(neighbours);
    da_free(wave);
    da_free(next_wave);
    da_free(points);

    return 0;
}