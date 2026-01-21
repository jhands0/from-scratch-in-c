#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600

#define TARGET_FPS 60

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

    float delay_ms = (1.0 / TARGET_FPS) * 1000;
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

        // On every frame ...

        SDL_Delay(delay_ms);
    }

    SDL_DestroyWindow(window);
}
