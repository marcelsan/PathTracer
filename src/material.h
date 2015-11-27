#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm/glm.hpp>

using namespace glm;

namespace PathTrace {
class Material {

public:
	Material();
	Material(vec3 color, double ka, double kd, double ks, double kt, int n) : color(color), ka(ka), kd(kd), ks(ks), kt(kt), n(n);

private:
	vec3 color;
	double ka, kd, ks, kt;
	int n;

};
}

#endif