#include "base.h"

#define renderer window_renderer(c)

void pen_mode(context* c, uint32 mode)
{
    c->pen_mode = mode;
}

void pen_color(context* c, color co) 
{ 
    SDL_SetRenderDrawColor(renderer , co.r, co.g, co.b, co.a);
    /*
    if(pen_is_down(c))
    {
        (c->_pen_vertex[c->_pen_idx]).color = to_sdl_color(co);
    }
    */
}
color pen_get_color(context* c)
{
    color co;
    SDL_GetRenderDrawColor(renderer, &co.r, &co.g, &co.b, &co.a);
    return co;
}

void pen_clear(context* c) { SDL_RenderClear(renderer); }

#define X(x) camera_cam_pos_2_pixel_pos_x(c, x)
#define Y(y) camera_cam_pos_2_pixel_pos_y(c, y)

rectf apply_offset(context* c, rectf r)
{
    return rectanglef(X(r.x), Y(r.y), r.w*camera_scale_x(c), r.h*camera_scale_y(c));
}

// todo : affected by pen size
void pen_line(context* c, float x1, float y1, float x2, float y2) { pen_pixel_line(c, X(x1), Y(y1), X(x2), Y(y2)); }
void pen_dot(context* c, float x, float y) { pen_pixel(c, X(x), Y(y)); }
void pen_rect(context* c, rectf r) { r = apply_offset(c, r); pen_pixel_rect(c, r); }

void pen_pixel(context* c, float x, float y) { SDL_RenderDrawPointF(renderer, x, y); }
void pen_pixel_line(context* c, float x1, float y1, float x2, float y2) { SDL_RenderDrawLineF(renderer, x1, y1, x2, y2); }
void pen_pixel_rect(context* c, rectf r) 
{ 
    c->pen_nb_rectangle++;
    SDL_RenderFillRectF(renderer, &r);
}

void pen_pixel_oval(context* c, rectf dest)
{
    // ovale off screen
    if(dest.x > window_width(c) || dest.y > window_height(c) || dest.x +dest.w < 0 || dest.y +dest.h < 0) return;
    float radius_x = dest.w/2;
    float radius_y = dest.h/2;
    float x = dest.x+radius_x;
    float y = dest.y+radius_y;

    if((c->pen_mode) & PEN_MODE_FILLED)
    {
        int stepPrecision = 1; 

        float radius_begin; 
        float radius_end; 

        radius_begin  = 0;
        radius_end = radius_x;

        for(float rx = radius_begin; rx < radius_end; rx+=stepPrecision)
        {
            float height = radius_y*sqrt(1-(1-rx/radius_x)*(1-rx/radius_x));
            pen_pixel_rect(c, rectanglef(x-radius_x+rx,y-height, 2*(radius_x - rx), 2*height));
        }
    }else if((c->pen_mode) & PEN_MODE_HOLLOW)
    {
        int precision = (int)sqrt((radius_x*radius_y)/10)+4;
        if(precision > 0)
        {
            #define PEN_DRAW_CIRCLE_MAX_PRECISION 500
            if(precision > PEN_DRAW_CIRCLE_MAX_PRECISION){ precision = PEN_DRAW_CIRCLE_MAX_PRECISION; }
            int old_x = radius_x;
            int old_y = 0;
            angle a = from_degree(0);

            for(int i = 0;i <= precision;i++)
            {
                a += from_degree(360.0f/precision);

                int new_x = cos(a)*radius_x;
                int new_y = sin(a)*radius_y;
                pen_pixel_line(c, x+old_x, y+old_y, x+new_x, y+new_y);
                old_x = new_x;
                old_y = new_y;
            }
        }
    }
}


void pen_circle(context* c, float x, float y, float radius) { pen_oval(c, x, y, radius, radius); }
void pen_oval(context* c, float x, float y, float radius_x, float radius_y)
{
    rectf dest_pixel = apply_offset(c, rectanglef(x-radius_x,y-radius_y,2*radius_x,2*radius_y));
    pen_pixel_oval(c, dest_pixel);
}

/*
void pen_triangle(context* c, float x1, float y1,
                              float x2, float y2,
                              float x3, float y3
                 )
{
    color co;
    SDL_GetRenderDrawColor(c->renderer, &co.r, &co.g, &co.b, &co.a);
    return pen_triangle_colored(c, x1, y1, co, x2, y2, co, x3, y3, co);
}

void pen_triangle_colored(context* c, float x1, float y1, color c1,
                              float x2, float y2, color c2,
                              float x3, float y3, color c3
                 )
{
    // Thank to https://stackoverflow.com/questions/69447778/fastest-way-to-draw-filled-quad-triangle-with-the-sdl2-renderer
    vertex triangleVertex[3]=
    {
        create_vertex(X(x1), Y(y1), c1),
        create_vertex(X(x2), Y(y2), c2),
        create_vertex(X(x3), Y(y3), c3),
    };

    if( SDL_RenderGeometry(c->renderer, NULL, triangleVertex, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}
}*/

#if 0
/*
void pen_move_2D(context* c, float stepX, float stepY) 
{
    
    //float cosinus = cos(c->pen_move_rotation);
    //float sinus   = sin(c->pen_move_rotation);

    // not sure about that
    //c->pen_x += cosinus*stepX + sinus  *stepY;
    //c->pen_y += sinus  *stepX + cosinus*stepY;
}*/

bool pen_is_down(context*  c)
{
    return c->_pen_is_down;
}
void pen_down(context* c)
{
    check(c->_pen_is_down == false);
    c->_pen_is_down = true;
    c->_pen_idx = 0;
}
void pen_up(context* c)
{
    check(c->_pen_is_down == true);
    c->_pen_is_down = false;
}


void pen_goto(context* c, float x, float y) 
{ 
    c->pen_x = x; c->pen_y = y;
    if(pen_is_down(c))
    {
        c->_pen_idx++;
        //(c->_pen_vertex[c->_pen_idx]).position.x = x;
        //(c->_pen_vertex[c->_pen_idx]).position.y = y;

        //(c->_pen_vertex[c->_pen_idx]).color = to_sdl_color(p);
    }
}
void pen_goto_with_color(context* c, float x, float y, color co)
{
    pen_goto(c, x, y);
    pen_color(c, co);
}

void pen_move(context* c, float step) 
{ 
    pen_goto(c, c->pen_x + cos(c->pen_move_rotation)*step, c->pen_y + sin(c->pen_move_rotation)*step);
}

void pen_rotate(context* c, angle a)
{
    c->pen_move_rotation += a;
}
#endif

void pen_texture(context* c, texture* t, rect src, rectf dest)
{
    dest = apply_offset(c, dest);
    SDL_RenderCopyF(renderer, t, &src, &dest);
}

void pen_texture_at(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY)
{
    pen_texture(c, t, src, rectanglef(x, y, src.w*scaleX,  src.h*scaleY));
}

void pen_texture_at_center(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY)
{
    float frame_width_scaled =  src.w *scaleX;
    float frame_height_scaled = src.h *scaleY;
    pen_texture(c, t, src, rectanglef(x-frame_width_scaled*coef_centerX, y-frame_height_scaled*coef_centerY, frame_width_scaled,  frame_height_scaled));
}


void pen_animation_at(context* c, animation* a, float x, float y, float scaleX, float scaleY, time t, int ligne)
{
    if( !a->nb_frame ) return;
    pen_animation(c, a, rectanglef(x, y, texture_width(a->sprite_sheet->t)/a->nb_frame*scaleX, texture_height(a->sprite_sheet->t)*scaleY), t, ligne);
}

void pen_animation_at_center(context* c, animation* a, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY, time t, int ligne)
{
    float frame_width_scaled =  animation_width (a) *scaleX;
    float frame_height_scaled = animation_height(a) *scaleY;
    pen_animation(c, a, rectanglef(x-frame_width_scaled*coef_centerX, y-frame_height_scaled*coef_centerY, frame_width_scaled, frame_height_scaled), t, ligne);
}

void pen_animation(context* c, animation* a, rectf dest, time t, int ligne)
{
    rect source = *animation_get_frame(a, t);
    source.y += ligne * a->sprite_sheet->frame_height;
    pen_texture(c, a->sprite_sheet->t, source, dest);
}

#define NUM_COL_LETTER 16
#define LETTER_WIDTH  18
#define LETTER_HEIGHT 18
#define INTERLIGNE 0.2
#define LETTER_SPACING -0.5

void pen_text_at(context* c, char* text, float x, float y, float pixel_ligne_height)
{
    float offset_x = 0; int offset_y = 0;
    float step = pixel_ligne_height/LETTER_HEIGHT* LETTER_WIDTH;
    int text_length = (int)strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        char letter = text[i];
        if (letter == '\n')
        {
            offset_x = 0;
            offset_y += (1+INTERLIGNE) * LETTER_HEIGHT;
        }
        else{
            pen_char(c, letter, rectanglef(x+offset_x, y+offset_y, 
                                        pixel_ligne_height,
                                        step));
            offset_x += step + step * LETTER_SPACING;
        }
    }
}

void pen_text_at_center(context* c, char* text, float x, float y, float pixel_ligne_height, float centerX, float centerY)
{
    int h = pixel_ligne_height; 
    int step = pixel_ligne_height/LETTER_HEIGHT* LETTER_WIDTH;
    int w = (int)strlen(text) * (step + step * LETTER_SPACING);

    w *= centerX;
    h *= centerY;

    pen_text_at(c, text, x-w, y-h, pixel_ligne_height);
}

void pen_char_at(context* c, char letter, float x, float y, float pixel_ligne_height)
{
    if (letter > ' ' && letter != '\\')
    {
        rect mask = rectangle((letter % NUM_COL_LETTER) * LETTER_WIDTH,
                              ((letter / NUM_COL_LETTER)) * LETTER_HEIGHT,
                              LETTER_WIDTH, LETTER_HEIGHT);
        pen_texture_at(c, c->_pen_font, mask, x, y,
                        pixel_ligne_height/LETTER_WIDTH,
                        pixel_ligne_height/LETTER_HEIGHT);
    }
}

void pen_char(context* c, char letter, rectf dest)
{
    if (letter > ' ' && letter != '\\')
    {
        rect mask = rectangle((letter % NUM_COL_LETTER) * LETTER_WIDTH,
                              ((letter / NUM_COL_LETTER)) * LETTER_HEIGHT,
                              LETTER_WIDTH, LETTER_HEIGHT);
        pen_texture(c, c->_pen_font, mask, dest);
    }
}

bool pen_load(context* c)
{
    c->_pen_font = texture_create(c, "asset/font_amstrad_cpc_18.png");
    pen_mode(c, PEN_MODE_FILL);

    return true;
}

void pen_unload(context* c)
{
    texture_free(c->_pen_font);
}