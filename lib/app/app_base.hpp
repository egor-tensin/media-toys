#pragma once

#include <SDL3/SDL.h>

class App {
public:
    static App* get();

    virtual SDL_AppResult init(int, char**);

    virtual SDL_AppResult iterate(float counter) = 0;

    virtual SDL_AppResult handle_event(SDL_Event*) = 0;

    virtual void quit(SDL_AppResult) {}

    float get_counter() const {
        return now() - start;
    }

private:
    static float now() {
        return static_cast<float>(SDL_GetTicks()) / 1000.;
    }

    float start = 0.;
};

extern "C" {

SDL_AppResult SDL_AppInit(void** app, int, char**);
SDL_AppResult SDL_AppIterate(void* app);
SDL_AppResult SDL_AppEvent(void* app, SDL_Event*);
void SDL_AppQuit(void* app, SDL_AppResult);
}
