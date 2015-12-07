#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>
#include <iostream>
#include "color.h"

namespace PathTrace {

class ImageBuffer
{
private:
    std::vector<color> buffer;
    std::size_t w;
    std::size_t h;

public:
    ImageBuffer(std::size_t width, std::size_t height)
        : buffer(width * height)
        , w(width)
        , h(height)
    {
    }

    std::size_t width() const { return w; }
    std::size_t height() const { return h; }
    color& operator()(std::size_t i, std::size_t j) { return buffer[i * w + j]; };
    const color& operator()(std::size_t i, std::size_t j) const { return buffer[i * w + j]; };
    void clear(const color& c);

    friend std::ostream& operator<<(std::ostream& stream, const ImageBuffer &);
};

}

#endif