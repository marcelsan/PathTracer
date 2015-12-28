#include "light.h"

#include "object.h"

namespace PathTrace {

vec3 Light::samplePosition() const
{
    return object()->samplePosition();
}

}
