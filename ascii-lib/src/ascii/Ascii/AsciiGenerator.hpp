#pragma once

#include "ascii/Image/Image.hpp"
#include "ascii/Image/Scaling/AveragingImageScaler.hpp"
#include "ascii/Image/Color.hpp"

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

static const std::string defaultPixels = " .-=+*x#$&X@";
static const std::string granularPixels = " .:-=+*#%@&$WX8";
static const std::string roughPixels = " .'=-*#%@";

class AsciiGenerator{
    public:
    virtual ~AsciiGenerator() = default;

    virtual std::string GenerateAscii(Image &image, GeneratorContext context, const std::string &pixels = defaultPixels)= 0;
};