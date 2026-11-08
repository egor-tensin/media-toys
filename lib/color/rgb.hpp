#pragma once

#include "hsv.hpp"

#include <cmath>
#include <cstdint>

struct RGB {
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;

    static constexpr RGB from_hex(uint32_t hex_color) {
        return {
            .r = static_cast<float>((hex_color >> 16) & 0xFF) / 255.f,
            .g = static_cast<float>((hex_color >> 8) & 0xFF) / 255.f,
            .b = static_cast<float>(hex_color & 0xFF) / 255.f,
        };
    }

    constexpr RGB lerp(const RGB& other, float t) const {
        // std::lerp on basic numbers is just a + t(b - a).
        // This is called linear interpolation, and I really do wish I was
        // smarter than I am.
        return {
            .r = std::lerp(r, other.r, t),
            .g = std::lerp(g, other.g, t),
            .b = std::lerp(b, other.b, t),
        };
    }

    static constexpr RGB from_hsv(const HSV& hsv) {
        const auto c = hsv.v * hsv.s;
        const auto x = c * (1.f - std::abs(std::fmod(hsv.h / 60.f, 2.f) - 1.f));
        const auto m = hsv.v - c;

        RGB result{};

        // The HSV color wheel is divided into 6 sectors:
        // < 60 - red to yellow,
        // < 120 - yellow to green,
        // < 180 - green to cyan,
        // < 240 - cyan to blue,
        // < 300 - blue to magenta
        // < 360 - magenta back to red again.
        if (hsv.h < 60.f)
            result = {c, x, 0.f};
        else if (hsv.h < 120.f)
            result = {x, c, 0.f};
        else if (hsv.h < 180.f)
            result = {0.f, c, x};
        else if (hsv.h < 240.f)
            result = {0.f, x, c};
        else if (hsv.h < 300.f)
            result = {x, 0.f, c};
        else
            result = {c, 0.f, x};

        return {result.r + m, result.g + m, result.b + m};
    }
};
