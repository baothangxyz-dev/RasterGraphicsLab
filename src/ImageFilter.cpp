
#include "ImageFilter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {

int clamp_channel(float value) {
    return static_cast<int>(
        std::lround(std::clamp(value, 0.0f, 255.0f))
    );
}

} // namespace

void ImageFilter::apply_sepia(Image& image) {
    for (std::size_t y = 0; y < image.get_height(); ++y) {
        for (std::size_t x = 0; x < image.get_width(); ++x) {
            Color& pixel = image.at(x, y);

            const float red = static_cast<float>(pixel.r);
            const float green = static_cast<float>(pixel.g);
            const float blue = static_cast<float>(pixel.b);

            const int new_red = clamp_channel(
                0.393f * red + 0.769f * green + 0.189f * blue
            );

            const int new_green = clamp_channel(
                0.349f * red + 0.686f * green + 0.168f * blue
            );

            const int new_blue = clamp_channel(
                0.272f * red + 0.534f * green + 0.131f * blue
            );

            pixel = Color(
                new_red,
                new_green,
                new_blue,
                static_cast<int>(pixel.a)
            );
        }
    }
}

void ImageFilter::apply_invert(Image& image) {
    for (std::size_t y = 0; y < image.get_height(); ++y) {
        for (std::size_t x = 0; x < image.get_width(); ++x) {
            Color& pixel = image.at(x, y);

            pixel = Color(
                255 - static_cast<int>(pixel.r),
                255 - static_cast<int>(pixel.g),
                255 - static_cast<int>(pixel.b),
                static_cast<int>(pixel.a)
            );
        }
    }
}

void ImageFilter::adjust_contrast(Image& image, float factor) {
    if (!std::isfinite(factor) || factor < 0.0f) {
        throw std::invalid_argument(
            "Contrast factor must be finite and non-negative."
        );
    }

    for (std::size_t y = 0; y < image.get_height(); ++y) {
        for (std::size_t x = 0; x < image.get_width(); ++x) {
            Color& pixel = image.at(x, y);

            const auto adjust = [factor](std::uint8_t channel) {
                return clamp_channel(
                    (static_cast<float>(channel) - 128.0f) *
                    factor + 128.0f
                );
            };

            pixel = Color(
                adjust(pixel.r),
                adjust(pixel.g),
                adjust(pixel.b),
                static_cast<int>(pixel.a)
            );
        }
    }
}
