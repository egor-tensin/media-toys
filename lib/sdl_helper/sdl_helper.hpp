#pragma once

#include "sdl_app.hpp"

#include <hsv.hpp>
#include <rgb.hpp>

#include <SDL3/SDL.h>

#include <array>

namespace sdl_helper {

void fill(float r, float g, float b);
void fill(const std::array<float, 3>&);
void fill(const RGB& rgb);
void fill(const HSV& hsv);

} // namespace sdl_helper

// Oh my fucking god, recent clang-format version strip the last empty line in
// "extern" god knows for what reason. TODO: remove this workaround when they
// fix their shit.
extern "C" {

SDL_AppResult SDL_AppIterate(void*);
// clang-format off

// clang-format on
}
