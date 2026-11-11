// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// As far as I understand, RBG is how displays work, and HSV is a convenient
// way to represent colors as humans expect them to be.

#include <hsv.hpp>
#include <rgb.hpp>
#include <sdl_helper.hpp>

#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_helper::now() - sdl_helper::app.start;

    // The cycle duration for the full rainbow.
    static constexpr auto cycle_duration = 10.f;
    const auto cycle_position = std::fmod(counter, cycle_duration);

    const auto t = cycle_position / cycle_duration;

    const auto hue = t * 360.f;

    const HSV color{
        .h = hue,
        .s = 1.f,
        .v = 1.f,
    };

    sdl_helper::fill(color);
    return SDL_APP_CONTINUE;
}
