
#include "Color.h"
#include "Image.h"
#include "Gradient.h"
#include "ImageFilter.h"
#include "PPMExporter.h"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>
int main() {
    try {
        std::cout << "========================================\n";
        std::cout << "       RASTER GRAPHICS LAB\n";
        std::cout << "            VARIANT 1\n";
        std::cout << "========================================\n";

        // Step 1: Image dimensions
        std::size_t width = 0;
        std::size_t height = 0;

        constexpr std::size_t MAX_DIMENSION = 4096;
constexpr std::size_t MAX_PIXELS = 4'000'000;

std::cout << "\nEnter image width: ";
if (!(std::cin >> width) || width == 0) {
    throw std::invalid_argument("Invalid image width.");
}

std::cout << "Enter image height: ";
if (!(std::cin >> height) || height == 0) {
    throw std::invalid_argument("Invalid image height.");
}

if (width > MAX_DIMENSION ||
    height > MAX_DIMENSION ||
    width > MAX_PIXELS / height) {
    throw std::invalid_argument(
        "Image dimensions are too large. "
        "Maximum dimension is 4096 and maximum pixel count is 4000000."
    );
}

        // Step 2: Gradient direction
        std::cout << "\nSelect gradient direction:\n";
        std::cout << "1. Horizontal\n";
        std::cout << "2. Vertical\n";
        std::cout << "3. Diagonal\n";
        std::cout << "4. Radial\n";
        std::cout << "Your choice: ";

        int direction_choice = 0;

        if (!(std::cin >> direction_choice) ||
            direction_choice < 1 ||
            direction_choice > 4) {
            throw std::invalid_argument(
                "Invalid gradient direction."
            );
        }

        GradientDirection direction;

        switch (direction_choice) {
        case 1:
            direction = GradientDirection::Horizontal;
            break;
        case 2:
            direction = GradientDirection::Vertical;
            break;
        case 3:
            direction = GradientDirection::Diagonal;
            break;
        default:
            direction = GradientDirection::Radial;
            break;
        }

        // Step 3: Enter custom gradient stops
        int stop_count = 0;

        std::cout << "\nEnter number of color stops (K >= 2): ";

        if (!(std::cin >> stop_count) || stop_count < 2) {
            throw std::invalid_argument(
                "A gradient requires at least two color stops."
            );
        }

        std::vector<GradientStop> stops;
        stops.reserve(static_cast<std::size_t>(stop_count));

        for (int i = 0; i < stop_count; ++i) {
            float position = 0.0f;
            int red = 0;
            int green = 0;
            int blue = 0;

            std::cout << "\nColor stop " << i + 1 << "\n";

            std::cout << "Position (0 to 1): ";
            if (!(std::cin >> position)) {
                throw std::invalid_argument(
                    "Invalid gradient position."
                );
            }

            std::cout << "Red (0 to 255): ";
            if (!(std::cin >> red)) {
                throw std::invalid_argument("Invalid red value.");
            }

            std::cout << "Green (0 to 255): ";
            if (!(std::cin >> green)) {
                throw std::invalid_argument("Invalid green value.");
            }

            std::cout << "Blue (0 to 255): ";
            if (!(std::cin >> blue)) {
                throw std::invalid_argument("Invalid blue value.");
            }

            if (red < 0 || red > 255 ||
                green < 0 || green > 255 ||
                blue < 0 || blue > 255) {
                throw std::invalid_argument(
                    "RGB values must be between 0 and 255."
                );
            }

            stops.push_back({
                position,
                Color(red, green, blue)
            });
        }

        // Gradient constructor validates stop positions
        Gradient gradient(stops, direction);

        // Step 4: Generate image
        Image image(width, height, Color(255, 255, 255));

        for (std::size_t y = 0; y < height; ++y) {
            for (std::size_t x = 0; x < width; ++x) {
                image.at(x, y) = gradient.get_color(
                    x, y, width, height
                );
            }
        }

        std::cout << "\nGradient generated successfully!\n";

        // Step 5: Select image filter
        std::cout << "\nSelect image filter:\n";
        std::cout << "0. Original image\n";
        std::cout << "1. Sepia\n";
        std::cout << "2. Invert\n";
        std::cout << "3. Contrast\n";
        std::cout << "Your choice: ";

        int filter_choice = 0;

        if (!(std::cin >> filter_choice) ||
            filter_choice < 0 ||
            filter_choice > 3) {
            throw std::invalid_argument(
                "Invalid filter choice."
            );
        }

        std::string filter_name = "original";

        switch (filter_choice) {
        case 1:
            ImageFilter::apply_sepia(image);
            filter_name = "sepia";
            break;

        case 2:
            ImageFilter::apply_invert(image);
            filter_name = "invert";
            break;

        case 3: {
            float factor = 0.0f;

            std::cout << "Enter contrast factor: ";

            if (!(std::cin >> factor)) {
                throw std::invalid_argument(
                    "Invalid contrast factor."
                );
            }

            ImageFilter::adjust_contrast(image, factor);
            filter_name = "contrast";
            break;
        }

        default:
            break;
        }

        // Step 6: Export PPM P3
        const std::filesystem::path output_dir = "output/ppm";

std::filesystem::create_directories(output_dir);

const std::filesystem::path output_path =
    output_dir / ("variant1_" + filter_name + ".ppm");

const std::string filename = output_path.string();

PPMExporter exporter;
exporter.export_image(image, filename);
        std::cout << "\n========================================\n";
        std::cout << "       PROCESS COMPLETED\n";
        std::cout << "========================================\n";
        std::cout << "Image size: "
                  << width << " x " << height << "\n";
        std::cout << "Color stops: " << stop_count << "\n";
        std::cout << "Output file: " << filename << "\n";
        std::cout << "Format: PPM P3\n";
        std::cout << "========================================\n";
    }
    catch (const std::exception& error) {
        std::cerr << "\nError: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
