#include "imagebuffer.h"

#include <cmath>

namespace PathTrace {

ImageBuffer::ImageBuffer(std::size_t width, std::size_t height)
    : buffer(width * height)
    , w(width)
    , h(height)
{
}

void ImageBuffer::setSize(std::size_t width, std::size_t height)
{
    w = width;
    h = height;
    buffer.resize(w * h);
}

void ImageBuffer::clear(const color& c)
{
    for (auto& bc : buffer)
        bc = c;
}

void ImageBuffer::setTonemapping(float tm)
{
    tonemapping_multiplier = 255.0f / tm;
}

static std::ostream& operator<<(std::ostream& stream, const color& color)
{
    stream << int(round(color.r)) << " ";
    stream << int(round(color.g)) << " ";
    stream << int(round(color.b)) << " ";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const ImageBuffer &image)
{
    stream << "P3" << std::endl; // P3 is the magic number
    stream << image.w << " "<< image.h << std::endl;
    stream << 255 << std::endl; // XXX: get this automaticaly
    for (const auto& color : image.buffer) {
        stream << color * image.tonemapping_multiplier << " ";
    }
    return stream;
}

}