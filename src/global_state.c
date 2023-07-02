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
    pen_text_at_center(c, "title", window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5);
}

void global_state_printf(context* c)
{
    unused(c);
}

bool global_state_event(context* c, event* ev)
{
    unused(c);
    unused(ev);
    /*
    switch (ev->type)
    {
        //mousePress(ev->button.);
        case SDL_KEYDOWN: //case SDL_KEYUP:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_ESCAPE: c->should_exit = true; break;
                case SDLK_m: scene_set(c, martin); return true;
                case SDLK_t: scene_set(c, thomas_parallax); return true;
                case SDLK_h: scene_set(c, houza); return true;
                case SDLK_j: scene_set(c, graph_joueur); gs->g->draw_text_info = GRAPH_DISPLAY_MODE_GRAPHIC; return true;
                case SDLK_f: scene_set(c, fourmi); return true;
                case SDLK_g: gs->g->draw_text_info = (gs->g->draw_text_info+1) % GRAPH_DISPLAY_MODE_MODULO ; return true;
                case SDLK_UP: case SDLK_RIGHT: gs->nb_node++; return true;
                case SDLK_DOWN: case SDLK_LEFT: gs->nb_node = gs->nb_node <= 2 ? 2 : gs->nb_node-1; return true;

                case SDLK_r: global_state_reset_traveler(c); return true;
                
                // Debug
                case SDLK_d: 
                    scene_printf(c, (scene*)(c->scene));
                    global_state_new_get_graph(c);
                return true;
                // menu Principal
                case SDLK_p: scene_set(c, titre); return true;
                default: break;
            }
        } break;
        default: break;
    }*/

    return false;
}