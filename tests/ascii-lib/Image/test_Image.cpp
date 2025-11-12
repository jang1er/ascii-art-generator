#include <catch2/catch_test_macros.hpp>
#include "common/Image/Image.hpp"
#include "vendor/stb-image/stb_image_write.h"

#include <iostream>

bool testGrayScale(Image& img){
    for(std::size_t y = 0; y < img.height; ++y){
        for(std::size_t x = 0; x < img.width; ++x){
            double* pixel = &img.data[(x + y * img.width) * img.numberOfColorChannels];
            auto r = pixel[0]; // red component
            auto g = pixel[1]; // green component
            auto b = pixel[2]; // blue component
            if(r != g || g != b || r != b)return false;
        }
    }
    return true;
}

TEST_CASE("Image default values", "[image]") {
    Image img;
    REQUIRE(img.data == nullptr);
    REQUIRE(img.width == 0);
    REQUIRE(img.height == 0);
    REQUIRE(img.numberOfColorChannels == 0);
}


TEST_CASE("Image loading files", "[image]") {
    SECTION("Kingfisher"){
        Image img("test-images/image-kingfisher.png");

        REQUIRE(img.data);
        REQUIRE(img.width > 0);
        REQUIRE(img.height > 0);
        REQUIRE(img.numberOfColorChannels == 3);
    }

    SECTION("Donut 1"){
        Image img("test-images/image-donut.png");

        REQUIRE(img.data);
        REQUIRE(img.width > 0);
        REQUIRE(img.height > 0);
        REQUIRE(img.numberOfColorChannels == 3);
    }

    SECTION("Donut 2"){
        Image img("test-images/image-donut-2.png");

        REQUIRE(img.data);
        REQUIRE(img.width > 0);
        REQUIRE(img.height > 0);
        REQUIRE(img.numberOfColorChannels == 3);
    }
}

TEST_CASE("Grayscaling image kingfisher", "[image]"){
    Image img("test-images/image-kingfisher.png");

    REQUIRE(img.data);

    // grayscale image
    Image gray = img.ToGrayScale();

    // check metrics
    REQUIRE(gray.data);
    REQUIRE(gray.data != img.data);
    REQUIRE(img.width == gray.width);
    REQUIRE(img.height == gray.height);
    REQUIRE(img.numberOfColorChannels == gray.numberOfColorChannels);

    // check grayscale
    REQUIRE(testGrayScale(gray));

    // write to file
    if(!stbi_write_png("test-images/output-kingfisher-gray.png", gray.width, gray.height, gray.numberOfColorChannels, gray.data, gray.width * gray.numberOfColorChannels)){
        std::cout << "TEST:: Failed to write image to file" << std::endl;
    }
}

TEST_CASE("Grayscaling image donut 1", "[image]"){
    Image img("test-images/image-donut.png");

    REQUIRE(img.data);

    // grayscale image
    Image gray = img.ToGrayScale();

    // check metrics
    REQUIRE(gray.data);
    REQUIRE(gray.data != img.data);
    REQUIRE(img.width == gray.width);
    REQUIRE(img.height == gray.height);
    REQUIRE(img.numberOfColorChannels == gray.numberOfColorChannels);

    // check grayscale
    REQUIRE(testGrayScale(gray));

    // write to file
    if(!stbi_write_png("test-images/output-donut-gray.png", gray.width, gray.height, gray.numberOfColorChannels, gray.data, gray.width * gray.numberOfColorChannels)){
        std::cout << "TEST:: Failed to write image to file" << std::endl;
    }
}

TEST_CASE("Grayscaling image donut 2", "[image]"){
    Image img("test-images/image-donut-2.png");

    REQUIRE(img.data);

    // grayscale image
    Image gray = img.ToGrayScale();

    // check metrics
    REQUIRE(gray.data);
    REQUIRE(gray.data != img.data);
    REQUIRE(img.width == gray.width);
    REQUIRE(img.height == gray.height);
    REQUIRE(img.numberOfColorChannels == gray.numberOfColorChannels);

    // check grayscale
    REQUIRE(testGrayScale(gray));

    // write to file
    if(!stbi_write_png("test-images/output-donut-2-gray.png", gray.width, gray.height, gray.numberOfColorChannels, gray.data, gray.width * gray.numberOfColorChannels)){
        std::cout << "TEST:: Failed to write image to file" << std::endl;
    }
}
