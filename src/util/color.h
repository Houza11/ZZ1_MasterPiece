#ifndef COLOR_H
#define COLOR_H
#include "base.h"

#define color_red   rgb(255, 0, 0)
#define color_green rgb(0, 255, 0)
#define color_blue  rgb(0, 0, 255)
#define color_white rgb(255, 255, 255)
#define color_black rgb(0, 0, 0)

typedef struct 
{
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
} color;

#define red(color)   (color.r)
#define green(color) (color.g)
#define blue(color)  (color.b)
#define alpha(color) (color.a)

color rgb(uint8 r, uint8 g, uint8 b);
color rgba(uint8 r, uint8 g, uint8 b, uint8 a);

SDL_Color to_sdl_color(color c);

color hsv(float h_0_to_360, float s_0_to_1, float v_0_to_1);

#endif