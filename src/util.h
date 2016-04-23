#ifndef UTIL_H
#define UTIL_H

bool fcmp(const float a, const float b, const float epsilon = 0.000001f);
double clamp(double x);
int toInt(const double x);

#endif