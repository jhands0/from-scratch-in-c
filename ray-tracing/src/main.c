#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define WIDTH 900
#define HEIGHT 600

#define TARGET_FPS 60

#define BLACK 0x000000
#define GRAY  0x4B4C4C
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


    double radius = 50.0;
    struct Circle circle = {0.0, 0.0, radius};

    float delay_ms = (1.0 / TARGET_FPS) * 1000;
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    circle.x = (double) event.motion.x;
                    circle.y = (double) event.motion.y;

                    //Create a light source when left mouse button is pressed
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        draw_circle(surface, circle, WHITE);
                    }

                    //Create a solid object when right mouse button is pressed
                    if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        draw_circle(surface, circle, GRAY);
                    }
                    break;

                case SDL_MOUSEWHEEL_NORMAL:
                    // Fix later
                    radius = (double) abs((int) radius + 10);
                    break;

                case SDL_MOUSEWHEEL_FLIPPED:
                    radius = (double) abs((int) radius - 10);
                    break;
            }
        }

        SDL_UpdateWindowSurface(window);

        SDL_Delay(delay_ms);
    }

    SDL_DestroyWindow(window);
}
