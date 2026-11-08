// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// For more details about HSV, you can hopefully see the hsv_rainbow example.

#include <hsv.hpp>
#include <rgb.hpp>
#include <sdl_stub.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <array>
#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_stub::now() - sdl_stub::app.start;
    // This is the main, ever-increasing counter - the floating-point value of
    // seconds passed since the program started.

    std::array<float, 3> rgb{};

    // I want for each color to take 1.5 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 1.5f;
    // The complete color cycle duration (going up and down).
    static constexpr auto color_duration = phase_duration * 2;
    // The complete cycle duration for all colors.
    static constexpr auto cycle_duration = color_duration * rgb.size();

    const auto color_position = std::fmod(counter, color_duration);

    const auto cycle_position = std::fmod(counter, cycle_duration);
    const auto active_color = static_cast<size_t>(cycle_position / color_duration);

    const RGB color = RGB::from_hsv({
        .h = active_color * 120.f,
        .s = 1.f,
        .v = std::sin(color_position / color_duration * SDL_PI_F),
    });

    SDL_SetRenderDrawColorFloat(
        sdl_stub::app.renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE_FLOAT
    );

    SDL_RenderClear(sdl_stub::app.renderer);
    SDL_RenderPresent(sdl_stub::app.renderer);

    return SDL_APP_CONTINUE;
}
