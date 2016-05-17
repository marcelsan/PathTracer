#ifndef UTIL_H
#define UTIL_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <cstdio>

bool fcmp(const float a, const float b, const float epsilon = 0.000001f);
double clamp(double x);
int toInt(const double x);

void printMatrix4(const glm::dmat4& M, const char* t);
void printVec4(const glm::vec4& v, const char* title);

glm::dmat4 LookAt(const glm::vec3 &pos, const glm::vec3 &look, const glm::vec3 &up);
#endif