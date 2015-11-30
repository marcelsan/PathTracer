
#include "camera.h"

namespace PathTrace {

Camera::Camera()
{
}

Camera::Camera(vec3 e)
    : eye(e)
{
}

Camera::~Camera()
{
}

}