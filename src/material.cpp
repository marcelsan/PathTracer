#include "material.h"

namespace PathTrace {

Material::Material()
{
}

Material::Material(vec3 color, float ka, float kd, float ks, float kt, int n)
    : color(color)
    , ka(ka)
    , kd(kd)
    , ks(ks)
    , kt(kt)
    , n(n)
{
}

Material::Material(vec3 color, float ka, float kd, float ks, float kt, int n)
    : color(color)
    , ka(ka)
    , kd(kd)
    , ks(ks)
    , kt(kt)
    , n(n)
{
}

}