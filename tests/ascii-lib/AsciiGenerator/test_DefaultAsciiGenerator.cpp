#include <catch2/catch_test_macros.hpp>
#include "common/Image/Image.hpp"
#include "common/Image/Scaling/AveragingImageScaler.hpp"
#include "common/Ascii/Default_AsciiGenerator.hpp"

#include <iostream>


TEST_CASE("DefaultAsciiGenerator KingFisher", "[DefaultAsciiGenerator]") {
    
    std::cout << "TEST:: Loaing kingfisher image" << std::endl;

    Image kingfisher("test-images/image-kingfisher.png");
    REQUIRE(kingfisher.data);
    REQUIRE(kingfisher.width > 0);
    REQUIRE(kingfisher.height > 0);

    // make context
    GeneratorContext context = {
        .width = 200,
        .height = 200/3,
        .useColor = false,
        .useEdgeDetection = false,
        .forceDefaultColor = true
    };
    
    std::cout << "TEST:: Generating Ascii" << std::endl;
    // get scaler
    auto scaler = std::make_shared<AveragingScaler>();

    DefaultAsciiGenerator generator(scaler);
    std::string ascii = generator.GenerateAscii(kingfisher, context);
        std::cout << "TEST:: Displaying Ascii" << std::endl;


    std::cout << ascii << std::endl;


}

TEST_CASE("DefaultAsciiGenerator Donut 1", "[DefaultAsciiGenerator]") {
    
    std::cout << "TEST:: Loaing donut image" << std::endl;

    Image donut("test-images/image-donut.png");
    REQUIRE(donut.data);
    REQUIRE(donut.width > 0);
    REQUIRE(donut.height > 0);

    // make context
    GeneratorContext context = {
        .width = 200,
        .height = 200/3,
        .useColor = false,
        .useEdgeDetection = false,
        .forceDefaultColor = true
    };
    
    std::cout << "TEST:: Generating Ascii" << std::endl;
    // get scaler
    auto scaler = std::make_shared<AveragingScaler>();

    DefaultAsciiGenerator generator(scaler);
    std::string ascii = generator.GenerateAscii(donut, context);
        std::cout << "TEST:: Displaying Ascii" << std::endl;


    std::cout << ascii << std::endl;


}

TEST_CASE("DefaultAsciiGenerator Donut 2", "[DefaultAsciiGenerator]") {
    
    std::cout << "TEST:: Loaing donut 2 image" << std::endl;

    Image donut("test-images/image-donut-2.png");
    REQUIRE(donut.data);
    REQUIRE(donut.width > 0);
    REQUIRE(donut.height > 0);

    // make context
    GeneratorContext context = {
        .width = 200,
        .height = 200/3,
        .useColor = false,
        .useEdgeDetection = false,
        .forceDefaultColor = true
    };
    
    std::cout << "TEST:: Generating Ascii" << std::endl;
    // get scaler
    auto scaler = std::make_shared<AveragingScaler>();

    DefaultAsciiGenerator generator(scaler);
    std::string ascii = generator.GenerateAscii(donut, context);
        std::cout << "TEST:: Displaying Ascii" << std::endl;


    std::cout << ascii << std::endl;


}
