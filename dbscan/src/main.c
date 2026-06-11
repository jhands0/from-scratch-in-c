#include <raylib.h>
#include <raymath.h>
#include <stddef.h>

#define WIDTH 800
#define HEIGHT 600

#define POINT_RADIUS 10
#define POINT_COLOR RED

#define DBSCAN_RADIUS 100
#define DBSCAN_MINPTS 5

typedef struct
{
    Vector2 position;
    size_t n_neighbors;
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

void get_neighbors(Points points, size_t target, Indices *neighbors)
{
    if (target >= points.count) return;
    for (size_t index = 0; index < points.count; index++)
    {
        if (index == target) continue;
        if (Vector2Distance(points.items[index].position, points.items[target].position) <= DBSCAN_RADIUS)
        {
            if (neighbors->count + 1 < neighbors->capacity)
            {
                neighbors->items[neighbors->count++] = index;
                neighbors->capacity;
            }
        }
    }
}

size_t count_neighbors(Points points, Vector2 centre)
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

    InitWindow(WIDTH, HEIGHT, "DBSCAN");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}