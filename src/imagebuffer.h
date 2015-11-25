#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>

namespace PathTrace {

template<typename C>
class ImageBuffer
{
private:
	std::vector<C> buffer;
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
	C& operator[](std::size_t idx) { return buffer[idx]; };
    const C& operator[](std::size_t idx) const { return buffer[idx]; };
};

}

#endif