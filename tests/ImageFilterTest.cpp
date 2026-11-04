#include "Image.h"
#include "ImageFilter.h"
#include "PPMExporter.h"

#include <iostream>
#include <exception>
#include <filesystem>
#include <string>

int main() {
    try {
        const Image original(200, 200, Color(120, 80, 40));

        PPMExporter exporter;

        const std::filesystem::path output_dir = "output/ppm";
        std::filesystem::create_directories(output_dir);

        Image sepia = original;
        ImageFilter::apply_sepia(sepia);
        exporter.export_image(
            sepia,
            (output_dir / "filter_sepia.ppm").string()
        );

        Image inverted = original;
        ImageFilter::apply_invert(inverted);
        exporter.export_image(
            inverted,
            (output_dir / "filter_invert.ppm").string()
        );

        Image contrast = original;
        ImageFilter::adjust_contrast(contrast, 1.5f);
        exporter.export_image(
            contrast,
            (output_dir / "filter_contrast.ppm").string()
        );

        std::cout << "All image filters tested successfully!\n";
        std::cout << "Created:\n";
        std::cout << "- output/ppm/filter_sepia.ppm\n";
        std::cout << "- output/ppm/filter_invert.ppm\n";
        std::cout << "- output/ppm/filter_contrast.ppm\n";
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}