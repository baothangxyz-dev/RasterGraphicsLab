
#pragma once

#include "Image.h"

#include <string>

class IPNMExporter {
public:
    virtual ~IPNMExporter() = default;

    virtual void export_image(
        const Image& image,
        const std::string& filename
    ) const = 0;
};
