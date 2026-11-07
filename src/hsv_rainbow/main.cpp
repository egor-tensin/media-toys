// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// As far as I understand, RBG is how displays work, and HSV is a convenient
// way to represent colors as humans expect them to be.
//
// I'm going to describe HSV at my best, but this is obviously not saying much.
//
// H - Hue
// S - Saturation
// V - Value

#include <sdl_stub.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <cmath>

namespace {

struct HSV {
    float h; // [0, 360]
    float s; // [0, 1]
    float v; // [0, 1]
};

struct RGB {
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;

    static constexpr RGB from_hsv(const HSV& hsv) {
        const float c = hsv.v * hsv.s;
        const float x = c * (1.f - std::abs(std::fmod(hsv.h / 60.f, 2.f) - 1.f));
        const float m = hsv.v - c;

        RGB result{};

        // The HSV color wheel is divided into 6 sectors:
        // < 60 - red to yellow,
        // < 120 - yellow to green,
        // < 180 - green to cyan,
        // < 240 - cyan to blue,
        // < 300 - blue to magenta
        // < 360 - magenta back to red again.
        if (hsv.h < 60.f)
            result = {c, x, 0.f};
        else if (hsv.h < 120.f)
            result = {x, c, 0.f};
        else if (hsv.h < 180.f)
            result = {0.f, c, x};
        else if (hsv.h < 240.f)
            result = {0.f, x, c};
        else if (hsv.h < 300.f)
            result = {x, 0.f, c};
        else
            result = {c, 0.f, x};

        return {result.r + m, result.g + m, result.b + m};
    }
};

} // namespace

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_stub::now() - sdl_stub::app.start;
    // This is the main, ever-increasing counter - the floating-point value of
    // seconds passed since the program started.

    // The cycle duration for the rainbow.
    static constexpr auto cycle_duration = 10.;

    const float hue =
        static_cast<float>(std::fmod(counter, cycle_duration) / cycle_duration * 360.0);

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
