#pragma once

#include <vector>
#include <string>
#include "Utils.hpp"

class Image
{
    std::vector<u_char> buffer;
    int width, height, components;
    static int JPEG_QUALITY;

public:
    Image(int width_, int height_, int components_);
    static Image fromFile(std::string const & filename);
    bool toFile(std::string const & filename, bool flip = false) const;

    Color getPixel(int x, int y) const;
    void setPixel(int x, int y, Color c);
    inline int getWidth() {
        return width;
    };
    inline int getHeight() {
        return height;
    };
    inline int getComponents() {
        return components;
    };
    inline float getAspectRatio() {
        return (float)getWidth() / getHeight();
    }
};