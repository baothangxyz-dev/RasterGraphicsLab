
#include "Gradient.h"
#include "Image.h"
#include "PPMExporter.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
void test_gradient(
    const std::string& name,
    GradientDirection direction
) {
    const std::vector<GradientStop> stops = {
        {0.0f, Color(255, 0, 0)},
        {0.5f, Color(0, 255, 0)},
        {1.0f, Color(0, 0, 255)}
    };

    Gradient gradient(stops, direction);
    Image image(200, 200, Color(255, 255, 255));

    for (std::size_t y = 0; y < image.get_height(); ++y) {
        for (std::size_t x = 0; x < image.get_width(); ++x) {
            image.at(x, y) = gradient.get_color(
                x, y,
                image.get_width(),
                image.get_height()
            );
        }
    }

   PPMExporter exporter;

const std::filesystem::path output_dir = "output/ppm";
std::filesystem::create_directories(output_dir);

const std::filesystem::path output_path =
    output_dir / (name + ".ppm");

const std::string filename = output_path.string();

exporter.export_image(image, filename);

std::cout << "Created: " << filename << "\n";
}

int main() {
    std::cout << "=================================\n";
    std::cout << "    GRADIENT PPM EXPORT TEST\n";
    std::cout << "=================================\n";

    try {
        test_gradient(
            "horizontal",
            GradientDirection::Horizontal
        );

        test_gradient(
            "vertical",
            GradientDirection::Vertical
        );

        test_gradient(
            "diagonal",
            GradientDirection::Diagonal
        );

        test_gradient(
            "radial",
            GradientDirection::Radial
        );

        std::cout << "\nAll PPM files created successfully!\n";
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
