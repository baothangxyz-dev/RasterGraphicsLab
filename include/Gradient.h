
#pragma once

#include "Color.h"

#include <cstddef>
#include <vector>

enum class GradientDirection {
    Horizontal,
    Vertical,
    Diagonal,
    Radial
};

struct GradientStop {
    float position;
    Color color;
};

class Gradient {
private:
    std::vector<GradientStop> stops;
    GradientDirection direction;

    float calculate_position(
        std::size_t x,
        std::size_t y,
        std::size_t width,
        std::size_t height
    ) const;

public:
    Gradient(
        const std::vector<GradientStop>& stops,
        GradientDirection direction
    );

    Color get_color(
        std::size_t x,
        std::size_t y,
        std::size_t width,
        std::size_t height
    ) const;
};
