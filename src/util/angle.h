#ifndef ANGLE_H
#define ANGLE_H
#include "base.h"
#include <math.h>

#define pi (3.14159265358979323846f)
typedef float angle;

angle from_degree(float val);
angle from_radian(float val);

#define angle_from_vector(x,y) atan2f((float)(y), (float)(x))

float as_degree(angle);
float as_radian(angle);

#define cos(a)  (cosf)(a)
#define sin(a)  (sinf)(a)
#endif