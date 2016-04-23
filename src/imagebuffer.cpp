#include "imagebuffer.h"
#include "util.h"

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
    tonemapping_multiplier = float(ImageBuffer::CHANNEL_MAX) / tm;
}

static std::ostream& operator<<(std::ostream& stream, const color& color)
{
    stream << toInt(color.r) << " ";
    stream << toInt(color.g) << " ";
    stream << toInt(color.b) << " ";
    return stream;
}

color limit(glm::vec3 c)
{
    float r = std::min(c[0], float(ImageBuffer::CHANNEL_MAX));
    float g = std::min(c[1], float(ImageBuffer::CHANNEL_MAX));
    float b = std::min(c[2], float(ImageBuffer::CHANNEL_MAX));

    return {r, g, b};
}

std::ostream& operator<<(std::ostream& stream, const ImageBuffer &image)
{
    stream << "P3" << std::endl; // P3 is the magic number
    stream << image.w << " "<< image.h << std::endl;
    stream <<  ImageBuffer::CHANNEL_MAX << std::endl; // XXX: get this automaticaly
    for (const auto& color : image.buffer) {
        stream << color << " ";
    }
    return stream;
}

}