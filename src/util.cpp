#include "util.h"
#include <cmath>

double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; } 
int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }
bool fcmp(float a, float b, float epsilon) { return (fabs(a - b) < epsilon); }