#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <wchar.h>

#define WIDTH 900
#define HEIGHT 600

#define TARGET_FPS 60

#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00FF
#define YELLOW  0xFFFF00

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
    int color_i = 0;
    while (!done)
    {
        // On every frame ...

        bool draw;
        SDL_Rect rect;
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
                    break;

                case SDL_MOUSEBUTTONUP:
                    draw = false;
                    break;

                case SDL_MOUSEMOTION:
                    if (color == NULL)
                    {
                        color = colors[color_i];
                    }

                    if (draw)
                    {
                        rect = (SDL_Rect) {event.motion.x, event.motion.y, 10, 10};
                        SDL_FillRect(surface, &rect, color);
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
