#pragma once

#include <string>
#include <cstddef>

#include "vendor/stb-image/stb_image.h"
#include "vendor/stb-image/stb_image_write.h"

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

    /// @brief 
    Image();

    /// @brief 
    /// @param path 
    Image(std::string path);

    /// @brief 
    ~Image();

    /// @brief 
    void Free();

    /// @brief 
    /// @return 
    std::size_t size() const;

    /// @brief 
    /// @return 
    bool isEmpty() const;

    /// @brief Grayscales an image by averaging rgba channels
    /// @param image Image to grayscale
    Image ToGrayScale() const;

    /// @brief 
    /// @param path 
    void WriteToFile(const std::string &path, const std::string &fileName) const;

    /*################ OPERATOR OVERLOADS ####################### */

    double& operator[] (std::size_t index){
        return data[index];
    }

    double& operator[] (std::size_t index) const{
        return data[index];
    }

    double& operator() (std::size_t x, std::size_t y){
        return data[(x + y * width) * numberOfColorChannels];
    }

    double& operator() (std::size_t x, std::size_t y) const{
        return data[(x + y * width) * numberOfColorChannels];
    }

    double& operator() (std::size_t x, std::size_t y, std::size_t c){
        return data[(x + y * width) * numberOfColorChannels + c];
    }

    double& operator() (std::size_t x, std::size_t y, std::size_t c) const{
        return data[(x + y * width) * numberOfColorChannels + c];
    }


    /*################ MOVE SEMANTICS ####################### */

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