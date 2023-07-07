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

    repeat(i, input_max_player)
    {
        c->action_bufferized[i] = vec_empty(timed_action);
    }

    return true;
}

void input_unload(context* c)
{ 
    repeat(i, input_max_player)
    {
        vec_free_lazy(c->action_bufferized[i]);
    }
}

void input_update(context* c)
{
    c->mouse_old_flag = c->mouse_flag;
    c->mouse_old_x = c->mouse_x;
    c->mouse_old_y = c->mouse_y;
    c->mouse_flag = SDL_GetMouseState(&(c->mouse_x), &(c->mouse_y));

    c->mouse_delta_x = c->mouse_x - c->mouse_old_x;
    c->mouse_delta_y = c->mouse_y - c->mouse_old_y;

    c->kb_state = SDL_GetKeyboardState(NULL);

    repeat(i, input_max_player)
    {
        vec* action_buffer = c->action_bufferized[i];
        while(action_buffer->length > 0 && c->timer - vec_get(action_buffer, timed_action, 0).time_pressed > action_expiration)
        {
            vec_remove_at(action_buffer, 0);
        }
    }
}

bool check_player_idx(int playerIdx)
{
    return playerIdx >= 0 && playerIdx < input_max_player;
}

void push_action(context* c, int val, int playerIdx)
{
    if(!check_player_idx(playerIdx)){ return; }
    timed_action a;
    a.time_pressed = c->timer;
    a.action = val;
    vec_push(c->action_bufferized[playerIdx], timed_action, a);
}

bool input_event(context* c, event* ev)
{
    switch(ev->type)
    {
        case SDL_MOUSEBUTTONDOWN: c->mouse_left_button_down = true;  break;
        case SDL_MOUSEBUTTONUP:   c->mouse_left_button_down = false; break;

        case SDL_KEYDOWN:
        //case SDL_KEYUP:
        {
            //bool pressed = ev->type == SDL_KEYDOWN;
            switch (ev->key.keysym.sym)
            {
                case SDLK_RIGHT:
                    push_action(c, action_right, 0);
                break;

                case SDLK_LEFT:
                    push_action(c, action_left, 0);
                break;

                case SDLK_UP:
                    push_action(c, action_up, 0);
                break;

                case SDLK_DOWN:
                    push_action(c, action_down, 0);
                break;

                case SDLK_SPACE:
                    push_action(c, action_sp0, 0);
                break;

                case SDLK_n:
                    push_action(c, action_sp1, 0);
                break;

                default: break;
            }
        }
        default: break;
    }
    return false;
}

void action_ignore(context* c, action action, int playerIdx)
{
    if(!check_player_idx(playerIdx)) return;
    for(int i = c->action_bufferized[playerIdx]->length-1; i >= 0; i--)
    {
        if(vec_get(c->action_bufferized[playerIdx], timed_action, i).action == action)
        {
            vec_remove_at(c->action_bufferized[playerIdx], 0);
        }
    }
}

//p1
bool action_consume(context* c, action action, int playerIdx)
{   
    if(!check_player_idx(playerIdx)) return false;

    if(c->action_bufferized[playerIdx]->length > 0 && vec_get(c->action_bufferized[playerIdx], timed_action, 0).action == action)
    {
        vec_remove_at(c->action_bufferized[playerIdx], 0);
        return true;
    }
    return false;
}

bool input_right(context* c, int playerIdx) { return action_consume(c, action_right, playerIdx);}
bool input_left (context* c, int playerIdx) { return action_consume(c, action_left, playerIdx); }
bool input_up   (context* c, int playerIdx) { return action_consume(c, action_up, playerIdx);   }
bool input_down (context* c, int playerIdx) { return action_consume(c, action_down, playerIdx); }
bool input_special0(context* c, int playerIdx) { return action_consume(c, action_sp0, playerIdx);  }
bool input_special1(context* c, int playerIdx) { return action_consume(c, action_sp1, playerIdx);  }