#ifndef __VEC_H__
#define __VEC_H__

template <typename T, int N>
class Vec
{
public:
	T data[N];

	Vec() 
	{
		for (unsigned int i = 0; i < N; ++i) data[i] = 0;
	}

	float dot(const Vec<T, N>& vec)
	{
		T result = 0;

		for (unsigned int i = 0; i < N; ++i)
		{
			result += data[i] * vec.data[i];
		}

		return result;
	}

	float norm()
	{
		return sqrt(this->dot(*this));
	}

	void normalize()
	{
		float norm = this->norm();
		
		for (unsigned int i = 0; i < N; ++i) data[i] /= norm;
	}

	Vec normalized() const
	{
		Vec result = *this;
		result.normalize();
		return result;
	}

	float cosine(const Vec& vec)
	{
		Vec v1 = this->normalized();
		Vec v2 = vec.normalized();
		return v1.dot(v2);
	}

	bool aligned(const Vec& vec)
	{
		float cos = this->cosine(vec);

		bool result = false;
		if (abs(cos) > 0.98 && abs(cos) < 1.2)
			result = true;
		
		return result;
	}
};

template <typename T>
class Vec3 : public Vec < T, 3 >
{
public:	
	Vec3() : Vec() {}

	Vec3(T x, T y, T z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	Vec3 normalized() const
	{
		Vec3 result = *this;
		result.normalize();
		return result;
	}

	Vec3 cross(const Vec3& vec) const
	{
		return  Vec3(
			data[1] * vec.data[2] - data[2] * vec.data[1],
			data[2] * vec.data[0] - data[0] * vec.data[2],
			data[0] * vec.data[1] - data[1] * vec.data[0]);
	}

	Vec3 operator-(const Vec3& vec) const
	{
		return Vec3(
				data[0]-vec.data[0], 
				data[1]-vec.data[1], 
				data[2]-vec.data[2]);
	}
	void operator=(const Vec3& vec)
	{
		data[0] = vec.data[0];
		data[1] = vec.data[1];
		data[2] = vec.data[2];
	}
};

template <typename T>
class Vec4 : public Vec < T, 4 >
{
public:
	Vec4() : Vec() {}

	Vec4(T x, T y, T z, T w)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}
};

typedef Vec3 <float> Vec3f;
typedef Vec3 <int> Vec3i;

typedef Vec3f Color;

typedef Vec4 <float> Vec4f;
typedef Vec4 <int> Vec4i;

typedef Vec <float, 2> Vec2f;
typedef Vec <int, 2> Vec2i;

#endif