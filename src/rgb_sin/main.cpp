// It's a variation on the "rgb" example, but the sine function is used to
// calculate the color values instead of linear arithmetics; see the "rgb"
// example for more info.

#include <sdl_helper.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <array>
#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_helper::now() - sdl_helper::app.start;

    std::array<float, 3> rgb{};

    // I want for each color to take 2 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 2.f;
    static constexpr auto color_duration = phase_duration * 2;
    static constexpr auto cycle_duration = color_duration * rgb.size();

    const auto color_position = std::fmod(counter, color_duration);

    const auto active_color =
        static_cast<size_t>(std::fmod(counter, cycle_duration) / color_duration);

    const auto t = color_position / color_duration;

    rgb[active_color] = std::sin(t * SDL_PI_F);
    // The sine function is used here because it conveniently produces values
    // in the range of [0, 1] for [0, Pi] in a smooth curve.

    // SDL_Log("rgb: %f %f %f", rgb[0], rgb[1], rgb[2]);

    sdl_helper::fill(rgb);
    return SDL_APP_CONTINUE;
}
