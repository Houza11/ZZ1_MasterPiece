#include "base.h"


rect square(int x, int y, int wh) { return rectangle(x, y, wh, wh); }
rect rectangle(int x, int y, int w, int h)
{
    rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}

rectf squaref(float x, float y, float wh) { return rectanglef(x, y, wh, wh); }
rectf rectanglef(float x, float y, float w, float h)
{
    rectf r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}