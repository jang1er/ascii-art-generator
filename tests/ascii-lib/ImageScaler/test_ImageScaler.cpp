#include <catch2/catch_test_macros.hpp>
#include "common/Image/Image.hpp"
#include "common/Image/Scaling/AveragingImageScaler.hpp"
#include "vendor/stb-image/stb_image_write.h"

#include <iostream>

void InitImage(Image &img, size_t width, size_t height, size_t nocc){
    img.width = width;
    img.height = height;
    img.numberOfColorChannels = nocc;
    double *data = new double[width * height * nocc];
    REQUIRE(data != nullptr);
    img.data = data;

    for(size_t y = 0; y < height; ++y){
        for(size_t x = 0; x < width; ++x){
            for(size_t c = 0; c < nocc; ++c){
                data[(x + y * width) * nocc + c] = nocc + 1;
            }
        }
    }
}

bool TestImage(const Image &img){
    for(size_t y = 0; y < img.height; ++y){
        for(size_t x = 0; x < img.width; ++x){
            for(size_t c = 0; c < img.numberOfColorChannels; ++c){
                if(!img.data[(x + y * img.width) * img.numberOfColorChannels] == img.numberOfColorChannels + 1)return false;
            }
        }
    }
    return true;
}

TEST_CASE("ImageScaler default test", "[imageScaler]") {
    Image img;
    size_t width = 100;
    size_t height = 100;
    size_t nocc = 4;

    // init the image
    InitImage(img, width, height, nocc);

    // get scaler
    AveragingScaler scaler;

    SECTION( "scaling to 1/2 uniformly" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/2, height/2);
        REQUIRE(scaledImg.width == width/2);
        REQUIRE(scaledImg.height == height/2);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/4 uniformly" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/4, height/4);
        REQUIRE(scaledImg.width == width/4);
        REQUIRE(scaledImg.height == height/4);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/8 uniformly" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/8, height/8);
        REQUIRE(scaledImg.width == width/8);
        REQUIRE(scaledImg.height == height/8);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/2 width" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/2, height);
        REQUIRE(scaledImg.width == width/2);
        REQUIRE(scaledImg.height == height);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/2 height" ){
        auto scaledImg = scaler.ScaleImageTo(img, width, height/2);
        REQUIRE(scaledImg.width == width);
        REQUIRE(scaledImg.height == height/2);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/4 width 1/2 height" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/4, height/2);
        REQUIRE(scaledImg.width == width/4);
        REQUIRE(scaledImg.height == height/2);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/2 width 1/4 height" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/2, height/4);
        REQUIRE(scaledImg.width == width/2);
        REQUIRE(scaledImg.height == height/4);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

}

TEST_CASE("ImageScaler non-uniform test", "[imageScaler]") {
    Image img;
    size_t width = 1920;
    size_t height = 1080;
    size_t nocc = 3;

    // init the image
    InitImage(img, width, height, nocc);

    // get scaler
    AveragingScaler scaler;

    SECTION( "scaling to 1/2 uniformly" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/2, height/2);
        REQUIRE(scaledImg.width == width/2);
        REQUIRE(scaledImg.height == height/2);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/4 uniformly" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/4, height/4);
        REQUIRE(scaledImg.width == width/4);
        REQUIRE(scaledImg.height == height/4);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/8 uniformly" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/8, height/8);
        REQUIRE(scaledImg.width == width/8);
        REQUIRE(scaledImg.height == height/8);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/2 width" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/2, height);
        REQUIRE(scaledImg.width == width/2);
        REQUIRE(scaledImg.height == height);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/2 height" ){
        auto scaledImg = scaler.ScaleImageTo(img, width, height/2);
        REQUIRE(scaledImg.width == width);
        REQUIRE(scaledImg.height == height/2);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/4 width 1/2 height" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/4, height/2);
        REQUIRE(scaledImg.width == width/4);
        REQUIRE(scaledImg.height == height/2);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

    SECTION( "scaling to 1/2 width 1/4 height" ){
        auto scaledImg = scaler.ScaleImageTo(img, width/2, height/4);
        REQUIRE(scaledImg.width == width/2);
        REQUIRE(scaledImg.height == height/4);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }
    SECTION( "scaling to fixed 100 x 100" ){
        auto scaledImg = scaler.ScaleImageTo(img,100,100);
        REQUIRE(scaledImg.width == 100);
        REQUIRE(scaledImg.height == 100);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }
    SECTION( "scaling to fixed 200 x 100" ){
        auto scaledImg = scaler.ScaleImageTo(img,200,100);
        REQUIRE(scaledImg.width == 200);
        REQUIRE(scaledImg.height == 100);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }
    SECTION( "scaling to fixed 640 x 320" ){
        auto scaledImg = scaler.ScaleImageTo(img,640,320);
        REQUIRE(scaledImg.width == 640);
        REQUIRE(scaledImg.height == 320);
        REQUIRE(scaledImg.numberOfColorChannels == nocc);
        REQUIRE(TestImage(scaledImg));
    }

}

TEST_CASE("Scaling image donut 1", "[imageScaler]"){
    Image img("test-images/image-donut.png");

    REQUIRE(img.data);

    AveragingScaler scaler;

    // grayscale image
    Image scaled = scaler.ScaleImageTo(img, 300, 300);

    // check metrics
    REQUIRE(scaled.data);
    REQUIRE(scaled.data != img.data);

    // write to file
    if(!stbi_write_png("test-images/output-donut-scaled.png", scaled.width, scaled.height, scaled.numberOfColorChannels, scaled.data, scaled.width * scaled.numberOfColorChannels)){
        std::cout << "TEST:: Failed to write image to file" << std::endl;
    }
}