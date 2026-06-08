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

size_t count_neighbors(Points points, Vector2 center)
{
    size_t count = 0;
    for(int i = 0; i < points.count; i++)
    {
        if (Vector2Distance(points.items[i].position, center) <= DBSCAN_RADIUS)
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