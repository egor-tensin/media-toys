#include <app.hpp>
#include <color.hpp>

#include <cmath>
#include <limits>

class ThisApp : public DumbApp {
public:
    SDL_AppResult iterate(float) override;

private:
    // Randomize everything every .25 seconds!
    static constexpr auto CYCLE_DURATION = .25;

    // Number of squares in each dimension:
    static constexpr size_t GRID_HEIGHT = 25;
    static constexpr size_t GRID_WIDTH = 25;

    static RGB random_color();

    size_t cycle_counter = std::numeric_limits<size_t>::max();
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
    if (current_cycle == cycle_counter)
        return SDL_APP_CONTINUE;
    cycle_counter = current_cycle;

    SDL_RenderClear(renderer);

    static constexpr auto rect_height = static_cast<float>(WINDOW_HEIGHT) / GRID_HEIGHT;
    static constexpr auto rect_width = static_cast<float>(WINDOW_WIDTH) / GRID_WIDTH;

    for (size_t i = 0; i < GRID_WIDTH; ++i) {
        for (size_t j = 0; j < GRID_HEIGHT; ++j) {
            const auto x1 = i * rect_width;
            const auto x2 = (i + 1) * rect_width;

            const auto y1 = j * rect_height;
            const auto y2 = (j + 1) * rect_height;

            SDL_FRect rect{
                .x = x1,
                .y = y1,
                .w = (x2 - x1),
                .h = (y2 - y1),
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
