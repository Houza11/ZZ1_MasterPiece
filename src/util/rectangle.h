#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "base.h"

rectf rectanglef(float x, float y, float w, float h);
rectf squaref(float x, float y, float wh);

rect rectangle(int x, int y, int w, int h);
rect square(int x, int y, int wh);

#endif