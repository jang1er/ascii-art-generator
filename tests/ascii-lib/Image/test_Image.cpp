#include <catch2/catch_test_macros.hpp>
#include "common/Image/Image.hpp"

TEST_CASE("Image default values", "[image]") {
    Image img;
    REQUIRE(img.data == nullptr);
    REQUIRE(img.width == 0);
    REQUIRE(img.height == 0);
    REQUIRE(img.numberOfColorChannels == 0);
}
