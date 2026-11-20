// I don't understand the HSV color model, and I'm trying to, as best as I can.
//
// As far as I understand, RBG is how displays work, and HSV is a convenient
// way to represent colors as humans expect them to be.

#include <app.hpp>
#include <color.hpp>

#include <cmath>

class ThisApp : public DumbApp {
public:
    SDL_AppResult iterate(float) override;
};

SDL_AppResult ThisApp::iterate(float counter) {
    // The cycle duration for the full rainbow.
    static constexpr auto cycle_duration = 10.;
    const auto cycle_position = std::fmod(counter, cycle_duration);

    const auto t = cycle_position / cycle_duration;

    const auto hue = t * 360.;

    const HSV color{
        .h = hue,
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
