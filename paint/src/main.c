#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600

#define TARGET_FPS 60

#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00FF
#define YELLOW  0xFFFF00

#define RADIUS        10
#define ERASER_RADIUS 15

void draw_circle(SDL_Surface *surface, int x, int y, int radius, int color)
{
    SDL_Rect pixel = (SDL_Rect) {0, 0, 1, 1};
    for (int i = x - radius; i <= x + radius; i++)
    {
        for (int j = y - radius; j <= y + radius; j++)
        {
            int distance_from_centre = sqrt(pow(i - x, 2) + pow(j - y, 2));
            if (distance_from_centre < radius)
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
    bool done = false;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Paint",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        0
    );

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    float delay_ms = (1.0 / TARGET_FPS) * 1000;
    int colors[7] = {WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW};
    int color_i;
    while (!done)
    {
        // On every frame ...

        bool draw;
        bool eraser;
        SDL_Event event;
        int color;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    draw = true;

                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            eraser = false;
                            color = colors[color_i];
                            break;

                        case SDL_BUTTON_RIGHT:
                            eraser = true;
                            color = BLACK;
                            break;
                    }

                    break;

                case SDL_MOUSEBUTTONUP:
                    draw = false;
                    break;

                case SDL_MOUSEMOTION:
                    color_i = 0;

                    if (draw)
                    {
                        int current_radius = eraser ? ERASER_RADIUS : RADIUS;
                        draw_circle(surface, event.motion.x, event.motion.y, current_radius, color);
                    }
                    break;

                case SDL_MOUSEWHEEL_NORMAL:
                    color_i = (color_i + 1) % 7;
                    break;

                case SDL_MOUSEWHEEL_FLIPPED:
                    color_i = (color_i - 1) % 7;
                    break;
            }
        }

        SDL_UpdateWindowSurface(window);

        SDL_Delay(delay_ms);
    }

    SDL_DestroyWindow(window);
}
