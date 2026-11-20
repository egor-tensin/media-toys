#pragma once

#include "sdl_app.hpp"

#include <hsv.hpp>
#include <rgb.hpp>

#include <SDL3/SDL.h>

#include <array>

class DumbApp : public App {
public:
    /* A dumb "app" that does nothing except show a black screen that can be
     * closed w/ Esc. Also, provides a simple fill() method. */

    SDL_AppResult init(int, char**) override;
    SDL_AppResult iterate(float) override;
    SDL_AppResult handle_event(SDL_Event*) override;
    void quit(SDL_AppResult) override;

    void fill(float, float, float) const;
    void fill(const std::array<float, 3>&) const;
    void fill(const RGB&) const;
    void fill(const HSV&) const;

protected:
    static constexpr size_t WINDOW_WIDTH = 800;
    static constexpr size_t WINDOW_HEIGHT = 600;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
