#include <app.hpp>
#include <color.hpp>

#include <cmath>
#include <limits>
#include <optional>

class ThisApp : public DumbApp {
public:
    SDL_AppResult iterate(float) override;

private:
    // Margin around the squares (in pixels):
    static constexpr auto MARGIN = 1.;

    // Randomize everything every .25 seconds!
    static constexpr auto CYCLE_DURATION = .25;

    // Number of squares in each dimension:
    static constexpr size_t GRID_HEIGHT = 25;
    static constexpr size_t GRID_WIDTH = 25;

    static RGB random_color();

    std::optional<size_t> cycle_counter;
};

RGB ThisApp::random_color() {
    const HSV hsv{
        .h = SDL_randf() * 360.,
        .s = std::sin(SDL_randf() * SDL_PI_F / 2 + SDL_PI_F / 4),
        .v = std::sin(SDL_randf() * SDL_PI_F / 2 + SDL_PI_F / 4),
    };
    return RGB::from_hsv(hsv);
}

SDL_AppResult ThisApp::iterate(float counter) {
    const auto current_cycle = static_cast<size_t>(counter / CYCLE_DURATION);
    if (cycle_counter && current_cycle == cycle_counter)
        return SDL_APP_CONTINUE;
    cycle_counter = current_cycle;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    static constexpr auto rect_height = (static_cast<float>(WINDOW_HEIGHT) - MARGIN) / GRID_HEIGHT;
    static constexpr auto rect_width = (static_cast<float>(WINDOW_WIDTH) - MARGIN) / GRID_WIDTH;

    for (size_t i = 0; i < GRID_HEIGHT; ++i) {
        for (size_t j = 0; j < GRID_WIDTH; ++j) {
            const auto x1 = j * rect_width + MARGIN;
            const auto x2 = (j + 1) * rect_width + MARGIN;

            const auto y1 = i * rect_height + MARGIN;
            const auto y2 = (i + 1) * rect_height + MARGIN;

            SDL_FRect rect{
                .x = x1,
                .y = y1,
                .w = x2 - x1 - MARGIN,
                .h = y2 - y1 - MARGIN,
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
