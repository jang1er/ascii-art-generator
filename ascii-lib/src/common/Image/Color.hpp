#pragma once

#include <string>
#include <array>
#include <utility>
#include <tuple>
#include <cmath>

namespace ColorConverter{

    struct Color {unsigned char r, g, b; };

    // 16 standard ANSI colors (0–7 = normal, 8–15 = bright)
    constexpr auto ANSI16_COLORS = std::to_array<std::pair<Color, unsigned char>>({
        {{0, 0, 0}, 30},         // Black
        {{128, 0, 0}, 31},       // Red
        {{0, 128, 0}, 32},       // Green
        {{128, 128, 0}, 33},     // Yellow
        {{0, 0, 128}, 34},       // Blue
        {{128, 0, 128}, 35},     // Magenta
        {{0, 128, 128}, 36},     // Cyan
        {{192, 192, 192}, 37},   // White
        {{128, 128, 128}, 90},   // Bright Black
        {{255, 0, 0}, 91},       // Bright Red
        {{0, 255, 0}, 92},       // Bright Green
        {{255, 255, 0}, 93},     // Bright Yellow
        {{0, 0, 255}, 94},       // Bright Blue
        {{255, 0, 255}, 95},     // Bright Magenta
        {{0, 255, 255}, 96},     // Bright Cyan
        {{255, 255, 255}, 97}    // Bright White
    });

    /// @brief 
    /// @param a 
    /// @param b 
    /// @return 
    double colorDistance(const Color& a, const Color& b) {
        return std::sqrt(
            (a.r - b.r) * (a.r - b.r) +
            (a.g - b.g) * (a.g - b.g) +
            (a.b - b.b) * (a.b - b.b)
        );
    }

    /// @brief 
    /// @param color 
    /// @return 
    std::string convertRGBtoAnsi8(Color color){
        // do some logic here
    }

    /// @brief 
    /// @param red 
    /// @param blue 
    /// @param green 
    /// @return 
    std::string convertRGBtoAnsi8(unsigned char red, unsigned char green, unsigned char blue){
        return ColorConverter::convertRGBtoAnsi8(ColorConverter::Color{red, green, blue});
    }


    /// @brief 
    /// @param red 
    /// @param blue 
    /// @param green 
    /// @return 
    std::string convertRGBtoAnsi16(unsigned char red, unsigned char blue, unsigned char green){
        
    }

    /// @brief 
    /// @param red 
    /// @param blue 
    /// @param green 
    /// @return 
    std::string convertRGBtoAnsi8bit(unsigned char red, unsigned char blue, unsigned char green){
        
    }

    /// @brief 
    /// @param red 
    /// @param blue 
    /// @param green 
    /// @return 
    std::string convertRGBtoAnsi24bit(unsigned char red, unsigned char blue, unsigned char green){
        
    }

    /// @brief 
    /// @param red 
    /// @param blue 
    /// @param green 
    /// @return 
    inline double convertRGBtoHSV(double red, double blue, double green){

    }


};