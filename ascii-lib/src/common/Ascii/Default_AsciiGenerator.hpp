#pragma once

#include "AsciiGenerator.hpp"

#include <memory>

class DefaultAsciiGenerator : public AsciiGenerator {
    public:
    DefaultAsciiGenerator(std::shared_ptr<ImageScaler> imageScaler) : scaler(std::move(imageScaler)) {}

    std::string GenerateAscii(Image &image, GeneratorContext context);

    private:
    std::shared_ptr<ImageScaler> scaler;
};