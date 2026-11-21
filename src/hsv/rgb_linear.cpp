// I don't understand the HSV color model, and I'm trying to.
//
// For more details about HSV, you can hopefully see the "rainbow" example.
//
// This is analagous to the "rgb/linear" example, but in the HSV color model.

#include <app.hpp>
#include <color.hpp>

#include <array>
#include <cmath>

class ThisApp : public DumbApp {
public:
    ThisApp();

    SDL_AppResult iterate(float) override;

private:
    float cycle_duration = 6.;
};

ThisApp::ThisApp() {
    cmd_parser.add_option("-d,--duration", cycle_duration, "Set cycle duration (seconds)")
        ->check(CLI::PositiveNumber);
}

SDL_AppResult ThisApp::iterate(float counter) {
    const auto color_duration = cycle_duration / 3;
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
