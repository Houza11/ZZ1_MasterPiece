#include "base.h"

time timer_since_launch(context* c) { return c->timer; }
time timer_scene(context* c) { return context_get_current_scene(c)->info.time; }

bool timer_load(context* c)
{
    c->fps_counter = 0;
    c->fps = 60;
    c->last_fps_tick = c->timer;
    c->paused = false;
    return true;
}
void timer_unload(context* c)
{
    unused(c);
}
void timer_update(context* c)
{
    c->fps_counter++;
    if(c->timer - c->last_fps_tick >= from_s(1))
    {
        c->fps = c->fps_counter;
        c->fps_counter = 0;
        c->last_fps_tick = c->timer;
    }
}