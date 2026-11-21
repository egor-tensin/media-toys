#include <app.hpp>
#include <color.hpp>

#include <cmath>
#include <limits>
#include <optional>

class ThisApp : public DumbApp {
public:
    ThisApp();

    SDL_AppResult iterate(float) override;

private:
    static RGB random_color();

    float cycle_duration = 1.;
    std::optional<size_t> cycle_counter;

    size_t grid_height = 10;
    size_t grid_width = 10;

    float rect_height;
    float rect_width;

    float margin = 0.;
};

ThisApp::ThisApp() {
    cmd_parser.add_option("-d,--duration", cycle_duration, "Set cycle duration (seconds)")
        ->check(CLI::PositiveNumber);
    cmd_parser.add_option("-g,--grid-width", grid_width, "Set grid width")
        ->check(CLI::PositiveNumber);
    cmd_parser.add_option("-G,--grid-height", grid_height, "Set grid height")
        ->check(CLI::PositiveNumber);
    cmd_parser.add_option("-m,--margin", margin, "Set margin for squares (px)")
        ->check(CLI::NonNegativeNumber);
}

RGB ThisApp::random_color() {
    const HSV hsv{
        .h = SDL_randf() * 360.,
        .s = std::sin(SDL_randf() * SDL_PI_F / 2 + SDL_PI_F / 4),
        .v = std::sin(SDL_randf() * SDL_PI_F / 2 + SDL_PI_F / 4),
    };
    return RGB::from_hsv(hsv);
}

SDL_AppResult ThisApp::iterate(float counter) {
    const auto current_cycle = static_cast<size_t>(counter / cycle_duration);
    if (cycle_counter && current_cycle == cycle_counter)
        return SDL_APP_CONTINUE;
    cycle_counter = current_cycle;

    const auto rect_height = (static_cast<float>(window_height) - margin) / grid_height;
    const auto rect_width = (static_cast<float>(window_width) - margin) / grid_width;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < grid_height; ++i) {
        for (size_t j = 0; j < grid_width; ++j) {
            const auto x1 = j * rect_width;
            const auto x2 = (j + 1) * rect_width;

            const auto y1 = i * rect_height;
            const auto y2 = (i + 1) * rect_height;

            SDL_FRect rect{
                .x = x1 + margin,
                .y = y1 + margin,
                .w = x2 - x1 - margin,
                .h = y2 - y1 - margin,
            };

            const auto rgb = random_color();

            SDL_SetRenderDrawColorFloat(renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE_FLOAT);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

App* App::get() {
    static ThisApp instance;
    return &instance;
}
