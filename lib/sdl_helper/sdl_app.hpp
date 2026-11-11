#pragma once

#include <SDL3/SDL.h>

namespace sdl_helper {

struct App {
    static constexpr size_t WINDOW_WIDTH = 800;
    static constexpr size_t WINDOW_HEIGHT = 600;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    float start = 0.f;
};

extern App app;

inline float now() {
    return static_cast<float>(SDL_GetTicks()) / 1000.;
}

} // namespace sdl_helper
