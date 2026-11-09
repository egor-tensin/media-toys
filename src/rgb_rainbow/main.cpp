// In this example, I want to cycle through all the rainbow colors in order;
// so, start with red, continue with orange, etc. This is a very dumb
// implementation, obviously.

#include <rgb.hpp>
#include <sdl_helper.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <array>
#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_helper::now() - sdl_helper::app.start;

    static constexpr std::array COLORS{
        // These particular values were picked from somewhere on the web.
        RGB::from_hex(0xFF'00'00),
        RGB::from_hex(0xFF'7F'00),
        RGB::from_hex(0xFF'FF'00),
        RGB::from_hex(0x00'FF'00),
        RGB::from_hex(0x00'00'FF),
        RGB::from_hex(0x4B'00'82),
        RGB::from_hex(0x8F'00'FF),

        // Black-to-white:
        // RGB::from_hex(0x00'00'00),
        // RGB::from_hex(0xFF'FF'FF),
    };

    // The cycle duration for the full rainbow.
    static constexpr auto cycle_duration = 10.f;
    static constexpr auto color_duration = cycle_duration / COLORS.size();

    const auto cycle_position = std::fmod(counter, cycle_duration);
    const auto color_position = std::fmod(cycle_position, color_duration);

    const auto this_color_idx = static_cast<size_t>(cycle_position / color_duration);
    const auto next_color_idx = (this_color_idx + 1) % COLORS.size();

    const auto& this_color = COLORS[this_color_idx];
    const auto& next_color = COLORS[next_color_idx];

    const auto t = color_position / color_duration;

    // This is basically a + t(b - a) for every color component.
    // So, new_color = this_color + color_position / color_duration * (next_color - this_color).
    const auto new_color = this_color.lerp(next_color, t);

    sdl_helper::fill(new_color);
    return SDL_APP_CONTINUE;
}
