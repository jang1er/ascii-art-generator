#include "common/Image/AveragingImageScaler.hpp"
#include "Image.hpp"

Image AveragingScaler::ScaleImageTo(const Image &image, int newWidth, int newHeight){
    // allocate big enough memory
    unsigned char *scaledData = new unsigned char[newWidth * newHeight * image.numberOfColorChannels];

    Image scaledImage;
    scaledImage.width = newWidth;
    scaledImage.height = newHeight;
    scaledImage.numberOfColorChannels = image.numberOfColorChannels;
    scaledImage.data = scaledData;

    // get ratio of old to new pixels
    int dx = image.width / newWidth;
    int dy = image.height / newHeight;

    auto getPixel = [&](int x, int y){
        return image.data + (x + y * image.width) * image.numberOfColorChannels;
    };

    for(int y = 0; y < newHeight; ++y){
        for(int x = 0; x < newWidth; ++x){
            int sum[4] = {0};

            // average over old pixels
            for(int j = 0; j < dy; ++j){
                for(int i = 0; i < dx; ++i){
                    const unsigned char *p = getPixel(x * dx + i,y * dy + j);
                    for(int c = 0; c < image.numberOfColorChannels; ++c){
                        sum[c] += p[c];
                    }
                }

                int samples = dx * dy;
                for(int c = 0; c < image.numberOfColorChannels; ++c){
                    scaledData[(y * newWidth + x) * image.numberOfColorChannels + c] = static_cast<unsigned char>(sum[c] / samples);
                }
            }
        }
    }


    return scaledImage;
};

Image AveragingScaler::ScaleImageTo(const Image &image, float scale){
    int newWidth = static_cast<int>(static_cast<float>(image.width) * scale);
    int newHeight = static_cast<int>(static_cast<float>(image.height) * scale);
    return ScaleImageTo(image, newWidth, newHeight);
}