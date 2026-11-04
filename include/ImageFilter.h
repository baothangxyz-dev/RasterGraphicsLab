
#pragma once

#include "Image.h"

class ImageFilter {
public:
    static void apply_sepia(Image& image);

    static void apply_invert(Image& image);

    static void adjust_contrast(Image& image, float factor);
};
