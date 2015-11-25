#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>

namespace PathTrace {

template<typename C>
class ImageBuffer
{
private:
	std::vector<C> buffer;
	unsigned int w;
	unsigned int h;

public:
	ImageBuffer(unsigned int width, unsigned int height);

	C& operator[](std::size_t idx) { return buffer[idx]; };
    const C& operator[](std::size_t idx) const { return buffer[idx]; };
};

}

#endif