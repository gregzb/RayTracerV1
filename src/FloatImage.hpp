#pragma once

#include <vector>
#include <string>

#include <Eigen/Core>

#include "Utils.hpp"

using Eigen::Vector4f;

class FloatImage
{
    std::vector<float> buffer;
    int width, height, components;
    static int JPEG_QUALITY;

public:
    FloatImage(int width_, int height_, int components_);
    static FloatImage fromFile(std::string const & filename);
    bool toFile(std::string const & filename) const;

    Vector4f getPixel(int x, int y) const;
    void setPixel(int x, int y, Vector4f const & c);
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