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

private:
    // The cycle duration for the full rainbow.
    static constexpr auto CYCLE_DURATION = 10.;
};

SDL_AppResult ThisApp::iterate(float counter) {
    const auto cycle_position = std::fmod(counter, CYCLE_DURATION);
    const auto t = cycle_position / CYCLE_DURATION;

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
