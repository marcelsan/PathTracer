#include "raytrace.h"
#include <glm/glm.hpp>
#include <cmath>
#include <random>
#include "ray.h"
#include "util.h"

using namespace glm;

namespace PathTrace {

inline static color phongShading(const Material& mat, const Light& light, const vec3& L, const vec3& N, const vec3& V, const vec3& R)
{
    auto lightColor = light.emissionColor();
    color c = black;
    float NL = dot(N, L);
    float LR = dot(L, R);

    c += std::max(NL, 0.0f) * mat.kd * lightColor * mat.color * light.ip;
    c += mat.ks * float(pow(std::max(LR, 0.0f), mat.n)) * lightColor * light.ip;

    return c;
}

inline static color raytracing(const Ray& ray, const Scene& scene, float srcIr = 1.0f, int depth = 5)
{
    Intersection inter;
    if (!scene.raycast(ray, inter))
        return scene.background();

    Material mat = inter.m;
    color c = mat.ka * mat.color;

    if (mat.emissive)
        return mat.color;

    vec3 L;
    vec3 N = inter.n;
    vec3 V = normalize(ray.d);
    vec3 R = reflect(V, N);

    if (depth <= 0)
        scene.background();

    for (auto& light : scene.getLights()) {
        vec3 l;
        Intersection shadow;
        bool shadowed = false;

        if(!light->directional) {
            l = light->samplePosition() - inter.p;
        } else {
            l = light->direction();
        }

        L = normalize(l);

        if (scene.raycast(inter.rayTo(L), shadow, length(l) - 0.00001f))
            if (shadow.o != light->object())
                shadowed = true;

        if (!shadowed)
            c += phongShading(mat, *light, L, N, V, R);
    }

    float F = 1.0f;
    color ct;
    color cr = mat.ks * raytracing(inter.rayTo(R), scene, srcIr, depth - 1); 

    if (mat.ir > 0) {
        float n1 = srcIr, n2 = mat.ir;
        if(fcmp(srcIr, mat.ir))
            n2 = 1.0f;

        const float F0 = pow((n2 - n1)/(n2 + n1), 2);
        F = F0 + (1 - F0) * (1 - dot(N, R));

        const float n = n1 / n2;
        const float cosI = -dot(N, V);
        const float sinT2 = n * n * (1.0 - pow(cosI, 2));
        
        if(sinT2 < 1.0f || fcmp(sinT2, 1.0f)) {
            const float cosT = sqrt(1 - sinT2);
            vec3 T = V * n + (n * cosI - cosT) * N;
            ct = mat.kt * raytracing(inter.rayTo(T), scene, mat.ir, depth - 1);
        }
    }

    c += F * cr + (1 - F) * ct;

    return c;
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

    if (depth <= 0)
        scene.background();

    color c = black;
    for (auto& light : scene.getLights()) {
        vec3 l;
        Intersection shadow;
        bool shadowed = false;

        if(!light->directional)
            l = light->samplePosition() - inter.p;
        else
            l = light->direction(); 

        const vec3 L = normalize(l);

        if (scene.raycast(inter.rayTo(L), shadow, length(l) - 0.00001f)) {
            if (shadow.o != light->object())
                shadowed = true;
        }

        if (!shadowed)
            c += phongShading(mat, *light, L, N, V, R);
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rRay(0, mat.ktot());
    float r = rRay(gen);

    if ((r -= mat.kd) < 0) {
        std::uniform_real_distribution<float> rAngle(0, 1);
        float  r1= 2 * M_PI * rAngle(gen); 
        float  r2 = rAngle(gen);
        float  r2s = sqrt(r2); 

        vec3 w = N;
        vec3 u = normalize(cross(fabs(w.x) > 0.1 ? vec3(0,1,0):vec3(1,0,0), w));
        vec3 v = cross(w, u); 
        vec3 d = normalize(cos(r1)*r2s*u + sin(r1)*r2s*v + sqrt(1-r2)*w);

        c += mat.color * mat.kd * raycast(inter.rayTo(d), scene, srcIr, depth - 1);
    } else if ((r -= mat.ks) < 0) {
        c += mat.color * mat.ks * raycast(inter.rayTo(R), scene, srcIr, depth - 1);
    } else {
        float n1 = srcIr, n2 = mat.ir;

        if (fcmp(srcIr, mat.ir)) {
            n2 = 1.0f;
            N = -N;
        }

        const float n = n1 / n2;
        const float cosI = -dot(N, V);
        const float sinT2 = n * n * (1.0 - cosI * cosI);

        if (sinT2 < 1.0f || fcmp(sinT2, 1.0f)) {
            const float cosT = sqrt(1 - sinT2);
            vec3 T = V * n + (n * cosI - cosT) * N;
            c += mat.color * mat.kt * raycast(inter.rayTo(T), scene, mat.ir, depth - 1);
        }
    }

    return c;
}

void raytrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    double w = buffer.width();
    double h = buffer.height();
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            color c = black;
            std::uniform_real_distribution<float> vDis(i / h, (i + 1) / h);
            std::uniform_real_distribution<float> hDis(j / w, (j + 1) / w);
            for (unsigned n = 0; n < cam.nPaths(); n++) {
                Ray ray = cam.ray(vDis(gen), hDis(gen));
                c += raytracing(ray, scene);
            }
            buffer(i, j) = c / float(cam.nPaths());
        }
    }
}

void pathtrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    double w = buffer.width();
    double h = buffer.height();
    std::cerr << "Working on pathtrace..." << std::endl;
    for (unsigned i = 0; i < h; i++) {
        for (unsigned j = 0; j < w; j++) {
            color c = black;
            std::uniform_real_distribution<float> vDis(i / h, (i + 1) / h);
            std::uniform_real_distribution<float> hDis(j / w, (j + 1) / w);
            for (unsigned n = 0; n < cam.nPaths(); n++) {
                Ray ray = cam.ray(vDis(gen), hDis(gen));
                c += raycast(ray, scene, 1 , 15);
            }
            buffer(i, j) = c / float(cam.nPaths());
        }
    }
}

}