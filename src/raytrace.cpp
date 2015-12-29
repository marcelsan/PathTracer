#include "raytrace.h"
#include <glm/glm.hpp>
#include <cmath>
#include "ray.h"

using namespace glm;

namespace PathTrace {

inline static color raycast(const Ray& ray, const Scene& scene, int depth = 0)
{
    Intersection inter;
    if (!scene.raycast(ray, inter))
        return scene.background();

    Material mat = inter.m;
    color c = mat.ka * mat.color;

    if (mat.emissive) {
        c += mat.color;
        return c;
    }

    vec3 N = normalize(inter.n);
    vec3 V = normalize(ray.d);
    vec3 R = reflect(V, N);

    for (auto& light : scene.getLights()) {
        vec3 lpos = light->samplePosition();
        color lightColor = light->emissionColor();
        vec3 l = lpos - inter.p;
        vec3 L = normalize(l);
    
        Intersection shadow;
        bool shadowed = true;
        if (scene.raycast(inter.rayTo(L), shadow, length(l) - 0.00001f)) {
            if (shadow.o != light->object())
                shadowed = true; //distance(inter.p, shadow.p) < length(l);
        } else {
            shadowed = false;
        }

        if (!shadowed) {
            float NL = dot(N, L);
            if (NL > 0)
                c += NL * mat.kd * lightColor * mat.color;
        }

        if (depth > 0) {
            if (mat.ks > 0)
                c += mat.ks * raycast(inter.rayTo(R), scene, depth - 1);

            // transmitted portion 
            if (mat.ir > 0) {
                float cosI = dot(N, L);
                float sinT2 = (1.0 - pow(cosI, 2))/pow(mat.ir, 2);
                
                if(sinT2 < 1.0f || fabs(sinT2 - 1.0f) < 0.0000001) {
                    float cosT = sqrt(1 - sinT2);
                    vec3 T = -L/mat.ir + (cosI/mat.ir - cosT)*N;
                    c += mat.kt * raycast(inter.rayTo(T), scene, depth - 1);
                }
            }

        } else if (!shadowed) {
            float LR = dot(L, R);
            if (LR > 0)
                c += mat.ks * float(pow(LR, mat.n)) * lightColor;
        }
    }

    return c;
}

void raytrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam)
{
    double w = buffer.width();
    double h = buffer.height();
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            Ray ray = cam.ray(i / (h - 1), j / (w - 1));
            buffer(i, j) = raycast(ray, scene, 5);
        }
    }
}

}