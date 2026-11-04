
#pragma once

#include "Color.h"

#include <cstddef>
#include <vector>

class Image {
private:
    std::size_t width;
    std::size_t height;
    std::vector<Color> pixels;

    static std::size_t calculate_size(
        std::size_t width,
        std::size_t height
    );

public:
    Image(
        std::size_t width,
        std::size_t height,
        const Color& fill_color = Color()
    );

    std::size_t get_width() const noexcept;
    std::size_t get_height() const noexcept;

    Color& at(std::size_t x, std::size_t y);
    const Color& at(std::size_t x, std::size_t y) const;

    void clear(const Color& color);

    void resize(
        std::size_t new_width,
        std::size_t new_height,
        const Color& fill_color = Color()
    );

    Color* data() noexcept;
    const Color* data() const noexcept;

    std::size_t size() const noexcept;
};
