
#include "Canvas.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

Canvas::Canvas(Image& image)
    : image(image),
      pen_color(0, 0, 0),
      antialiasing(false),
      clip_enabled(false),
      clip_left(0),
      clip_top(0),
      clip_right(0),
      clip_bottom(0) {
}

void Canvas::set_pen_color(const Color& color) {
    pen_color = color;
}

const Color& Canvas::get_pen_color() const noexcept {
    return pen_color;
}

void Canvas::set_antialiasing(bool enabled) noexcept {
    antialiasing = enabled;
}

bool Canvas::is_antialiasing_enabled() const noexcept {
    return antialiasing;
}

bool Canvas::is_inside_clip(int x, int y) const noexcept {
    if (!clip_enabled) {
        return true;
    }

    const std::int64_t px = x;
    const std::int64_t py = y;

    return px >= clip_left &&
           px < clip_right &&
           py >= clip_top &&
           py < clip_bottom;
}

void Canvas::draw_pixel(int x, int y) {
    draw_pixel(x, y, pen_color);
}

void Canvas::draw_pixel(
    int x,
    int y,
    const Color& color
) {
    if (x < 0 || y < 0) {
        return;
    }

    if (!is_inside_clip(x, y)) {
        return;
    }

    const auto px = static_cast<std::size_t>(x);
    const auto py = static_cast<std::size_t>(y);

    if (px >= image.get_width() ||
        py >= image.get_height()) {
        return;
    }

    Color& destination = image.at(px, py);
    destination = destination.blend(color);
}

void Canvas::draw_pixel_coverage(
    int x,
    int y,
    const Color& color,
    float coverage
) {
    if (!std::isfinite(coverage)) {
        throw std::invalid_argument(
            "Pixel coverage must be finite."
        );
    }

    coverage = std::clamp(coverage, 0.0f, 1.0f);

    if (coverage <= 0.0f) {
        return;
    }

    const float alpha =
        static_cast<float>(color.a) * coverage;

    const auto adjusted_alpha =
        static_cast<std::uint8_t>(std::lround(alpha));

    const Color adjusted_color = Color::from_bytes(
        color.r,
        color.g,
        color.b,
        adjusted_alpha
    );

    draw_pixel(x, y, adjusted_color);
}

void Canvas::clear(const Color& color) {
    image.clear(color);
}

void Canvas::set_clip(
    int x,
    int y,
    int width,
    int height
) {
    if (width < 0 || height < 0) {
        throw std::invalid_argument(
            "Clip dimensions cannot be negative."
        );
    }

    clip_left = x;
    clip_top = y;

    clip_right =
        static_cast<std::int64_t>(x) + width;

    clip_bottom =
        static_cast<std::int64_t>(y) + height;

    clip_enabled = true;
}

void Canvas::reset_clip() noexcept {
    clip_enabled = false;
}

Image& Canvas::get_image() noexcept {
    return image;
}

const Image& Canvas::get_image() const noexcept {
    return image;
}
