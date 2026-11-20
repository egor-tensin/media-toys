// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// For more details about HSV, you can hopefully see the "hsv_rainbow" example.
//
// This is analagous to the "rgb" example, but in the HSV color model.

#include <app.hpp>
#include <color.hpp>

#include <array>
#include <cmath>

class ThisApp : public DumbApp {
public:
    SDL_AppResult iterate(float) override;
};

SDL_AppResult ThisApp::iterate(float counter) {
    static constexpr std::array<float, 3> rgb{};

    // I want for each color to take 2 seconds to go from 0 to 1.
    static constexpr auto phase_duration = 2.;
    static constexpr auto color_duration = phase_duration * 2;
    static constexpr auto cycle_duration = color_duration * rgb.size();

    const auto color_position = std::fmod(counter, color_duration);
    const auto cycle_position = std::fmod(counter, cycle_duration);

    const auto active_color = static_cast<size_t>(cycle_position / color_duration);

    const auto t = color_position / color_duration;

    const HSV color{
        .h = active_color * 120.,
        .s = 1.,
        .v = 1. - std::abs(2. * t - 1),
    };

    fill(color);
    return SDL_APP_CONTINUE;
}

App* App::get() {
    static ThisApp instance;
    return &instance;
}
