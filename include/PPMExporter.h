
#pragma once

#include "IPNMExporter.h"

class PPMExporter : public IPNMExporter {
public:
    void export_image(
        const Image& image,
        const std::string& filename
    ) const override;
};
