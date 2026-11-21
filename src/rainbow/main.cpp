// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// As far as I understand, RBG is how displays work, and HSV is a convenient
// way to represent colors as humans expect them to be.

#include <app.hpp>
#include <color.hpp>

#include <cmath>

class ThisApp : public DumbApp {
public:
    ThisApp();

    SDL_AppResult iterate(float) override;

private:
    float cycle_duration = 10.;
};

ThisApp::ThisApp() {
    cmd_parser.add_option("-d,--duration", cycle_duration, "Set cycle duration (seconds)")
        ->check(CLI::PositiveNumber);
}

SDL_AppResult ThisApp::iterate(float counter) {
    const auto cycle_position = std::fmod(counter, cycle_duration);
    const auto t = cycle_position / cycle_duration;

    const HSV color{
        .h = t * 360,
        .s = 1.,
        .v = 1.,
    };

    fill(color);
    return SDL_APP_CONTINUE;
}

App* App::get() {
    static ThisApp instance;
    return &instance;
}
