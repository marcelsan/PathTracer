#include "raytrace.h"
#include <glm/glm.hpp>
#include "ray.h"

namespace PathTrace {

inline static color raycast(const Ray& ray, const Scene& scene, int depth = 0)
{
    Intersection inter;
    if (!scene.raycast(ray, inter))
        return scene.background();

    color c = black;
    for (auto& light : scene.getLights()) {
        c += light->sampleColor(inter);
    }

    return c;
}

void raytrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam)
{
    double w = buffer.width();
    double h = buffer.height();
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            Ray ray = cam.ray(j / (w - 1), i / (h - 1));
            buffer(i, j) = raycast(ray, scene);
        }
    }
}

}