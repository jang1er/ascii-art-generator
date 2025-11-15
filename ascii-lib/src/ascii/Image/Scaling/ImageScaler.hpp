#pragma once

#include "../Image.hpp"

class ImageScaler{
    public:
    virtual ~ImageScaler() = default;

    virtual Image ScaleImageTo(const Image &image, std::size_t newWidth, std::size_t newHeight) = 0;
    virtual Image ScaleImageTo(const Image &image, float scale) = 0;
};