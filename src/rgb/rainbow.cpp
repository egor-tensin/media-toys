// In this example, I want to cycle through all the rainbow colors in order;
// so, start with red, continue with orange, etc. This is a very dumb
// implementation, obviously.
//
// The value of this particular implementation is to demonstrate how cycling
// through RGB colors with linear interpolation can look bad.

#include <app.hpp>
#include <color.hpp>

#include <array>
#include <cmath>

class ThisApp : public DumbApp {
public:
    ThisApp();

    SDL_AppResult iterate(float) override;

private:
    static constexpr std::array COLORS{
        // These particular values were picked from somewhere on the web.
        RGB::from_hex(0xFF'00'00), // red
        RGB::from_hex(0xFF'7F'00), // orange
        RGB::from_hex(0xFF'FF'00), // yellow
        RGB::from_hex(0x00'FF'00), // green
        RGB::from_hex(0x00'00'FF), // blue
        RGB::from_hex(0x4B'00'82), // indigo
        RGB::from_hex(0x8F'00'FF), // violet
    };

    float cycle_duration = 10.;
};

ThisApp::ThisApp() {
    cmd_parser.add_option("-d,--duration", cycle_duration, "Set cycle duration (seconds)")
        ->check(CLI::PositiveNumber);
}

SDL_AppResult ThisApp::iterate(float counter) {
    const auto color_duration = cycle_duration / COLORS.size();
    const auto cycle_position = std::fmod(counter, cycle_duration);
    const auto color_position = std::fmod(cycle_position, color_duration);

    const auto this_color_idx = static_cast<size_t>(cycle_position / color_duration);
    const auto next_color_idx = (this_color_idx + 1) % COLORS.size();

    const auto& this_color = COLORS[this_color_idx];
    const auto& next_color = COLORS[next_color_idx];

    const auto t = color_position / color_duration;

    // This is basically a + t(b - a) for every color component.
    // So, new_color = this_color + color_position / color_duration * (next_color - this_color).
    const auto new_color = this_color.lerp(next_color, t);

    fill(new_color);
    return SDL_APP_CONTINUE;
};

App* App::get() {
    static ThisApp instance;
    return &instance;
}
