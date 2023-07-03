#include "base.h"

#define FPS_IDLE 500
#define FPS_WALK 200

/*
no opti, fast compile : -O0
lot of opti, slow compile : -O4

gcc -O0 -fdiagnostics-color=always -g ./src/*.c ./src/betterC/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/ordi/*.c ./src/game/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
./bin/main.exe
gource
*/

void global_state_load(context* c)
{
    unused(c);
}
void global_state_unload(context* c)
{
    unused(c);
}

void global_state_update(context* c)
{
    unused(c);
}


void global_state_draw(context* c)
{
    pen_color(c, rgb(93,39,137));
    pen_clear(c);
}

void global_state_printf(context* c)
{
    unused(c);
}

bool global_state_event(context* c, event* ev)
{
    unused(c);
    unused(ev);
    
    switch (ev->type)
    {
        //mousePress(ev->button.);
        case SDL_KEYDOWN: //case SDL_KEYUP:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_ESCAPE: c->should_exit = true; break;
                case SDLK_r: scene_set(c, jeu); return true;
                case SDLK_d: scene_printf(c, (scene*)(c->scene)); return true;
                default: break;
            }
        } break;
        default: break;
    }

    return false;
}