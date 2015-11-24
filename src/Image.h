#ifndef __IMAGE_H__
#define __IMAGE_H__

template <typename PixelType = unsigned char>
class Image
{
public:
	Image()
	{
		width = 0;
		height = 0;
		channels = 0;
		data = NULL;
	}

	Image(
		unsigned int width,
		unsigned int height,
		unsigned int channels = 1,
		unsigned char* data = NULL)
	{
		init(width, height, channels, data);
	}

	~Image()
	{
		if (data) 
		{
			delete[] data;
			data = NULL;
		}
	}

	// assignement operator works as a copy function
	void operator=(const Image &image)
	{
		init(image.width, image.height, image.channels, image.data);
	}

	void init(
		unsigned int width,
		unsigned int height,
		unsigned int channels = 1,
		unsigned char* data = NULL)
	{
		// check for equal sized image
		bool allocate = true;

		if (this->width == width &&
			this->height == height &&
			this->channels == channels)
			allocate = false;

		this->width = width;
		this->height = height;
		this->channels = channels;

		this->npixels = width * height * channels;
		this->size = npixels * sizeof(PixelType);

		if (allocate)
			this->data = new unsigned char[this->size];

		if (data != NULL)
		{
			memcpy(this->data, data, this->size);
		}
		else
		{
			for (int i = 0; i < this->size; ++i)
			{
				this->data[i] = 100;
			}
		}
	}

	inline PixelType getPixel(unsigned int id1D) const
	{
		PixelType result;

		if (id1D < 0 || id1D >= npixels)
		{
			std::cerr 
				<< "ERROR: image invalid access, input index is " 
				<< i 
				<< " and the number of pixels is " 
				<< npixels 
				<< std::endl
				<< "       returning default pixel"
				<< std::endl;
		}
		else
		{
			PixelType* pointer = (PixelType*)data;
			result = pointer[id1D];
		}

		return result;
	}

	inline PixelType getPixel(unsigned int x, unsigned int y) const
	{
		return getPixel(y * width + x);
	}

	inline void setPixel(unsigned int id1D, const PixelType& pixel)
	{
		PixelType* pointer = (PixelType*)data;
		pointer[id1D] = pixel;
	}

	inline void setPixel(unsigned int x, unsigned int y, const PixelType& pixel)
	{
		setPixel(y * width + x, pixel);
	}

	const unsigned char* getData() const
	{
		return data;
	}

	unsigned char* grabData()
	{
		return data;
	}

	void copyData(const unsigned char* data)
	{
		if(size == this->size)
		{
			memcpy(this->data, data, this->size);
		} else {
			std::cerr << "ERROR: new data size is different from Image data size." << std::endl;
		}
	}

	inline void shareData(unsigned char* data)
	{
		this->data = data;
	}

	inline unsigned int getWidth() const
	{
		return width;
	}

	inline unsigned int getHeight() const
	{
		return height;
	}

	inline unsigned int getChannels() const
	{
		return channels;
	}

	inline unsigned int getNPixels() const
	{
		return npixels;
	}

private:
	unsigned int width;
	unsigned int height;
	unsigned int channels;
	unsigned int npixels;
	unsigned int size;
	unsigned char* data;
};

#endif