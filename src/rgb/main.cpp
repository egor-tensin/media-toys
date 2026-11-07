// In this example, I want to cycle through RGB values in order; so, red starts
// at 0, incrementally gets to 1, goes back to 0 again; after that, green does
// the same (red & blue staying at 0 meanwhile), and blue after that.

#include <sdl_stub.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <array>
#include <cmath>

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_stub::now() - sdl_stub::app.start;
    // This is the main, ever-increasing counter - the floating-point value of
    // seconds passed since the program started.

    // All colors are 0 for now.
    std::array<float, 3> rgb{};

    // I want for each color to take 1.5 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 1.5;
    // The complete color cycle duration (going up and down).
    static constexpr auto color_duration = phase_duration * 2;
    // The complete cycle duration for all colors.
    static constexpr auto cycle_duration = color_duration * rgb.size();

    // What's the ID of the active color?
    const auto active_color =
        static_cast<size_t>(std::fmod(counter, cycle_duration) / color_duration);

    // The active color's value.
    // I want it to oscilate between 0 to 1 and back to 0 again during each
    // phase. That means that it starts at 0, goes up to 1 during the first
    // phase, then goes back to 0 in the same time.

    // Where are we in the cycle?
    const auto position = std::fmod(counter, color_duration);

    // This "position" value should now be turned into a value between 0 and 1;
    // increasing for the first phase, and decreasing for the second phase. The
    // sine function works great for that, in the range [0, Pi]. So, the first
    // phase is [0, Pi/2] and the second phase is [Pi/2, Pi].

    // I'm old and stupid now, so I'll make this note: to turn position X in
    // [0, A] into a position in [0, B], you divide by A and multiply by B.

    rgb[active_color] = std::sin(position / color_duration * SDL_PI_D);
    // TODO: ^^^ why on earth did I decide to use the sine function?
    // You can easily normalize a value over a range without using any sine
    // function whatsoever: just divide by the range length, no? The sine
    // function was initially picked because it conveniently returns values
    // in [0, 1] in the [0, Pi] range.

    // SDL_Log("rgb: %f %f %f", rgb[0], rgb[1], rgb[2]);

    SDL_SetRenderDrawColorFloat(
        sdl_stub::app.renderer, rgb[0], rgb[1], rgb[2], SDL_ALPHA_OPAQUE_FLOAT
    );

    SDL_RenderClear(sdl_stub::app.renderer);
    SDL_RenderPresent(sdl_stub::app.renderer);

    return SDL_APP_CONTINUE;
}
