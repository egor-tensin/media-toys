#include "sdl_helper.hpp"

#include <rgb.hpp>

#include <SDL3/SDL.h>

namespace sdl_helper {

App app;

void fill(float r, float g, float b) {
    SDL_SetRenderDrawColorFloat(sdl_helper::app.renderer, r, g, b, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(sdl_helper::app.renderer);
    SDL_RenderPresent(sdl_helper::app.renderer);
}

void fill(const std::array<float, 3>& rgb) {
    fill(rgb[0], rgb[1], rgb[2]);
}

void fill(const RGB& rgb) {
    fill(rgb.r, rgb.g, rgb.b);
}

} // namespace sdl_helper

SDL_AppResult SDL_AppInit(void**, int, char*[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
            "libsdl_dumb",
            sdl_helper::app.WINDOW_WIDTH,
            sdl_helper::app.WINDOW_HEIGHT,
            0,
            &sdl_helper::app.window,
            &sdl_helper::app.renderer
        )) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
        sdl_helper::app.renderer,
        sdl_helper::app.WINDOW_WIDTH,
        sdl_helper::app.WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    sdl_helper::app.start = sdl_helper::now();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void*, SDL_Event* event) {
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

void SDL_AppQuit(void*, SDL_AppResult) {}
