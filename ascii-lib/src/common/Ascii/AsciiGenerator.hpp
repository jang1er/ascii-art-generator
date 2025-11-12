#pragma once

#include "common/Image/Image.hpp"
#include "common/Image/Scaling/AveragingImageScaler.hpp"
#include "common/Image/Color.hpp"

#include <string>

enum ColorMode{
    DEFAULT_COLOR,
    BLACK_WHITE,
    ANSII8,
    ANSII16,
    ANSII256,
    ANSIIRGB
};

enum EdgeDetectionMode{
    NO_EDGE,
    SOBOL
};

struct GeneratorContext{
    std::size_t width;
    std::size_t height;
    ColorMode colorMode;
    EdgeDetectionMode detectionMode;
};

class AsciiGenerator{
    public:
    virtual ~AsciiGenerator() = default;

    virtual std::string GenerateAscii(Image &image, GeneratorContext context) = 0;
};