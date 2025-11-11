#include "common/Image/Image.hpp"
#include "vendor/stb-image/stb_image.h"

#include <string>
#include <iostream>

Image::Image(){
    data = nullptr;
    width = 0;
    height = 0;
    numberOfColorChannels = 0;
}

Image::Image(std::string path){
    int w,h, n;
    data = stbi_load(path.c_str(), &w, &h, &n, 3);
    if(!data){
        std::cout << "STBI::ERROR: Image loading failed for " << path << std::endl;
        Free();
        return;
    }

    // set data of image
    width = static_cast<std::size_t>(w);
    height = static_cast<std::size_t>(h);
    numberOfColorChannels = 3;
}

void Image::Free(){
    stbi_image_free(data);
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
    grayImage.data = new unsigned char[width * height * numberOfColorChannels];
    if(!grayImage.data) {
        std::cerr << "Failed to allocate memory for grayscale image\n";
        return Image();
    }

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            const unsigned char* srcPixel = data + (x + y * width) * numberOfColorChannels;
            unsigned char* dstPixel = grayImage.data + (x + y * width) * numberOfColorChannels;

            // Average RGB channels
            unsigned char gray = static_cast<unsigned char>(
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