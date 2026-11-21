// It's a variation on the "rgb" example, but the sine function is used to
// calculate the color values instead of linear arithmetics; see the "rgb"
// example for more info.

#include <app.hpp>

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

    const auto active_color =
        static_cast<size_t>(std::fmod(counter, cycle_duration) / color_duration);

    const auto t = color_position / color_duration;

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
