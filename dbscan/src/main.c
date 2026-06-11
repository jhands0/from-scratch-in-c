#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

#define POINT_RADIUS 10
#define POINT_COLOUR RED

#define DBSCAN_RADIUS 100
#define DBSCAN_MINPTS 5

#define POINTS_CAP 100
#define NEIGHBOURS_CAP 500

#define FONT_SIZE 40
#define FONT_COLOUR WHITE

typedef struct
{
    Vector2 position;
    size_t n_neighbours;
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
            if (neighbours->count + 1 < neighbours->capacity)
            {
                neighbours->items[neighbours->count] = index;
                neighbours->count++;
            }
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
    Points points = {
        .items = (Point*) malloc(POINTS_CAP * sizeof(Point)),
        .count = 0,
        .capacity = POINTS_CAP,
    };

    Indices neighbours = {
        .items = (size_t*) malloc(NEIGHBOURS_CAP * sizeof(size_t)),
        .count = 0,
        .capacity = NEIGHBOURS_CAP,
    };

    InitWindow(WIDTH, HEIGHT, "DBSCAN");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Point point = {
                .position = GetMousePosition(),
            };
            if (points.count + 1 < points.capacity)
            {
                points.items[points.count] = point;
                points.count++;
            }
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            for (size_t target = 0; target < points.count; target++)
            {
                neighbours.count = 0;
                get_neighbours(points, target, &neighbours);
                points.items[target].n_neighbours = neighbours.count;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (size_t index = 0; index < points.count; index++)
        {
            Point point = points.items[index];
            DrawCircleV(point.position, POINT_RADIUS, POINT_COLOUR);
            if (point.n_neighbours > 0)
            {
                DrawText(TextFormat("%zu", point.n_neighbours), point.position.x, point.position.y, FONT_SIZE, FONT_COLOUR);
            }
            DrawRing(point.position, DBSCAN_RADIUS, DBSCAN_RADIUS + 2, 0, 360, 70, POINT_COLOUR);
        }
        EndDrawing();
    }
    CloseWindow();

    free(neighbours.items);
    free(points.items);

    return 0;
}