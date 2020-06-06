#include <iostream>

#include "stb_image.h"

#include "stb_image_write.h"

#include "FloatImage.hpp"

int FloatImage::JPEG_QUALITY = 90;

FloatImage::FloatImage(int width_, int height_, int components_) : width(width_), height(height_), components(components_)
{
    buffer.reserve(width * height * components);
}

FloatImage FloatImage::fromFile(std::string const &filename)
{
    int width, height, n;
    int components = 4;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &n, components);
    if (data == NULL)
    {
        std::cout << "Couldn't load file!" << std::endl;
        exit(1);
    }

    FloatImage temp(width, height, components);

    for (int i = 0; i < width * height * components; i++)
    {
        temp.buffer.push_back(data[i]);
    }

    stbi_image_free(data);

    return temp;
}

bool FloatImage::toFile(std::string const &filename) const
{
    auto lastpd = filename.rfind('.');
    if (lastpd == std::string::npos)
        return false;
    auto const &filetype = filename.substr(lastpd, std::string::npos);

    if (filetype == ".hdr")
    {
        stbi_write_hdr(filename.c_str(), width, height, components, &(buffer[0]));
    }
    else
    {
        return false;
    }

    return true;
}

Vector4f FloatImage::getPixel(int x, int y) const
{
    //y * width * + x doesnt error???
    int baseIdx = components * (y * width + x);
    return {buffer[baseIdx], buffer[baseIdx+1], buffer[baseIdx+2], buffer[baseIdx+3]};
}
void FloatImage::setPixel(int x, int y, Vector4f const & c)
{
    int baseIdx = components * (y * width + x);
    buffer[baseIdx] = c[0];
    buffer[baseIdx+1] = c[1];
    buffer[baseIdx+2] = c[2];
    buffer[baseIdx+3] = c[3];
}