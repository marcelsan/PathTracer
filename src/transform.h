#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{

public:
    void translate(glm::vec3& trans);
    void scale(glm::vec3& scale);
    glm::vec3 operator() (glm::vec3& v) const;
    friend std::ostream& operator<<(std::ostream &output, const Transform& t);

private:
    glm::mat4 transform = glm::mat4();

};

#endif