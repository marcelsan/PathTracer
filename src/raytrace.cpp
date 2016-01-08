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

inline static color phongShading(const Intersection& inter, const Scene& scene, const Light* light, const vec3& N, const vec3& V, const vec3& R)
{
    Material mat = inter.m;
    vec3 l;
    color lightColor = light->emissionColor();

    if(!light->directional) {
        l = light->samplePosition() - inter.p;
    } else {
        l = light->direction();
    }

    const vec3 L = normalize(l);

    Intersection shadow;
    if (scene.raycast(inter.rayTo(L), shadow, length(l) - 0.00001f)) {
        if (shadow.o != light->object())
            return black;
    }

    float NL = dot(N, L);
    float LR = dot(L, R);

    if (NL > 0)
        return NL * mat.kd * lightColor * mat.color * light->ip;

    if (LR > 0)
        return mat.ks * float(pow(LR, mat.n)) * lightColor * light->ip;

    return black;
}

inline static color raycast(const Ray& ray, const Scene& scene, float srcIr = 1.0f, int depth = 5)
{
    Intersection inter;
    if (!scene.raycast(ray, inter))
        return scene.background();

    Material mat = inter.m;

    if (mat.emissive)
        return mat.color;

    vec3 N = inter.n;
    vec3 V = normalize(ray.d);
    vec3 R = reflect(V, N);

    color c = black;
    for (auto& light : scene.getLights())
        c += phongShading(inter, scene, light.get(), N, V, R);

    if (depth <= 0)
        return c;

    float ktot = mat.kd + mat.ks + mat.kt + mat.ka;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rRay(0, ktot);
    float r = rRay(gen);

    if ((r -= mat.ka) < 0) {
        c += mat.color;
    } else if ((r -= mat.kd) < 0) {
        std::uniform_real_distribution<float> rAngle(0, 1);
        const float r1 = rAngle(gen);
        const float r2 = rAngle(gen);

        const float phi = acos(sqrt(r1));
        const float theta = 2 * M_PI * r2;

        const float x = sin(phi) * cos(theta);
        const float y = sin(phi) * sin(theta);
        const float z = cos(phi);

        c += raycast(inter.rayTo(vec3(x,y,z)), scene, srcIr, depth - 1);
    } else if ((r -= mat.ks) < 0) {
        c += raycast(inter.rayTo(R), scene, srcIr, depth - 1);
    } else {
        float n1 = srcIr, n2 = mat.ir;

        if (fcmp(srcIr, mat.ir)) {
            n2 = 1.0f;
            N = -N;
        }

        const float n = n1 / n2;
        const float cosI = -dot(N, V);
        const float sinT2 = n * n * (1.0 - cosI * cosI);

        if(sinT2 < 1.0f || fcmp(sinT2, 1.0f)) {
            const float cosT = sqrt(1 - sinT2);
            vec3 T = V * n + (n * cosI - cosT) * N;
            c += raycast(inter.rayTo(T), scene, mat.ir, depth - 1);
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