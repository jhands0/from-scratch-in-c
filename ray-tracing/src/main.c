#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
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

#define NUM_RAYS 100
#define RAY_LENGTH 200.0

#define BLACK 0x000000
#define GRAY  0x4B4C4C
#define WHITE 0xFFFFFF

struct Circle
{
    double x;
    double y;
    double radius;
};

struct Ray
{
    double x_1, y_1;
    double length;
    double x_2, y_2;
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

void generate_rays(struct Circle source, struct Ray rays[NUM_RAYS])
{
    double x_1 = source.x;
    double y_1 = source.y;

    double angle_step = 360.0 / NUM_RAYS;
    struct Ray ray = {x_1, y_1, RAY_LENGTH, 0, 0};
    int count = 0;
    for (double angle = 0.0; angle < 360.0; angle += angle_step)
    {
        ray.x_2 = x_1 + (RAY_LENGTH * cos(angle));
        ray.y_2 = y_1 + (RAY_LENGTH * sin(angle));

        rays[count] = ray;
        count += 1;
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);


    double radius = 50.0;
    struct Circle circle = {0.0, 0.0, radius};
    struct Ray rays[NUM_RAYS];

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
                        generate_rays(circle, rays);
                        //draw_rays(surface, rays);
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
