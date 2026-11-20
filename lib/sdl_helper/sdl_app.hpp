#pragma once

#include <SDL3/SDL.h>

namespace sdl_helper {

struct App {
    float start = 0.;

    static float now() {
        return static_cast<float>(SDL_GetTicks()) / 1000.;
    }

    float counter() const {
        return now() - start;
    }

    static constexpr size_t WINDOW_WIDTH = 800;
    static constexpr size_t WINDOW_HEIGHT = 600;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

extern App app;

} // namespace sdl_helper
