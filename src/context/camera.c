#include "base.h"

#define current_state (vec_peek(c->cams, camera_state))
#define first_state   (vec_get(c->cams, camera_state, 0))

float camera_x(context* c) { return current_state.x; }
float camera_y(context* c) { return current_state.y; }
float camera_scale_x(context* c) { return current_state.scale_x; }
float camera_scale_y(context* c) { return current_state.scale_y; }

void camera_set_x(context* c, float v) { current_state.x = v; }
void camera_set_y(context* c, float v) { current_state.y = v; }

float camera_scale_range(float v)
{
    float max_precision = 100.0f;
    return maxif(1/max_precision, minif(max_precision, v));
}
float camera_set_scale_x(context* c, float v) { current_state.scale_x = camera_scale_range(v); return current_state.scale_x; }
float camera_set_scale_y(context* c, float v) { current_state.scale_y = camera_scale_range(v); return current_state.scale_y; }

bool camera_load(context* c)
{
    c->cams = vec_empty(camera_state);
    vec_push(c->cams, camera_state, camera_default());
    camera_set_x(c, 0);
    camera_set_y(c, 0);
    camera_set_scale_x(c, 1);
    camera_set_scale_y(c, 1);

    bool allow = true;
    camera_allow_scrolling(c, allow);
    camera_allow_zooming(c, allow);
    return true;
}

void camera_unload(context* c)
{ 
    vec_free_lazy(c->cams);
    c->cams = null;
}

void camera_update(context* c)
{
    if(camera_can_scroll(c) && c->mouse_left_button_down)
    {
        //first_state
        //first_state.x -= c->mouse_delta_x/first_state.scale_x;
        //first_state.y -= c->mouse_delta_y/first_state.scale_y;

        current_state.x -= c->mouse_delta_x/current_state.scale_x;
        current_state.y -= c->mouse_delta_y/current_state.scale_y;
    }
}

void camera_zoom(context* c, float center_pixel_x, float center_pixel_y, float coef)
{
    if(coef == 1) return;
    float center_coef_x = center_pixel_x /(float)window_width(c);
    float center_coef_y = center_pixel_y /(float)window_height(c);

    float old_scale_x = camera_scale_x(c);

    float new_scale_x = camera_scale_range(camera_scale_x(c)*coef);
    float new_scale_y = camera_scale_range(camera_scale_y(c)*coef);

    coef =  new_scale_x / old_scale_x;

    float offset_x = (1-coef) * window_width(c);
    float offset_y = (1-coef) * window_height(c);

    camera_set_x(c, camera_x(c) - (offset_x*center_coef_x)/new_scale_x);
    camera_set_y(c, camera_y(c) - (offset_y*center_coef_y)/new_scale_y);

    camera_set_scale_x(c, new_scale_x);
    camera_set_scale_y(c, new_scale_y);
}

bool camera_event(context* c, event* ev)
{
    if(camera_can_zoom(c))
    {
        if(ev->type == SDL_MOUSEWHEEL)
        {
            #define coef (1+0.1f *ev->wheel.y)
            if(ev->wheel.y > 0) // scroll up
            {
                camera_zoom(c, input_mouse_x(c), input_mouse_y(c), coef);
                // Put code for handling "scroll up" here!
            }
            else if(ev->wheel.y < 0) // scroll down
            {
                camera_zoom(c, input_mouse_x(c), input_mouse_y(c), coef);
            }

            if(ev->wheel.x > 0) // scroll right
            {
                // ...
            }
            else if(ev->wheel.x < 0) // scroll left
            {
                // ...
            }
        }
        else if(ev->type == SDL_MOUSEBUTTONDOWN)
        {
            if(camera_can_scroll(c))
            {
                //camera_set_x(input_mouse_x(c))
                //c->_camera_x += (c->mouse_old_x-c->mouse_x); ///c->_camera_scale_x;
                //c->_camera_y += (c->mouse_old_y-c->mouse_y); ///c->_camera_scale_y;
            }
            // ... handle mouse clicks ...
        }
    }

    return false;
}

void camera_allow_zooming(context* c, bool b)
{
    current_state.can_zoom = b;
}
void camera_allow_scrolling(context* c, bool b)
{
    current_state.can_scroll = b;
}

bool camera_can_zoom(context* c) { return current_state.can_zoom; }
bool camera_can_scroll(context* c) { return current_state.can_scroll; }

camera_state camera_get(context* c)
{   
    return current_state;
}

camera_state camera_state_create(float x, float y, float scale_x, float scale_y, bool allow_scrolling, bool allow_zooming)
{
    camera_state s;
    s.x = x;
    s.y = y;
    s.scale_x = scale_x;
    s.scale_y = scale_y;
    s.can_scroll = allow_scrolling;
    s.can_zoom   = allow_zooming;
    return s;
}

void camera_set(context* c, camera_state s)
{
    camera_set_x(c, s.x);
    camera_set_y(c, s.y);
    camera_set_scale_x(c, s.scale_x);
    camera_set_scale_y(c, s.scale_y);
}

camera_state camera_default()
{
    return camera_state_create(0,0,1,1, false, false);
}


float camera_cam_pos_2_pixel_pos_x(context* c, float x) { return (x - camera_x(c))*camera_scale_x(c); }
float camera_cam_pos_2_pixel_pos_y(context* c, float y) { return (y - camera_y(c))*camera_scale_y(c); }

float camera_pixel_pos_2_cam_pos_x(context* c, float pos) { return pos/camera_scale_x(c)+camera_x(c); }
float camera_pixel_pos_2_cam_pos_y(context* c, float pos) { return pos/camera_scale_y(c)+camera_y(c); }

// relative
void camera_push(context* c, camera_state state)
{
    unused(c);
    vec_push(c->cams, camera_state, state);
}

void camera_push_set(context* c, camera_state state)
{
    unused(c);
    vec_push(c->cams, camera_state, state);
}

void camera_pop(context* c)
{
    check(c->cams->length >= 1);
    vec_remove_end(c->cams);
}

void camera_push_focus_fullscreen(context* c, rectf source)
{
    camera_push_focus(c, source, window_rectf(c));
}

void camera_push_focus(context* c, rectf source, rectf dest)
{
    camera_push_focus_centered(c, source, dest, 0.5, 0.5);
}

void camera_push_focus_centered(context* c, rectf source, rectf dest, float center_x_coef, float center_y_coef)
{
    float d_ratio_xy = window_ratio_width_div_height(c);
    float s_ratio_xy = source.w/source.h;
    unused(d_ratio_xy);
    unused(s_ratio_xy);
    unused(center_x_coef);
    unused(center_y_coef);


    float scale_x = (dest.w / source.w)*camera_scale_x(c);
    float scale_y = (dest.h / source.h)*camera_scale_y(c);


    float x = source.x + camera_x(c)*(camera_scale_x(c)/scale_x);
    float y = source.y + camera_y(c)*(camera_scale_y(c)/scale_y);

    /*
    if(d_ratio_xy > s_ratio_xy)
    {
        //limited by Y
    }else
    {
        //limited by X
    }*/

    camera_state cs = camera_state_create(x, y,scale_x,scale_y, camera_can_scroll(c), camera_can_zoom(c));
    camera_push_set(c,cs);
}