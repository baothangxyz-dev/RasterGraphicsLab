
#include "Color.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {

std::uint8_t clamp_channel(float value) {
    const float bounded = std::clamp(value, 0.0f, 255.0f);
    return static_cast<std::uint8_t>(std::lround(bounded));
}

void validate_channel(int value) {
    if (value < 0 || value > 255) {
        throw std::invalid_argument(
            "Color channel must be between 0 and 255."
        );
    }
}

} // namespace

Color::Color()
    : r(0), g(0), b(0), a(255) {
}

Color::Color(int red, int green, int blue, int alpha)
    : r(0), g(0), b(0), a(255) {

    validate_channel(red);
    validate_channel(green);
    validate_channel(blue);
    validate_channel(alpha);

    r = static_cast<std::uint8_t>(red);
    g = static_cast<std::uint8_t>(green);
    b = static_cast<std::uint8_t>(blue);
    a = static_cast<std::uint8_t>(alpha);
}

Color Color::from_bytes(
    std::uint8_t red,
    std::uint8_t green,
    std::uint8_t blue,
    std::uint8_t alpha
) {
    Color result;
    result.r = red;
    result.g = green;
    result.b = blue;
    result.a = alpha;
    return result;
}

std::uint8_t Color::to_grayscale() const {
    const float gray =
        0.299f * static_cast<float>(r) +
        0.587f * static_cast<float>(g) +
        0.114f * static_cast<float>(b);

    return clamp_channel(gray);
}

Color Color::lerp(const Color& target, float t) const {
    t = std::clamp(t, 0.0f, 1.0f);

    return Color(
        static_cast<int>(clamp_channel(
            static_cast<float>(r) +
            (static_cast<float>(target.r) - static_cast<float>(r)) * t
        )),
        static_cast<int>(clamp_channel(
            static_cast<float>(g) +
            (static_cast<float>(target.g) - static_cast<float>(g)) * t
        )),
        static_cast<int>(clamp_channel(
            static_cast<float>(b) +
            (static_cast<float>(target.b) - static_cast<float>(b)) * t
        )),
        static_cast<int>(clamp_channel(
            static_cast<float>(a) +
            (static_cast<float>(target.a) - static_cast<float>(a)) * t
        ))
    );
}

Color Color::blend(const Color& src) const {
    const float source_alpha = static_cast<float>(src.a) / 255.0f;
    const float destination_alpha = static_cast<float>(a) / 255.0f;

    const float output_alpha =
        source_alpha + destination_alpha * (1.0f - source_alpha);

    if (output_alpha <= 0.0f) {
        return Color(0, 0, 0, 0);
    }

    const auto blend_channel = [&](std::uint8_t destination,
                                   std::uint8_t source) {
        const float result =
            (static_cast<float>(source) * source_alpha +
             static_cast<float>(destination) * destination_alpha *
                 (1.0f - source_alpha)) / output_alpha;

        return clamp_channel(result);
    };

    return Color::from_bytes(
        blend_channel(r, src.r),
        blend_channel(g, src.g),
        blend_channel(b, src.b),
        clamp_channel(output_alpha * 255.0f)
    );
}

Color Color::operator+(const Color& other) const {
    return Color(
        static_cast<int>(clamp_channel(
            static_cast<float>(r) + static_cast<float>(other.r))),
        static_cast<int>(clamp_channel(
            static_cast<float>(g) + static_cast<float>(other.g))),
        static_cast<int>(clamp_channel(
            static_cast<float>(b) + static_cast<float>(other.b))),
        static_cast<int>(clamp_channel(
            static_cast<float>(a) + static_cast<float>(other.a)))
    );
}

Color Color::operator*(float factor) const {
    return Color(
        static_cast<int>(clamp_channel(static_cast<float>(r) * factor)),
        static_cast<int>(clamp_channel(static_cast<float>(g) * factor)),
        static_cast<int>(clamp_channel(static_cast<float>(b) * factor)),
        static_cast<int>(clamp_channel(static_cast<float>(a) * factor))
    );
}

bool Color::operator==(const Color& other) const {
    return r == other.r &&
           g == other.g &&
           b == other.b &&
           a == other.a;
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}
