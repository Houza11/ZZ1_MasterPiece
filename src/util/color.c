#include "base.h"

color rgb(uint8 r, uint8 g, uint8 b)
{
    color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = 255;
    return c;
}

color rgba(uint8 r, uint8 g, uint8 b, uint8 a)
{
    color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

SDL_Color to_sdl_color(color c)
{
    SDL_Color co;
    co.r = red(c);
    co.g = green(c);
    co.b = blue(c);
    co.a = alpha(c);
    return co;
}


// Thank to https://www.programmingalgorithms.com/algorithm/hsv-to-rgb/c/
color hsv(float h, float s, float v)
{
    double r = 0, g = 0, b = 0;

	if (s == 0)
	{
		r = v;
		g = v;
		b = v;
	}
	else
	{
		int i;
		double f, p, q, t;

		if (h == 360) { h = 0;}
		else { h /= 60; }

		i = (int)trunc(h);
		f = h - i;

		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch (i)
		{
            case 0:
                r = v;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = v;
                b = p;
                break;

            case 2:
                r = p;
                g = v;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = v;
                break;

            case 4:
                r = t;
                g = p;
                b = v;
                break;

            default:
                r = v;
                g = p;
                b = q;
                break;
        }
	}

	return rgb(r * 255, g * 255, b * 255);
}