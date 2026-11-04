
#pragma once

#include <cstdint>

struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

    Color();

    Color(int red, int green, int blue, int alpha = 255);

    static Color from_bytes(
        std::uint8_t red,
        std::uint8_t green,
        std::uint8_t blue,
        std::uint8_t alpha = 255
    );

    std::uint8_t to_grayscale() const;

    Color lerp(const Color& target, float t) const;

    Color blend(const Color& src) const;

    Color operator+(const Color& other) const;

    Color operator*(float factor) const;

    bool operator==(const Color& other) const;

    bool operator!=(const Color& other) const;
};
