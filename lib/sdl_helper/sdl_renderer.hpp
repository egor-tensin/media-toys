#pragma once

#include <hsv.hpp>
#include <rgb.hpp>

#include <array>

namespace sdl_helper {

void fill(float r, float g, float b);
void fill(const std::array<float, 3>&);
void fill(const RGB& rgb);
void fill(const HSV& hsv);

} // namespace sdl_helper
