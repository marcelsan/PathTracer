#ifndef __SCENE_H__
#define __SCENE_H__

#include "Vec.h"
#include "Object.h"
#include "LightScheme.h"
#include "Light.h"

#include <vector>

class Scene
{
private:
	Vec3f gravity;

	std::vector<unsigned int> objectsIDs;
	std::vector<Plane> planes;
	std::vector<Cube> cubes;
	std::vector<Mesh> meshes;
	LightScheme lights;

public:

	Scene()
	{
	}

	const Vec3f getGravity()
	{
		return gravity;
	}

	void setGravity(Vec3f newGravity)
	{
		gravity = newGravity;
	}

	void add(Cube& cube)
	{
		cubes.push_back(cube);
		objectsIDs.push_back(cube.getID());
	}

	void add(Plane& plane)
	{
		planes.push_back(plane);
		objectsIDs.push_back(plane.getID());
	}

	void add(Mesh& mesh)
	{
		meshes.push_back(mesh);
		objectsIDs.push_back(mesh.getID());
	}

	void add(LightScheme& scheme)
	{
		lights = scheme;
	}
		
	void add(Light& light)
	{
		lights.add(light);
	}

	const std::vector<Cube>& getCubes() const
	{
		return cubes;
	}

	const std::vector<Plane>& getPlanes() const
	{
		return planes;
	}

	std::vector<Plane>& grabPlanes()
	{
		return planes;
	}

	const std::vector<Mesh>& getMeshes() const
	{
		return meshes;
	}

	std::vector<Mesh>& grabMeshes()
	{
		return meshes;
	}

	const LightScheme& getLightScheme() const
	{
		return lights;
	}
};


#endif