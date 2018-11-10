#include <stdafx.h>

//#undef main
//
//#include <iostream>


int main(int argc, char *argv[])
{
    /*
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
    }
    SDL_Window *win = SDL_CreateWindow("Hello", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow() Error: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 333;
    rect.h = 227;

    SDL_RenderClear(ren);

    SDL_Event event;

    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            SDL_PumpEvents();
            if (event.type == SDL_QUIT)
            {
                return 0;
            }
            SDL_Surface *surface = SDL_GetWindowSurface(win);
            SDL_FillRect(surface, &rect, 0xffff0000);
            SDL_UpdateWindowSurface(win);
        }
    }

    */

    return 0;
}
