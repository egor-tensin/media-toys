#pragma once

#include <SDL3/SDL.h>

namespace sdl_stub {

struct App {
    static constexpr size_t WINDOW_WIDTH = 640;
    static constexpr size_t WINDOW_HEIGHT = 480;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    double start = 0.;
};

extern App app;

inline double now() {
    return static_cast<double>(SDL_GetTicks()) / 1000.;
}

} // namespace sdl_stub

extern "C" {

SDL_AppResult SDL_AppInit(void**, int, char*[]);
SDL_AppResult SDL_AppEvent(void*, SDL_Event*);
void SDL_AppQuit(void*, SDL_AppResult);

}
