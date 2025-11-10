#pragma once
#include "Image.hpp"
#include "ImageScaler.hpp"


class AveragingScaler : public ImageScaler {
public:
    Image ScaleImageTo(const Image &image, int newWidth, int newHeight) override;
    Image ScaleImageTo(const Image &image, float scale) override;
};