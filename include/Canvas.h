
#pragma once

#include "Image.h"

#include <cstdint>

class Canvas {
private:
    Image& image;

    Color pen_color;
    bool antialiasing;

    bool clip_enabled;

    std::int64_t clip_left;
    std::int64_t clip_top;
    std::int64_t clip_right;
    std::int64_t clip_bottom;

    bool is_inside_clip(int x, int y) const noexcept;

public:
    explicit Canvas(Image& image);

    void set_pen_color(const Color& color);

    const Color& get_pen_color() const noexcept;

    void set_antialiasing(bool enabled) noexcept;

    bool is_antialiasing_enabled() const noexcept;

    void draw_pixel(int x, int y);

    void draw_pixel(int x, int y, const Color& color);

    void draw_pixel_coverage(
        int x,
        int y,
        const Color& color,
        float coverage
    );

    void clear(const Color& color);

    void set_clip(int x, int y, int width, int height);

    void reset_clip() noexcept;

    Image& get_image() noexcept;

    const Image& get_image() const noexcept;
};
