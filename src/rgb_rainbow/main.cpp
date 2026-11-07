// In this example, I want to cycle through all the rainbow colors in order;
// so, start with red, continue with orange, etc. This is a very dumb
// implementation, obviously.

#include <sdl_stub.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <array>
#include <cmath>

namespace {

struct RGB {
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;

    static constexpr RGB decode(uint32_t hex_color) {
        return {
            static_cast<float>((hex_color >> 16) & 0xFF) / 255.f,
            static_cast<float>((hex_color >> 8) & 0xFF) / 255.f,
            static_cast<float>(hex_color & 0xFF) / 255.f,
        };
    }

    constexpr RGB lerp(const RGB& other, float t) const {
        // std::lerp on basic numbers is just a + t(b - a).
        // This is called linear interpolation, and I really do wish I was
        // smarter than I am.
        return {
            std::lerp(r, other.r, t),
            std::lerp(g, other.g, t),
            std::lerp(b, other.b, t),
        };
    }
};

} // namespace

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_stub::now() - sdl_stub::app.start;
    // This is the main, ever-increasing counter - the floating-point value of
    // seconds passed since the program started.

    static constexpr std::array COLORS{
        // These particular values were picked from somewhere on the web.
        RGB::decode(0xFF'00'00),
        RGB::decode(0xFF'7F'00),
        RGB::decode(0xFF'FF'00),
        RGB::decode(0x00'FF'00),
        RGB::decode(0x00'00'FF),
        RGB::decode(0x4B'00'82),
        RGB::decode(0x8F'00'FF),

        // Black-to-white:
        // RGB::decode(0x00'00'00),
        // RGB::decode(0xFF'FF'FF),
    };

    // The cycle duration for the rainbow.
    static constexpr auto cycle_duration = 10.;
    const auto cycle_position = std::fmod(counter, cycle_duration);

    static constexpr auto color_duration = cycle_duration / COLORS.size();
    const auto color_position = std::fmod(cycle_position, color_duration);

    const auto this_color_idx = static_cast<size_t>(cycle_position / color_duration);
    const auto next_color_idx = (this_color_idx + 1) % COLORS.size();

    const auto& this_color = COLORS[this_color_idx];
    const auto& next_color = COLORS[next_color_idx];

    const RGB new_color = this_color.lerp(next_color, color_position / color_duration);

    SDL_SetRenderDrawColorFloat(
        sdl_stub::app.renderer, new_color.r, new_color.g, new_color.b, SDL_ALPHA_OPAQUE_FLOAT
    );

    SDL_RenderClear(sdl_stub::app.renderer);
    SDL_RenderPresent(sdl_stub::app.renderer);

    return SDL_APP_CONTINUE;
}
