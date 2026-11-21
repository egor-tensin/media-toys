#include "app_base.hpp"

#include <CLI/CLI.hpp>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_AppResult App::init(int argc, char** argv) {
    try {
        cmd_parser.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        cmd_parser.exit(e);
        return SDL_APP_FAILURE;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    start = now();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void** _app, int argc, char** argv) {
    const auto app = App::get();
    *_app = app;
    return app->init(argc, argv);
}

SDL_AppResult SDL_AppIterate(void* _app) {
    const auto app = reinterpret_cast<App*>(_app);
    return app->iterate(app->get_counter());
}

SDL_AppResult SDL_AppEvent(void* app, SDL_Event* event) {
    return reinterpret_cast<App*>(app)->handle_event(event);
}

void SDL_AppQuit(void* app, SDL_AppResult result) {
    reinterpret_cast<App*>(app)->quit(result);
}
