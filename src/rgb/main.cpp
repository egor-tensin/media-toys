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

    // I want for each color to take 2 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 2.f;
    // The complete color cycle duration (going up and down).
    static constexpr auto color_duration = phase_duration * 2;
    // The complete cycle duration for all colors.
    static constexpr auto cycle_duration = color_duration * rgb.size();

    // What's the ID of the active color?
    const auto active_color =
        static_cast<size_t>(std::fmod(counter, cycle_duration) / color_duration);

    // The active color's value.
    // I want it to oscillate between 0 to 1 and back to 0 again during each
    // phase. That means that it starts at 0, goes up to 1 during the first
    // phase, then goes back to 0 in the same time.

    // Where are we in the cycle?
    const auto color_position = std::fmod(counter, color_duration);

    // This "color_position" value should now be turned into a value between 0
    // and 1; increasing for the first phase, and decreasing for the second
    // phase. One way to do that is using a linear function; see the "rgb_sin"
    // example for the sine function usage.
    //
    // Here I want for the value to rise linearly for the first phase, and
    // decrease linearly for the second phase. The school way to do that is to
    // use the absolute value function, I guess?
    //
    // So, y = |x|, which looks like \/, except it should be normalized for the
    // color_duration range (so y(color_duration) = 0), shifted along the X
    // axis to the right by one (by subtracting 1), _and_ we want it to be
    // flipped (by negating the value), _and_ we want it to be narrower (for
    // the both phases) by multiplying by 2. Raise the flipped /\ up by one,
    // and we're done.
    //
    // So, the final color value is y = 1 - |2t - 1|, where t is the relative
    // position in the complete up-and-down cycle.

    // I'm old and stupid now, so I'll make this note: to turn position X in
    // [0, A] into a position in [0, B], you divide by A and multiply by B.
    const auto t = color_position / color_duration;

    rgb[active_color] = 1.f - std::abs(2.f * t - 1.f);

    // SDL_Log("rgb: %f %f %f", rgb[0], rgb[1], rgb[2]);

    sdl_stub::fill(rgb);
    return SDL_APP_CONTINUE;
}
