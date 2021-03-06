#include "material.h"

namespace PathTrace {

Material::Material()
{
}

Material::Material(vec3 color, float ka, float kd, float ks, float kt, int n, float ir, bool e)
    : color(color)
    , ka(ka)
    , kd(kd)
    , ks(ks)
    , kt(kt)
    , n(n)
    , ir(ir)
    , emissive(e)
{
}

}