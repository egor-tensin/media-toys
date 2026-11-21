#include "app_dumb.hpp"

#include <color.hpp>

#include <SDL3/SDL.h>

#include <array>

DumbApp::DumbApp() {
    cmd_parser.add_option("-W,--width", window_width, "Set window width (px)")
        ->check(CLI::Range(MIN_WINDOW_SIZE, MAX_WINDOW_SIZE));
    cmd_parser.add_option("-H,--height", window_height, "Set window height (px)")
        ->check(CLI::Range(MIN_WINDOW_SIZE, MAX_WINDOW_SIZE));
}

SDL_AppResult DumbApp::init(int argc, char** argv) {
    const auto base_result = App::init(argc, argv);
    if (base_result != SDL_APP_CONTINUE)
        return base_result;

    SDL_Log("Available renderer drivers:");
    for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i) {
        SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
    }

    if (!SDL_CreateWindowAndRenderer(
            "dumb_app", window_width, window_height, 0, &window, &renderer
        )) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
        renderer, window_width, window_height, SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    return SDL_APP_CONTINUE;
}

SDL_AppResult DumbApp::iterate(float) {
    return SDL_APP_CONTINUE;
}

SDL_AppResult DumbApp::handle_event(SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_ESCAPE:
                    return SDL_APP_SUCCESS;
            }
            break;
    }
    return SDL_APP_CONTINUE;
}

void DumbApp::quit(SDL_AppResult) {}

void DumbApp::fill(float r, float g, float b) const {
    SDL_SetRenderDrawColorFloat(renderer, r, g, b, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void DumbApp::fill(const std::array<float, 3>& rgb) const {
    fill(rgb[0], rgb[1], rgb[2]);
}

void DumbApp::fill(const RGB& rgb) const {
    fill(rgb.r, rgb.g, rgb.b);
}

void DumbApp::fill(const HSV& hsv) const {
    fill(RGB::from_hsv(hsv));
}
