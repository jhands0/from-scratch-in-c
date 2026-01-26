#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

#include <math.h>
#include <stdio.h>
#include <stdbool.h>


#define WIDTH 900
#define HEIGHT 600

#define TARGET_FPS 60

#define WHITE 0xFFFFFF

struct Circle
{
    double x;
    double y;
    double radius;
};

void draw_circle(SDL_Surface *surface, struct Circle circle, int color)
{
    SDL_Rect pixel = (SDL_Rect) {0, 0, 1, 1};
    for (double i = circle.x - circle.radius; i <= circle.x + circle.radius; i++)
    {
        for (double j = circle.y - circle.radius; j <= circle.y + circle.radius; j++)
        {
            double distance_from_centre = sqrt(pow(i - circle.x, 2) + pow(j - circle.y, 2));
            if (distance_from_centre < circle.radius)
            {
                pixel.x = i;
                pixel.y = j;
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    struct Circle source = {200.0, 200.0, 50.0};
    draw_circle(surface, source, WHITE);

    float delay_ms = (1.0 / TARGET_FPS) * 1000;
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
        }

        SDL_UpdateWindowSurface(window);

        SDL_Delay(delay_ms);
    }

    SDL_DestroyWindow(window);
}
