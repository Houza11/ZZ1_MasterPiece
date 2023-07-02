#include "base.h"

int input_mouse_x(context* c) { return c->mouse_x; }
int input_mouse_y(context* c) { return c->mouse_y; }
int input_mouse_old_x(context* c) { return c->mouse_old_x; }
int input_mouse_old_y(context* c) { return c->mouse_old_y; }
int input_mouse_delta_x(context* c) { return input_mouse_x(c)-input_mouse_old_x(c);  }
int input_mouse_delta_y(context* c) { return input_mouse_y(c)-input_mouse_old_y(c);  }
int32 input_mouse_flag(context* c) { return c->mouse_flag; }
const Uint8* input_kb_state(context* c) { return c->kb_state; }

void get_last_mouse_pos(context* c)
{
    c->mouse_flag = SDL_GetMouseState(&(c->mouse_x), &(c->mouse_y));
}

bool input_load(context* c)
{
    c->mouse_left_button_down = false;
    get_last_mouse_pos(c);
    c->mouse_old_x = c->mouse_x;
    c->mouse_old_y = c->mouse_y;
    return true;
}

void input_unload(context* c){ unused(c);}


void input_update(context* c)
{
    c->mouse_old_flag = c->mouse_flag;
    c->mouse_old_x = c->mouse_x;
    c->mouse_old_y = c->mouse_y;
    c->mouse_flag = SDL_GetMouseState(&(c->mouse_x), &(c->mouse_y));

    c->mouse_delta_x = c->mouse_x - c->mouse_old_x;
    c->mouse_delta_y = c->mouse_y - c->mouse_old_y;

    c->kb_state = SDL_GetKeyboardState(NULL);
}

bool input_event(context* c, event* ev)
{
    switch(ev->type){
        case SDL_MOUSEBUTTONDOWN: c->mouse_left_button_down = true; break;
        case SDL_MOUSEBUTTONUP: c->mouse_left_button_down = false; break;

    }
    return false;
}