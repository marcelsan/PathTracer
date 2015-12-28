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

    color c = black;
    for (auto& light : scene.getLights()) {
        Material mat = inter.m;
        if (mat.emissive) {
            c += mat.color;
            continue;
        }

        color lightColor = light->emissionColor();
        vec3 lpos = light->samplePosition();
        vec3 L = normalize(lpos - inter.p);
        vec3 N = normalize(inter.n);
        vec3 V = normalize(ray.d);
        vec3 R = reflect(V, N);

        c += mat.ka * mat.color;

        float NL = dot(N, L);
        if (NL > 0)
            c += NL * mat.kd * lightColor * mat.color;

        if (depth > 0) {
            if (mat.ks > 0)
                c += mat.ks * raycast(inter.rayTo(R), scene, depth - 1);
        } else {
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