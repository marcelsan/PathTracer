#include "raytrace.h"

#include <glm/glm.hpp>
#include <cmath>
#include <random>

#include "feature.h"
#include "ray.h"
#include "util.h"
#include "npywriter.h"

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

inline static Feature raycast(const Ray& ray, const Scene& scene, float srcIr = 1.0f, int depth = 5)
{
    Feature feat;

    Intersection inter;
    if (!scene.raycast(ray, inter)) {
        feat.col = scene.background();
        feat.positive = true;
        return feat;
    }

    feat.normal = inter.n;
    Material mat = feat.mat = inter.m;

    if (mat.emissive) {
        feat.col = mat.color;
        return feat;
    }

    vec3 N = inter.n;
    vec3 V = normalize(ray.d);
    vec3 R = reflect(V, N);

    if (depth <= 0) {
        feat.col = scene.background();
        feat.positive = -1.0f;
        return feat;
    }

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

        c += mat.color * mat.kd * raycast(inter.rayTo(d), scene, srcIr, depth - 1).col;
    } else if ((r -= mat.ks) < 0) {
        c += mat.color * mat.ks * raycast(inter.rayTo(R), scene, srcIr, depth - 1).col;
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
            c += mat.color * mat.kt * raycast(inter.rayTo(T), scene, mat.ir, depth - 1).col;
        }
    }

    feat.col = c;
    return feat;
}

void pathtrace(std::string filename, const Size& size, const Scene& scene, const Camera& cam)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    double w = size.width;
    double h = size.height;
    std::cerr << "Working on pathtrace..." << std::endl;

    NPYWriter writer(filename);
    writer.writeHeader({cam.nPaths(), size.height, size.width, Feature::feature_size});
    for (unsigned n = 0; n < cam.nPaths(); n++) {
        for (unsigned i = 0; i < h; i++) {
            for (unsigned j = 0; j < w; j++) {
                std::uniform_real_distribution<float> vDis(i / h, (i + 1) / h);
                std::uniform_real_distribution<float> hDis(j / w, (j + 1) / w);
                Ray ray = cam.ray(vDis(gen), hDis(gen));
                writer.write(raycast(ray, scene, 1 , 15).data());
            }
        }
    }
}

}