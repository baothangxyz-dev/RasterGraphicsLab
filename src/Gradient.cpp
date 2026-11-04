
#include "Gradient.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

Gradient::Gradient(
    const std::vector<GradientStop>& stops,
    GradientDirection direction
)
    : stops(stops),
      direction(direction) {

    if (this->stops.size() < 2) {
        throw std::invalid_argument(
            "A gradient must have at least two color stops."
        );
    }

    for (std::size_t i = 0; i < this->stops.size(); ++i) {
        const float position = this->stops[i].position;

        if (!std::isfinite(position) ||
            position < 0.0f ||
            position > 1.0f) {
            throw std::invalid_argument(
                "Gradient stop position must be between 0 and 1."
            );
        }

        if (i > 0 &&
            position <= this->stops[i - 1].position) {
            throw std::invalid_argument(
                "Gradient stop positions must be strictly increasing."
            );
        }
    }
}

float Gradient::calculate_position(
    std::size_t x,
    std::size_t y,
    std::size_t width,
    std::size_t height
) const {
    if (width == 0 || height == 0) {
        throw std::invalid_argument(
            "Image dimensions must be greater than zero."
        );
    }

    if (x >= width || y >= height) {
        throw std::out_of_range(
            "Gradient coordinates are outside the image."
        );
    }

    const float nx = width > 1
        ? static_cast<float>(x) /
              static_cast<float>(width - 1)
        : 0.5f;

    const float ny = height > 1
        ? static_cast<float>(y) /
              static_cast<float>(height - 1)
        : 0.5f;

    switch (direction) {
    case GradientDirection::Horizontal:
        return nx;

    case GradientDirection::Vertical:
        return ny;

    case GradientDirection::Diagonal:
        return (nx + ny) / 2.0f;

    case GradientDirection::Radial: {
        const float dx = nx - 0.5f;
        const float dy = ny - 0.5f;

        const float distance =
            std::sqrt(dx * dx + dy * dy);

        const float max_distance =
            std::sqrt(
                (width > 1 ? 0.25f : 0.0f) +
                (height > 1 ? 0.25f : 0.0f)
            );

        if (max_distance == 0.0f) {
            return 0.0f;
        }

        return std::clamp(
            distance / max_distance,
            0.0f,
            1.0f
        );
    }
    }

    throw std::invalid_argument("Unknown gradient direction.");
}

Color Gradient::get_color(
    std::size_t x,
    std::size_t y,
    std::size_t width,
    std::size_t height
) const {
    const float position =
        calculate_position(x, y, width, height);

    if (position <= stops.front().position) {
        return stops.front().color;
    }

    if (position >= stops.back().position) {
        return stops.back().color;
    }

    for (std::size_t i = 0; i + 1 < stops.size(); ++i) {
        const GradientStop& start = stops[i];
        const GradientStop& end = stops[i + 1];

        if (position >= start.position &&
            position <= end.position) {

            const float t =
                (position - start.position) /
                (end.position - start.position);

            return start.color.lerp(end.color, t);
        }
    }

    return stops.back().color;
}
