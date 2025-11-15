#include "AveragingImageScaler.hpp"
#include "../Image.hpp"
#include <cmath>
#include <iostream>

Image AveragingScaler::ScaleImageTo(const Image &image, std::size_t newWidth, std::size_t newHeight){
    // make scaled image
    Image scaledImage;
    scaledImage.width = newWidth;
    scaledImage.height = newHeight;
    scaledImage.numberOfColorChannels = image.numberOfColorChannels;

    // allocate big enough memory
    double *scaledData = new double[scaledImage.size()];
    scaledImage.data = scaledData;

    if(!scaledData){
        std::cout << "ERROR::SCALING can not allocate memory for sclaed image" << std::endl;
        scaledImage.Free();
        return scaledImage; // return empty image
    }
    
    // use floating-point ratios
    float dx = static_cast<float>(image.width) / static_cast<float>(newWidth);
    float dy = static_cast<float>(image.height) / static_cast<float>(newHeight);
    
    for (std::size_t y = 0; y < newHeight; ++y) {
        for (std::size_t x = 0; x < newWidth; ++x) {
            // compute start and end of each block
            float srcX0 = static_cast<float>(x) * dx;
            float srcX1 = static_cast<float>(x + 1) * dx;
            float srcY0 = static_cast<float>(y) * dy;
            float srcY1 = static_cast<float>(y + 1) * dy;
        
            // snap to pixels
            std::size_t x0 = static_cast<std::size_t>(srcX0);
            std::size_t x1 = static_cast<std::size_t>(std::ceil(srcX1));
            std::size_t y0 = static_cast<std::size_t>(srcY0);
            std::size_t y1 = static_cast<std::size_t>(std::ceil(srcY1));
        
            double sum[4] = {0.0};
            int samples = 0;
        
            // accumalate all rgb values
            for (std::size_t sy = y0; sy < y1 && sy < image.height; ++sy) {
                for (std::size_t sx = x0; sx < x1 && sx < image.width; ++sx) {
                    for (std::size_t c = 0; c < image.numberOfColorChannels; ++c) {
                        sum[c] += image(sx, sy, c);
                    }
                    samples++;
                }
            }
        
            for (std::size_t c = 0; c < image.numberOfColorChannels; ++c) {
                scaledImage(x, y, c) = static_cast<double>(sum[c] / samples);
            }
        }
    }


    return scaledImage;
};

Image AveragingScaler::ScaleImageTo(const Image &image, float scale){
    std::size_t newWidth = static_cast<std::size_t>(static_cast<float>(image.width) * scale);
    std::size_t newHeight = static_cast<std::size_t>(static_cast<float>(image.height) * scale);
    return ScaleImageTo(image, newWidth, newHeight);
}