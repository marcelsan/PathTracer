#include "transform.h"
#include "util.h"

void Transform::translate(glm::vec3& translation)
{
    glm::mat4 tm = glm::translate(glm::mat4(), translation);
    transform *= tm;
}

void Transform::scale(glm::vec3& scale)
{
    glm::mat4 sm = glm::scale(glm::mat4(), scale);
    transform *= sm;
}

glm::vec3 Transform::operator() (glm::vec3& v) const
{
    glm::vec4 r = transform * glm::vec4(v, 1.0f);

    r.x = r.x/r.w;
    r.y = r.y/r.w;
    r.z = r.z/r.w;

    return glm::vec3(r);
}

std::ostream& operator<<(std::ostream &output, const Transform& t)
{
    printMatrix4(t.transform, "Transform ");
    return output;
}