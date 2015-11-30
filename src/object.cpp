#include "object.h"

namespace PathTrace {

Object::Object()
{
}


Object::Object(const Material& m)
    : mat(m)
{
}

Object::~Object()
{
}

}