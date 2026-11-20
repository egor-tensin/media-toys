// It's a variation on the "rgb" example, but the sine function is used to
// calculate the color values instead of linear arithmetics; see the "rgb"
// example for more info.

#include <sdl_dumb_app.hpp>

#include <array>
#include <cmath>

class ThisApp : public DumbApp {
public:
    SDL_AppResult iterate(float) override;
};

SDL_AppResult ThisApp::iterate(float counter) {
    std::array<float, 3> rgb{};

    // I want for each color to take 2 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 2.;
    static constexpr auto color_duration = phase_duration * 2;
    static constexpr auto cycle_duration = color_duration * rgb.size();

    const auto color_position = std::fmod(counter, color_duration);

    const auto active_color =
        static_cast<size_t>(std::fmod(counter, cycle_duration) / color_duration);

    const auto t = color_position / color_duration;

    rgb[active_color] = std::sin(t * SDL_PI_F);
    // The sine function is used here because it conveniently produces values
    // in the range of [0, 1] for [0, Pi] in a smooth curve.

    fill(rgb);
    return SDL_APP_CONTINUE;
}

App* App::get() {
    static ThisApp instance;
    return &instance;
}
