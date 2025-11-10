#pragma once

#include <string>

class Image{
    public:
    /// @brief 
    unsigned char *data;
    /// @brief 
    int width;
    /// @brief 
    int height;
    /// @brief 
    int numberOfColorChannels;

    Image();
    Image(std::string path);

    ~Image();

    void Free();

    /// @brief Grayscales an image by averaging rgba channels
    /// @param image Image to grayscale
    void ToGreyScale();

};