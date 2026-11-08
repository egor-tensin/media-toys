// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// As far as I understand, RBG is how displays work, and HSV is a convenient
// way to represent colors as humans expect them to be.

#include <hsv.hpp>
#include <rgb.hpp>
#include <sdl_stub.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_stub::now() - sdl_stub::app.start;

    // The cycle duration for the full rainbow.
    static constexpr auto cycle_duration = 10.f;

    const auto hue = std::fmod(counter, cycle_duration) / cycle_duration * 360.f;

    const RGB color = RGB::from_hsv({
        .h = hue,
        .s = 1.f,
        .v = 1.f,
    });

    SDL_SetRenderDrawColorFloat(
        sdl_stub::app.renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE_FLOAT
    );

    SDL_RenderClear(sdl_stub::app.renderer);
    SDL_RenderPresent(sdl_stub::app.renderer);

    return SDL_APP_CONTINUE;
}
