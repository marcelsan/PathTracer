#include "util.h"
#include <cmath>

double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; } 
int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }
bool fcmp(float a, float b, float epsilon) { return (fabs(a - b) < epsilon); }
void printMatrix4(const glm::dmat4& M, const char* t)
{
    printf("M(%s) = ", t);
    for(int i = 0; i < 4; ++i) {
        printf("[%f %f %f %f]\n", M[i][0], M[i][1], M[i][2], M[i][3]);
    }
    printf("\n");
}

void printVec4(const glm::vec4& v, const char* title)
{
    printf("vec4(%s) = ", title);
    printf("[%f %f %f %f]\n", v[0], v[1], v[2], v[3]);
    printf("\n");
}

glm::dmat4 LookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) {
    
    glm::dmat4 cameraToWorld;
    // Initialize fourth column of viewing matrix
    cameraToWorld[0][3] = eye.x;
    cameraToWorld[1][3] = eye.y;
    cameraToWorld[2][3] = eye.z;
    cameraToWorld[3][3] = 1;

    glm::vec3 dir = glm::normalize(center - eye);
    glm::vec3 left = glm::normalize(glm::cross(glm::normalize(up), dir));
    glm::vec3 newUp = glm::cross(dir, left);

    cameraToWorld[0][0] = left.x;
    cameraToWorld[1][0] = left.y;
    cameraToWorld[2][0] = left.z;
    cameraToWorld[3][0] = 0.;
    cameraToWorld[0][1] = newUp.x;
    cameraToWorld[1][1] = newUp.y;
    cameraToWorld[2][1] = newUp.z;
    cameraToWorld[3][1] = 0.;
    cameraToWorld[0][2] = dir.x;
    cameraToWorld[1][2] = dir.y;
    cameraToWorld[2][2] = dir.z;
    cameraToWorld[3][2] = 0.;

    return glm::inverse(cameraToWorld);
}