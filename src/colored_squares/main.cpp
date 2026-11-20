#include <hsv.hpp>
#include <rgb.hpp>
#include <sdl_helper.hpp>

#include <cmath>
#include <limits>

namespace {

RGB random_color() {
    const HSV hsv{
        .h = SDL_randf() * 360.,
        .s = std::sin(SDL_randf() * SDL_PI_F / 2 + SDL_PI_F / 4),
        .v = std::sin(SDL_randf() * SDL_PI_F / 2 + SDL_PI_F / 4),
    };

    return RGB::from_hsv(hsv);
}

}

SDL_AppResult SDL_AppIterate(void*) {
    const auto counter = sdl_helper::app.counter();
    static constexpr auto cycle_duration = .25;
    static size_t cycle_counter = std::numeric_limits<size_t>::max();
    const auto current_cycle = static_cast<size_t>(counter / cycle_duration);

    if (current_cycle == cycle_counter)
        return SDL_APP_CONTINUE;

    cycle_counter = current_cycle;

    static constexpr auto window_height = static_cast<float>(sdl_helper::app.WINDOW_HEIGHT);
    static constexpr auto window_width = static_cast<float>(sdl_helper::app.WINDOW_WIDTH);

    static constexpr size_t grid_height = 25;
    static constexpr size_t grid_width = 25;

    static constexpr auto rect_height = window_height / grid_height;
    static constexpr auto rect_width = window_width / grid_width;

    SDL_RenderClear(sdl_helper::app.renderer);

    for (size_t i = 0; i < grid_width; ++i) {
        for (size_t j = 0; j < grid_height; ++j) {
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

            SDL_SetRenderDrawColorFloat(sdl_helper::app.renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE_FLOAT);
            SDL_RenderFillRect(sdl_helper::app.renderer, &rect);
        }
    }

    SDL_RenderPresent(sdl_helper::app.renderer);
    return SDL_APP_CONTINUE;
}
