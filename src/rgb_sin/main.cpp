// It's a variation on the "rgb" example, but the sine function is used to
// calculate the color values instead of linear arithmetics; see the "rgb"
// example for more info.

#include <app.hpp>

#include <array>
#include <cmath>

class ThisApp : public DumbApp {
public:
    SDL_AppResult iterate(float) override;

private:
    // I want for each color to take 2 seconds to go from 0 to 1.
    static constexpr auto PHASE_DURATION = 2.;
    // Colors fade in and fade out:
    static constexpr auto COLOR_DURATION = PHASE_DURATION * 2;
    // Three colors in RGB:
    static constexpr auto CYCLE_DURATION = COLOR_DURATION * 3;
};

SDL_AppResult ThisApp::iterate(float counter) {
    const auto color_position = std::fmod(counter, COLOR_DURATION);

    const auto active_color =
        static_cast<size_t>(std::fmod(counter, CYCLE_DURATION) / COLOR_DURATION);

    const auto t = color_position / COLOR_DURATION;

    std::array<float, 3> rgb{};
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
