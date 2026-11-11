#pragma once

#include "sdl_app.hpp"
#include "sdl_renderer.hpp"

#include <SDL3/SDL.h>

// Oh my fucking god, recent clang-format version strip the last empty line in
// "extern" god knows for what reason. TODO: remove this workaround when they
// fix their shit.
extern "C" {

SDL_AppResult SDL_AppIterate(void*);
// clang-format off

// clang-format on
}
