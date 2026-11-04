
#include "Image.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

std::size_t Image::calculate_size(
    std::size_t width,
    std::size_t height
) {
    if (width == 0 || height == 0) {
        throw std::invalid_argument(
            "Image dimensions must be greater than zero."
        );
    }

    if (width > std::numeric_limits<std::size_t>::max() / height) {
        throw std::length_error(
            "Image dimensions are too large."
        );
    }

    return width * height;
}

Image::Image(
    std::size_t width,
    std::size_t height,
    const Color& fill_color
)
    : width(width),
      height(height),
      pixels(calculate_size(width, height), fill_color) {
}

std::size_t Image::get_width() const noexcept {
    return width;
}

std::size_t Image::get_height() const noexcept {
    return height;
}

Color& Image::at(std::size_t x, std::size_t y) {
    if (x >= width || y >= height) {
        throw std::out_of_range(
            "Pixel coordinates are outside the image."
        );
    }

    return pixels[y * width + x];
}

const Color& Image::at(
    std::size_t x,
    std::size_t y
) const {
    if (x >= width || y >= height) {
        throw std::out_of_range(
            "Pixel coordinates are outside the image."
        );
    }

    return pixels[y * width + x];
}

void Image::clear(const Color& color) {
    std::fill(pixels.begin(), pixels.end(), color);
}

void Image::resize(
    std::size_t new_width,
    std::size_t new_height,
    const Color& fill_color
) {
    const std::size_t new_size =
        calculate_size(new_width, new_height);

    std::vector<Color> new_pixels(new_size, fill_color);

    const std::size_t copy_width =
        std::min(width, new_width);

    const std::size_t copy_height =
        std::min(height, new_height);

    for (std::size_t y = 0; y < copy_height; ++y) {
        for (std::size_t x = 0; x < copy_width; ++x) {
            new_pixels[y * new_width + x] =
                pixels[y * width + x];
        }
    }

    pixels.swap(new_pixels);

    width = new_width;
    height = new_height;
}

Color* Image::data() noexcept {
    return pixels.data();
}

const Color* Image::data() const noexcept {
    return pixels.data();
}

std::size_t Image::size() const noexcept {
    return pixels.size();
}
