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

    c->action_right      = false;
    c->action_old_right  = false;
    c-> action_old_right = false;
    c-> action_left      = false;
    c-> action_old_left  = false;
    c-> action_up        = false;
    c-> action_old_up    = false;
    c-> action_down      = false;
    c-> action_old_down  = false;

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

    c->action_old_right = c->action_right;
    c->action_old_left  = c->action_left;
    c->action_old_up    = c->action_up;
    c->action_old_down  = c->action_down;

    c->kb_state = SDL_GetKeyboardState(NULL);
}

bool input_event(context* c, event* ev)
{
    switch(ev->type)
    {
        case SDL_MOUSEBUTTONDOWN: c->mouse_left_button_down = true;  break;
        case SDL_MOUSEBUTTONUP:   c->mouse_left_button_down = false; break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            bool pressed = ev->type == SDL_KEYDOWN;
            switch (ev->key.keysym.sym)
            {
                case SDLK_RIGHT:
                case SDLK_f:
                    c->action_right = pressed;
                break;

                case SDLK_LEFT:
                case SDLK_s:
                    c->action_left = pressed;
                break;

                case SDLK_UP:
                case SDLK_e:
                    c->action_up = pressed;
                break;

                case SDLK_DOWN:
                case SDLK_d:
                    c->action_down = pressed;
                break;

                default: break;
            }
        }
        default: break;
    }
    return false;
}

bool input_right(context* c) { return c->action_right; }
bool input_left (context* c) { return c->action_left; }
bool input_up   (context* c) { return c->action_up; }
bool input_down (context* c) { return c->action_down; }

bool input_old_right(context* c) { return c->action_old_right; }
bool input_old_left (context* c) { return c->action_old_left; }
bool input_old_up   (context* c) { return c->action_old_up; }
bool input_old_down (context* c) { return c->action_old_down; }