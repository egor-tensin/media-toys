#include "sdl_stub.hpp"

#include <SDL3/SDL.h>

namespace sdl_stub {

App app;

}

SDL_AppResult SDL_AppInit(void**, int, char*[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
            "libsdl_dumb",
            sdl_stub::app.WINDOW_WIDTH,
            sdl_stub::app.WINDOW_HEIGHT,
            0,
            &sdl_stub::app.window,
            &sdl_stub::app.renderer
        )) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
        sdl_stub::app.renderer,
        sdl_stub::app.WINDOW_WIDTH,
        sdl_stub::app.WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    sdl_stub::app.start = sdl_stub::now();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void*, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void*, SDL_AppResult) {}
