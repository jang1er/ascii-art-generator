#pragma once

#include <string>
#include <cstddef>

class Image{
    public:
    /// @brief 
    double *data;
    /// @brief 
    std::size_t width;
    /// @brief 
    std::size_t height;
    /// @brief 
    std::size_t numberOfColorChannels;

    Image();
    Image(std::string path);

    ~Image();

    void Free();

    /// @brief Grayscales an image by averaging rgba channels
    /// @param image Image to grayscale
    Image ToGrayScale() const;

    // Move Semantics Functions

    // Copy Constructor (deep copy)
    Image(const Image& other)
    : width(other.width), height(other.height), numberOfColorChannels(other.numberOfColorChannels)
    {
        if (other.data){
            std::size_t size = width * height * numberOfColorChannels;
            data = new double[size];
            std::copy(other.data, other.data + size, data); // copy data
        }
    }

    // Copy Assignment (deep copy)
    Image& operator=(const Image& other){
        if(this != &other){
            delete[] data;
            width = other.width;
            height = other.height;
            numberOfColorChannels = other.numberOfColorChannels;
            if(other.data){
                std::size_t size = width * height * numberOfColorChannels;
                data = new double[size];
                std::copy(other.data, other.data + size, data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Move Constructor
    Image(Image&& other) noexcept
        : data(other.data), width(other.width), height(other.height), numberOfColorChannels(other.numberOfColorChannels)
    {
        other.data = nullptr;
        other.width = other.height = other.numberOfColorChannels = 0;
    }

    // Move assignment
    Image& operator=(Image&& other) noexcept {
        if(this != &other){
            delete[] data;
            width = other.width;
            height = other.height;
            numberOfColorChannels = other.numberOfColorChannels;
            data = other.data;

            other.data = nullptr;
            other.width = other.height = other.numberOfColorChannels = 0;
        }
        return *this;
    }

};