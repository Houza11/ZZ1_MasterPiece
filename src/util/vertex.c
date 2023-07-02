#include "base.h"

SDL_Vertex create_vertex(float x, float y, color co)
{
    SDL_Vertex v;
    v.color = to_sdl_color(co);
    v.position.x = x;
    v.position.y = y;
    v.tex_coord.x = 0;
    v.tex_coord.y = 0;
    return v;
}