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
    data = stbi_load(path.c_str(), &width, &height, &numberOfColorChannels, 3);
    if(!data){
        std::cout << "STBI::ERROR: Image loading failed for " << path << std::endl;
        return;
    }
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