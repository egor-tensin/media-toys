// Analogous to the "rgb_sin" example, but in the HSV color model.

#include <app.hpp>
#include <color.hpp>

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
    const auto cycle_position = std::fmod(counter, CYCLE_DURATION);

    const auto active_color = static_cast<size_t>(cycle_position / COLOR_DURATION);

    const auto t = color_position / COLOR_DURATION;

    const HSV color{
        .h = active_color * 120.,
        .s = 1.,
        .v = std::sin(t * SDL_PI_F),
    };

    fill(color);
    return SDL_APP_CONTINUE;
}

App* App::get() {
    static ThisApp instance;
    return &instance;
}
