#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "Vec.h"

class ColorMaterial
{
private:
	Color color;
	int reflectionExponent;
	double Ka;
	double Kd;
	double Ks;

public:
	ColorMaterial()
	{
	}

	ColorMaterial(Color color, 
		double Ka, 
		double Kd, 
		double Ks, 
		int reflectionExponent) : color(color), Ka(Ka), Kd(Kd), Ks(Ks), reflectionExponent(reflectionExponent) {}

	const Color getColor() const
	{
		return this->color;
	}

	double getKa() const
	{
		return Ka;
	}

	double getKd() const
	{
		return Kd;
	}

	double getKs() const
	{
		return Ks;
	}

	double getReflectionExponent() const
	{
		return reflectionExponent;
	}
};

class Object : public ColorMaterial
{

public:
	Object(
		const Vec3f& position = Vec3f(),
		const Vec3f& orientation = Vec3f(0, 1, 0)) : ColorMaterial(Color(1.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f))
	{
	
	}

	Object(
		Color _diffuse,
		Color _specular,
		Color _ambiental,
		const Vec3f& position = Vec3f(),
		const Vec3f& orientation = Vec3f(0, 1, 0)) : ColorMaterial(_diffuse, _specular, _ambiental)
	{
	}
};

class Box : public Object
{
protected:
	float depth;
	float height;
	float width;

public:
	Box(const Vec3f& position = Vec3f()) : Object()
	{
		this->width = 1;
		this->height = 1;
		this->depth = 1;
	}

	Box(Color _diffuse,
		Color _specular,
		Color _ambiental,
		float width,
		float height,
		float depth,
		const Vec3f& position = Vec3f()) : Object(_diffuse, _specular, _ambiental, position)
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
	}
	
	Box(float width,
		float height,
		float depth,
		const Vec3f& position = Vec3f()) : Object()
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
	}
};

class Cube : public Box
{
public:
	Cube(const Vec3f& position = Vec3f()) : Box(position)
	{
	}

	Cube(Color _diffuse,
		Color _specular,
		Color _ambiental, 
		float size, 
		Vec3f& position = Vec3f()) : Box(_diffuse, _specular, _ambiental, size, size, size, position)
	{
	}
	
	Cube(float size, const Vec3f& position = Vec3f()) : Box(size, size, size, position)
	{
	}

	const float getSize() const
	{
		return width;
	}

private:
	physx::PxShape* shape;
};

class Plane : public Object
{
public:
	bool grid;
	unsigned int size;

	const Vec3f getNormal() const
	{
		return this->getOrientation();
	}

	Plane(const Color color,
		const Vec3f& position = Vec3f(),
		const Vec3f& normal = Vec3f(0, 1, 0)) : Object(color, position, normal)
	{
		this->size = 60;
		this->grid = true;
	};

	Plane(unsigned int size,
		const Color color,
		const Vec3f& position = Vec3f(),
		const Vec3f& normal = Vec3f(0, 1, 0)) : Object(color, position, normal)
	{
		this->size = size;
		this->grid = true;
	};
};

class Mesh : public Object
{
private:
	float scale;

	void resetObject()
	{
		this->vertices.clear();
		this->indices.clear();
		this->texturaIndices.clear();
		this->normalIndices.clear();
		this->normals.clear();
		this->texture.clear();
	}

public:
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texture; 
	std::vector<unsigned int> indices;
	std::vector<unsigned int> texturaIndices;
	std::vector<unsigned int> normalIndices;

	Mesh(const Vec3f& position = Vec3f(),
		const Vec3f& orientation = Vec3f(0, 1, 0),
		const float scale = 1) :
	Object(position, orientation)
	{
		this->resetObject();
		this->scale = scale;
	};

	void addVertex(Vec3f vertex)
	{
		vertices.push_back(vertex.data[0] * scale);
		vertices.push_back(vertex.data[1] * scale);
		vertices.push_back(vertex.data[2] * scale);
	}

	int addNormals(Vec3f normal)
	{
		this->normals.push_back(normal.data[0]);
		this->normals.push_back(normal.data[1]);
		this->normals.push_back(normal.data[2]);

		return (this->normals.size()/3 - 1);
	}

	void addTexture(Vec3f texture)
	{
		this->texture.push_back(texture.data[0]);
		this->texture.push_back(texture.data[1]);
		this->texture.push_back(texture.data[2]);
	}

	void addTriangleIndices(Vec3i indices)
	{
		this->indices.push_back(indices.data[0]);
		this->indices.push_back(indices.data[1]);
		this->indices.push_back(indices.data[2]);
	}

	void clearVertices()
	{
		vertices.clear();
	}

	void clearIndices()
	{
		indices.clear();
	}

	const std::vector<float>& getVertices() const
	{
		return vertices;
	}

	std::vector<float>& grabVertices()
	{
		return vertices;
	}

	const std::vector<unsigned int> getIndices() const
	{
		return indices;
	}

	std::vector<unsigned int> grabIndices()
	{
		return indices;
	}

	const std::vector<float>& getNormals() const 
	{
		return normals;
	}

	const std::vector <unsigned int> getNormalsIndices() const
	{
		return normalIndices;
	}
	
	int getNormalsSize() const
	{
		return (int)this->normals.size();
	}

	int getIndicesSize() const
	{
		return (int)this->indices.size();
	}
};

#endif