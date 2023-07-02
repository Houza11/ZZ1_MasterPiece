#ifndef CONTEXT_WINDOW_H
#define CONTEXT_WINDOW_H

#include "base.h"

void window_center_coef(context* c, float coef_x, float coef_y);
bool window_load(context* c, char* window_name, int width, int height, Uint32 flags);
void window_unload(context* c);
void window_update(context* c);

int screen_width(context* c);
int screen_height(context* c);

#define  window_renderer(context) screen_renderer(context)
SDL_Renderer* screen_renderer(context* c);

SDL_Window* window(context* c);
int window_width(context* c);
int window_height(context* c);
int window_x(context* c);
int window_y(context* c);
float window_ratio_width_div_height(context* c);
float window_ratio_height_div_width(context* c);

rectf window_rectf(context* c);
rect window_rectangle(context* c);

#endif