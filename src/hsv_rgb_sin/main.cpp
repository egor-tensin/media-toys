// Analogous to the "rgb_sin" example, but in the HSV color model.

#include <hsv.hpp>
#include <rgb.hpp>
#include <sdl_helper.hpp>

#include <array>
#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_helper::now() - sdl_helper::app.start;

    static constexpr std::array<float, 3> rgb{};

    // I want for each color to take 2 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 2.f;
    static constexpr auto color_duration = phase_duration * 2;
    static constexpr auto cycle_duration = color_duration * rgb.size();

    const auto color_position = std::fmod(counter, color_duration);
    const auto cycle_position = std::fmod(counter, cycle_duration);

    const auto active_color = static_cast<size_t>(cycle_position / color_duration);

    const auto t = color_position / color_duration;

    const HSV color{
        .h = active_color * 120.f,
        .s = 1.f,
        .v = std::sin(t * SDL_PI_F),
    };

    sdl_helper::fill(color);
    return SDL_APP_CONTINUE;
}
