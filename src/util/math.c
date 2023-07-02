#include "base.h"

float squared(float x) { return x*x; }

float length(float x1, float y1, float x2, float y2)
{
    return sqrt(squared(x2-x1)+squared(y2-y1));
}

float length_squared(float x1, float y1, float x2, float y2)
{
    return squared(x2-x1)+squared(y2-y1);
}

float maxif(float a, float b) { return a > b ? a : b; }
float minif(float a, float b) { return a < b ? a : b; }