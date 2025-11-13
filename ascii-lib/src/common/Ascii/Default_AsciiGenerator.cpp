#include "Default_AsciiGenerator.hpp"

#include <string>
#include <memory>
#include <algorithm>

#include "common/Image/Color.hpp"



static unsigned char asciiEdges[] = {'|', '-', '/', '\\'};

std::string DefaultAsciiGenerator::GenerateAscii(Image &image, GeneratorContext context, const std::string &pixels){
    // scale image to size
    const std::size_t width = context.width;
    const std::size_t height = context.height;
    
    auto scaledImage = scaler->ScaleImageTo(image, context.width, context.height);
    
    // convert image to grayscale
    auto grayImage = scaledImage.ToGrayScale();
    
    // use gaussian blur on image
    
    // create edge image
    
    std::string asciiString;
    
    // set ascii pixel set to use
    
    ColorMode mode = context.colorMode;
    std::size_t pixelArraySize = pixels.size();
    
    // build string
    for(std::size_t y = 0; y < height; ++y){
        if(mode != ColorMode::DEFAULT_COLOR)asciiString += "\e[37;40m";
        for(std::size_t x = 0; x < width; ++x){
            // check for edge

            // normalize gray value to ascii pixel data
            std::size_t index = static_cast<std::size_t>(grayImage.data[(x + y * width) * grayImage.numberOfColorChannels] * (pixelArraySize-1));
            index = std::clamp(index, std::size_t(0), pixelArraySize - 1);
            asciiString += pixels[index];
        }
        if(mode != ColorMode::DEFAULT_COLOR) asciiString += "\e[0m";
        asciiString += "\n";
    }
    return asciiString;
}