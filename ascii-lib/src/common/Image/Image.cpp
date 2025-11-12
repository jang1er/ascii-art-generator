#include "common/Image/Image.hpp"
#include "vendor/stb-image/stb_image.h"

#include <string>
#include <iostream>

Image::Image() 
    : data(nullptr), width(0), height(0), numberOfColorChannels(0) 
    {}

Image::Image(std::string path){
    int w,h, n;
    unsigned char *image_data = stbi_load(path.c_str(), &w, &h, &n, 3);
    if(!image_data){
        std::cout << "STBI::ERROR: Image loading failed for " << path << " due to insufficient memory" << std::endl;
        Free();
        return;
    }

    // set data of image
    width = static_cast<std::size_t>(w);
    height = static_cast<std::size_t>(h);
    numberOfColorChannels = 3;
    
    // convert to double
    data = new double[width * height * numberOfColorChannels];
    if(!data){
        std::cout << "Image::ERROR: Image loading failed for " << path << " due to insufficient memory" << std::endl;
        Free();
        return;
    }

    // copy data
    for(std::size_t i = 0; i < width * height * numberOfColorChannels; ++i){
        data[i] = static_cast<double>(image_data[i]) / 255; // map colors to range of 0 to 1
    }

    // free image data
    stbi_image_free(image_data);
}

void Image::Free(){
    delete[] data;
    data = 0;
    width = 0;
    height = 0;
    numberOfColorChannels = 0;
}

Image::~Image(){
    Free();
}

Image Image::ToGrayScale() const{
    if(!data || numberOfColorChannels < 3) {
        std::cerr << "Cannot grayscale: image has less than 3 channels or data is null\n";
        return Image(); // return empty image
    }

    Image grayImage;
    grayImage.width = width;
    grayImage.height = height;
    grayImage.numberOfColorChannels = numberOfColorChannels;

    // Allocate memory for new image
    grayImage.data = new double[width * height * numberOfColorChannels];
    if(!grayImage.data) {
        std::cerr << "Failed to allocate memory for grayscale image\n";
        return Image();
    }

    for(std::size_t y = 0; y < height; ++y) {
        for(std::size_t x = 0; x < width; ++x) {
            const double* srcPixel = data + (x + y * width) * numberOfColorChannels;
            double* dstPixel = grayImage.data + (x + y * width) * numberOfColorChannels;

            // Average RGB channels
            double gray = static_cast<double>(
                (srcPixel[0] + srcPixel[1] + srcPixel[2]) / 3
            );

            dstPixel[0] = gray;
            dstPixel[1] = gray;
            dstPixel[2] = gray;

            // Copy alpha if present
            if(numberOfColorChannels == 4) {
                dstPixel[3] = srcPixel[3];
            }
        }
    }

    return grayImage;
}