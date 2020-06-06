#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.hpp"

int Image::JPEG_QUALITY = 90;

Image::Image(int width_, int height_, int components_) : width(width_), height(height_), components(components_)
{
    buffer.reserve(width * height * components);
}

Image Image::fromFile(std::string const &filename)
{
    int width, height, n;
    int components = 4;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &n, components);
    if (data == NULL)
    {
        std::cout << "Couldn't load file!" << std::endl;
        exit(1);
    }

    Image temp(width, height, components);

    for (int i = 0; i < width * height * components; i++)
    {
        temp.buffer.push_back(data[i]);
    }

    stbi_image_free(data);

    return temp;
}

bool Image::toFile(std::string const &filename, bool flip) const
{
    stbi_flip_vertically_on_write(flip);
    auto lastpd = filename.rfind('.');
    if (lastpd == std::string::npos)
        return false;
    auto const &filetype = filename.substr(lastpd, std::string::npos);

    if (filetype == ".png")
    {
        stbi_write_png(filename.c_str(), width, height, components, &(buffer[0]), width * components);
    }
    else if (filetype == ".bmp")
    {
        stbi_write_bmp(filename.c_str(), width, height, components, &(buffer[0]));
    }
    else if (filetype == ".tga")
    {
        stbi_write_tga(filename.c_str(), width, height, components, &(buffer[0]));
    }
    else if (filetype == ".jpg")
    {
        stbi_write_jpg(filename.c_str(), width, height, components, &(buffer[0]), JPEG_QUALITY);
    }
    else
    {
        return false;
    }

    return true;
}

Color Image::getPixel(int x, int y) const
{
    //y * width * + x doesnt error???
    int baseIdx = components * (y * width + x);
    return {buffer[baseIdx], buffer[baseIdx+1], buffer[baseIdx+2], buffer[baseIdx+3]};
}
void Image::setPixel(int x, int y, Color c)
{
    int baseIdx = components * (y * width + x);
    buffer[baseIdx] = c.r;
    buffer[baseIdx+1] = c.g;
    buffer[baseIdx+2] = c.b;
    buffer[baseIdx+3] = c.a;
}