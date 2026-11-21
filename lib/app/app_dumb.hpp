#pragma once

#include "app_base.hpp"

#include <color.hpp>

#include <SDL3/SDL.h>

#include <array>

class DumbApp : public App {
public:
    /* A dumb "app" that does nothing except show a black screen that can be
     * closed w/ Esc. Also, provides a simple fill() method. */

    DumbApp();

    SDL_AppResult init(int, char**) override;
    SDL_AppResult iterate(float) override;
    SDL_AppResult handle_event(SDL_Event*) override;
    void quit(SDL_AppResult) override;

    void fill(float, float, float) const;
    void fill(const std::array<float, 3>&) const;
    void fill(const RGB&) const;
    void fill(const HSV&) const;

protected:
    static constexpr size_t MIN_WINDOW_SIZE = 10;
    static constexpr size_t MAX_WINDOW_SIZE = 10000;

    size_t window_width = 800;
    size_t window_height = 600;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
