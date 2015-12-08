#include "raytrace.h"
#include <glm/glm.hpp>
#include "ray.h"

namespace PathTrace {

void raytrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam)
{
    double w = buffer.width();
    double h = buffer.height();
    buffer.clear(scene.background());
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            Ray ray = cam.ray(j / (w - 1), i / (h - 1));
            Intersection inter;
            if (scene.raycast(ray, inter)) {
                // XXX
                buffer(i, j) = normalize(vec3(1, 1, 1) + inter.n);
            }
        }
    }
}

}