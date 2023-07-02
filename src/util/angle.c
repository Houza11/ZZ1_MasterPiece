#include "base.h"

angle from_degree(float val)
{
    angle a;
    a = val * pi / 180;
    return a;
}
angle from_radian(float val) { return val; }

float as_degree(angle a) { return a/pi*180; }
float as_radian(angle a) { return a; }