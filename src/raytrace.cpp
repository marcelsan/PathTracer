#include "raytrace.h"
#include <glm/glm.hpp>
#include <cmath>
#include <random>
#include "ray.h"

using namespace glm;

namespace PathTrace {

inline static bool fcmp(float a, float b, float epsilon = 0.000001f) 
{
    return (fabs(a - b) < epsilon);
}

inline static color raycast(const Ray& ray, const Scene& scene, float srcIr = 1.0f, int depth = 5)
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

    vec3 L;
    vec3 N = inter.n;
    vec3 V = normalize(ray.d);
    vec3 R = reflect(V, N);

    for (auto& light : scene.getLights()) {
        vec3 l;
        color lightColor = light->emissionColor();

        if(!light->directional) {
            l = light->samplePosition() - inter.p;
        } else {
            l = light->direction();
        }

        L = normalize(l);

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
    }

    if (depth > 0) {
        if (mat.ks > 0)
            c += mat.ks * raycast(inter.rayTo(R), scene, srcIr, depth - 1);
    }

    if (mat.ir > 0) {
        float n1 = srcIr, n2 = mat.ir;

        if(fcmp(srcIr, mat.ir)) {
            n2 = 1.0f;
            N = -N;
        }

        const float n = n1 / n2;
        const float cosI = -dot(N, V);
        const float sinT2 = n * n * (1.0 - cosI * cosI);
        
        if(sinT2 < 1.0f || fcmp(sinT2, 1.0f)) {
            const float cosT = sqrt(1 - sinT2);
            vec3 T = V * n + (n * cosI - cosT) * N;
            c += mat.kt * raycast(inter.rayTo(T), scene, mat.ir, depth - 1);
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
            buffer(i, j) = raycast(ray, scene);
        }
    }
}

void pathtrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    double w = buffer.width();
    double h = buffer.height();
    for (unsigned i = 0; i < h; i++) {
        for (unsigned j = 0; j < w; j++) {
            std::cerr << i << j << std::endl;
            color c = black;
            std::uniform_real_distribution<float> vDis(i / h, (i + 1) / h);
            std::uniform_real_distribution<float> hDis(j / w, (j + 1) / w);
            for (unsigned n = 0; n < cam.nPaths(); n++) {
                Ray ray = cam.ray(vDis(gen), hDis(gen));
                c += raycast(ray, scene);
            }
            buffer(i, j) = c / float(cam.nPaths());
        }
    }
}

}