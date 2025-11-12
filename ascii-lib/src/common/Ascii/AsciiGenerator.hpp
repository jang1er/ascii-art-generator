#pragma once

#include "../Image/Image.hpp"
#include "../Image/Scaling/AveragingImageScaler.hpp"

#include <string>

struct GeneratorContext{
    std::size_t width;
    std::size_t height;
    bool useColor;
    bool useEdgeDetection;
    bool forceDefaultColor;
};

class AsciiGenerator{
    public:
    virtual ~AsciiGenerator() = default;

    virtual std::string GenerateAscii(Image &image, GeneratorContext context) = 0;
};