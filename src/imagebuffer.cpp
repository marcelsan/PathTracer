#include "imagebuffer.h"

namespace PathTrace {

template<typename C>
ImageBuffer<C>::ImageBuffer(unsigned int width, unsigned int height)
	: buffer(width * height)
	, w(width)
	, h(height)
{
}

}