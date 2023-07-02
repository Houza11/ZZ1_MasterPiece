#include "base.h"

void window_center_coef(context* c, float coef_x, float coef_y)
{
    SDL_SetWindowPosition(c->window, coef_x*(c->screen_width-c->window_width), (1-coef_y)*(c->screen_height-c->window_height));
}

rectf window_rectf(context* c)
{
    int w; int h;
    SDL_GetWindowSize(c->window, &w, &h);
    return rectanglef(0,0,w,h);
}

rect window_rect(context* c)
{
    int w; int h;
    SDL_GetWindowSize(c->window, &w, &h);
    return rectangle(0,0,w,h);
}

bool window_load(context* c, char* window_name, int width, int height, Uint32 flags)
{
    c->window = SDL_CreateWindow(window_name,
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            width,
                                            height,
                                            flags);

    if (c->window == NULL)
    {
        printf("Impossible de creer la fenetre: %s\n", SDL_GetError());
        return false;
    }

    c->renderer = SDL_CreateRenderer(c->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (c->renderer == NULL)
    {
        printf("Impossible de creer le renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(c->window);
        return false;
    }

    c->window_width = width;
    c->window_width = height;
    SDL_GetWindowSize(c->window, &c->window_width, &c->window_height);
    return true;
}

void window_unload(context* c)
{
    SDL_DestroyRenderer(c->renderer);
    SDL_DestroyWindow(c->window);
}

void window_update(context* c)
{
    SDL_DisplayMode screen;
    SDL_GetCurrentDisplayMode(0, &screen);
    c->screen_width  = screen.w;
    c->screen_height = screen.h;

    SDL_GetWindowPosition(c->window, &c->window_x, &c->window_y);
    SDL_GetWindowSize(c->window, &c->window_width, &c->window_height);

    c->window_ratio_width_div_height = c->screen_width/(float)c->screen_height;
    c->window_ratio_height_div_width = c->screen_height/(float)c->screen_width;
}

int screen_width(context* c) { return c->screen_width; }
int screen_height(context* c) { return c->screen_height; }

SDL_Renderer* screen_renderer(context* c) { return c->renderer; }

SDL_Window* window(context* c) { return c->window; }
int window_width(context* c) { return c->window_width; }
int window_height(context* c) { return c->window_height; }
int window_x(context* c) { return c->window_x; }
int window_y(context* c) { return c->window_y; }
float window_ratio_width_div_height(context* c) { return c->window_ratio_width_div_height; }
float window_ratio_height_div_width(context* c) { return c->window_ratio_width_div_height; }