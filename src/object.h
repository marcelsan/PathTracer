#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "ray.h"
#include "material.h"
#include "intersection.h"

using namespace glm;

namespace PathTrace {

class Object {
public:
	Object();
	Object(vec3 color, double ka, double kd, double ks, double kt, int n) 
	{
		mat = Material(color, ka, kd, ks, kt, n);
	};
	
	virtual double intersect(const Ray& ray) = 0;

private:
	Material mat;
};

class Quadric : public Object {
public:
	Quadric();
	Quadric(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j,
			vec3 color, double ka, double kd, double ks, double kt, int n) : Object(color, ka, kd, ks, kt, n)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
		this->g = g;
		this->h = h;
		this->i = i;
		this->j = j;
	}

	double intersect(const Ray& ray) {

	    double  acoef, bcoef, ccoef; // Intersection coefficents
	    double  dx, dy, dz; // Direction - origin coordinates
	    double  disc; // Distance to intersection
	    double  root; // Root of distance to intersection
	    double  t; // Distance along ray to intersection
	    double  x0, y0, z0; // Origin coordinates

	    dx = ray.d[0] - ray.o[0];
	    dy = ray.d[1] - ray.o[1];
	    dz = ray.d[2] - ray.o[2];

	    x0 = ray.o[0];
	    y0 = ray.o[1];
	    z0 = ray.o[2];

	 	// Ax2 + By2 + Cz2 + Dxy+ Exz + Fyz + Gx + Hy + Iz + J = 0

	    acoef = a * dx * dx + b * dy * dy + c * dz * dz + d * dx * dy + e * dx * dz + f * dy * dz;

	    bcoef = 2 * a * x0 * dx + 2 * b * y0 * dy + 2 * c * z0 * dz + d * (x0 * dy + y0 * dx) + 
	    		e * (x0 * dz + z0 * dx) + f * (y0 * dz + dy * z0) + g * dx + h * dy + i * dz;

	    ccoef = a * x0 * x0 + b * y0 * y0 + c * z0 * z0 + d * x0 * y0 + e * x0 * z0 + f * y0 * z0 + g * x0 +
	    		h * y0 + i * z0 + j;

	    if ( 1.0 + acoef == 1.0 ) {
	        if ( 1.0 + bcoef == 1.0 ) {
	            return -1.0;
	        }

	      t = ( -ccoef ) / ( bcoef );

	    } else {
	        disc = bcoef * bcoef - 4 * acoef * ccoef;
	      	if ( 1.0 + disc < 1.0 ) {
	         	return -1.0;
	      	}

		    root = sqrt( disc );
		    t = ( -bcoef - root ) / ( acoef + acoef );
		    if ( t < 0.0 ) {
		        t = ( -bcoef + root ) / ( acoef + acoef );
		    }
	    }

	    if (t < 0.001) {
	    	return -1.0;
	    }

	   return t;
	}

	const vec3 getNormal(vec3 point) const {
		
		const double x = point[0];
		const double y = point[1];
		const double z = point[2];

		float gradx = 2 * a * x + d * y + e * z + g;
		float grady = 2 * b * y + d * x + f * z + h;
		float gradz = 2 * c * z + e * x + f * y + i;

		return vec3(gradx, grady, gradz);
	}

private:
	double  a, b, c, d, e; // Coefficents of equation of..
   	double  f, g, h, i, j; // ... quadric surface
};

}

#endif