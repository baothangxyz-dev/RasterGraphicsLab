
#include "PPMExporter.h"

#include <fstream>
#include <stdexcept>
#include <string>

void PPMExporter::export_image(
    const Image& image,
    const std::string& filename
) const {
    std::ofstream output(filename);

    if (!output.is_open()) {
        throw std::runtime_error(
            "Cannot open PPM output file: " + filename
        );
    }

    output << "P3\n";
    output << image.get_width() << " "
           << image.get_height() << "\n";
    output << "255\n";

    std::string current_line;
    std::size_t line_length = 0;

    for (std::size_t y = 0; y < image.get_height(); ++y) {
        for (std::size_t x = 0; x < image.get_width(); ++x) {
            const Color& pixel = image.at(x, y);

            const std::string pixel_text =
                std::to_string(static_cast<int>(pixel.r)) + " " +
                std::to_string(static_cast<int>(pixel.g)) + " " +
                std::to_string(static_cast<int>(pixel.b));

            const std::size_t separator =
                current_line.empty() ? 0 : 1;

            if (line_length + separator + pixel_text.length() > 70) {
                output << current_line << "\n";
                current_line.clear();
                line_length = 0;
            }

            if (!current_line.empty()) {
                current_line += " ";
                ++line_length;
            }

            current_line += pixel_text;
            line_length += pixel_text.length();
        }
    }

    if (!current_line.empty()) {
        output << current_line << "\n";
    }

    if (!output) {
        throw std::runtime_error(
            "Failed to write PPM output file."
        );
    }
}
